extern "C" {
    #include "../../../Dependencies/luajit/src/lua.h"
    #include "../../../Dependencies/luajit/src/lauxlib.h"
    #include "../../../Dependencies/luajit/src/lualib.h"
}

#include <functional>

#define REGISTER_START struct _proxy {
#define REGISTER_END };

namespace gene { namespace scripting {
    namespace lua {
        inline void PushToStack(lua_State* state, const double& v) { lua_pushnumber(state, v); }

        inline void PushToStack(lua_State* state, const char* str) { lua_pushstring(state, str); }

        inline void PushToStack(lua_State* state, const int& i) { lua_pushinteger(state, i); }

        inline void PushToStack(lua_State* state, const bool& b) { lua_pushboolean(state, b); }

        inline void PushToStack(lua_State* state) {}

        template <typename T, typename... Args>
        inline void PushToStack(lua_State* state, const T& t, const Args&... args)
        {
            PushToStack(state, t);
            PushToStack(state, args...);
        }

        template<typename T>
        inline T GetFromStack(lua_State* state, const int& index);

        template <>
        inline int GetFromStack(lua_State* state, const int& index) { return lua_tointeger(state, index); }

        template <>
        inline double GetFromStack(lua_State* state, const int& index) { return lua_tonumber(state, index); }

        template <>
        inline const char* GetFromStack(lua_State* state, const int& index) { return lua_tostring(state, index); }

        template <>
        inline bool GetFromStack(lua_State* state, const int& index) { return lua_toboolean(state, index); }

        struct BaseFunction 
        {
            virtual int Apply(lua_State* state) = 0;
        };
        
        template <int... Is>
        struct Indices {};

        template <int N, int... Is>
        struct IndicesBuilder : IndicesBuilder<N - 1, N - 1, Is...> {};

        template <int... Is>
        struct IndicesBuilder<0, Is...> 
        {
            using Type = Indices<Is...>;
        };

        template <typename T>
        struct Id {};

        template <typename... T, int... N>
        inline std::tuple<T...> GetArgs(lua_State* state, Indices<N...>)
        {
            return std::make_tuple(GetFromStack<T>(state, N + 1)...);
        }

        template <typename... T>
        inline std::tuple<T...> GetArgs(lua_State* state)
        {
            return GetArgs<T...>(state, typename IndicesBuilder<sizeof...(T)>::Type());
        }
        
        template <typename Ret, typename... Args, int... N>
        Ret Lift(std::function<Ret(Args...)> fun, std::tuple<Args...> args, Indices<N...>)
        {
            return fun(std::get<N>(args)...);
        }

        template <typename Ret, typename... Args>
        Ret Lift(std::function<Ret(Args...)> fun, std::tuple<Args...> args) 
        {
            return Lift(fun, args, typename IndicesBuilder<sizeof...(Args)>::Type());
        }

        template <int N, typename Ret, typename... Args>
        struct Function : BaseFunction 
        {
            using StdFuncType = std::function<Ret(Args...)>;

            const char* Name;
            StdFuncType Functor;

            Function(lua_State* state, const char*funcName, StdFuncType func): Name(funcName), Functor(func) 
            {
                lua_pushlightuserdata(state, (void*)static_cast<BaseFunction*>(this));
                lua_pushcclosure(state, &lua::LuaFunctorDispatcher, 1);
            }

            virtual int Apply(lua_State* state)
            {
                std::tuple<Args...> args = lua::GetArgs<Args...>(state);
                Ret v = lua::Lift(Functor, args);
                lua::PushToStack(state, v);
                return 1;
            }
        };

        template <typename... Args>
        struct Function<0, void, Args...> : BaseFunction {
            using StdFuncType = std::function<void(Args...)>;
            const char* Name;
            StdFuncType Functor;

            Function(lua_State* state, const char*funcName, StdFuncType func) : Name(funcName), Functor(func) 
            {
                lua_pushlightuserdata(state, (void*)static_cast<BaseFunction*>(this));
                lua_pushcclosure(state, &lua::LuaFunctorDispatcher, 1);
           }

            virtual int Apply(lua_State* state)
            {
                std::tuple<Args...> args = lua::GetArgs<Args...>(state);
                lua::Lift(Functor, args);
                return 1;
            }
        };

        int LuaFunctorDispatcher(lua_State* state)
        {
            void* ptr = lua_touserdata(state, lua_upvalueindex(1));
            BaseFunction *base = (BaseFunction*)ptr;
            return base->Apply(state);
        }
    }

    class LuaTable
    {
    public:
        LuaTable(lua_State* state, const char* tableName)
            : m_State(state), m_TableName(tableName)
        {
            lua_newtable(state);
            lua_setglobal(state, tableName);
        }

        template <typename KeyType, typename ValueType>
        void AddPair(KeyType key, ValueType value)
        {
            lua_getglobal(m_State, m_TableName);
            lua::PushToStack(m_State, key);
            lua::PushToStack(m_State, value);
            lua_settable(m_State, -3);
            lua_setglobal(m_State, m_TableName);
        }

    private:
        lua_State * m_State;
        const char* m_TableName;
    };

    class LuaEnvironment 
    {
    public:
        LuaEnvironment() 
        {
            m_state = luaL_newstate();
            luaL_openlibs(m_state);
        }

        void LoadFile(const char* filepath)
        {
            int r = luaL_loadfile(m_state, filepath);
            lua_pcall(m_state, 0, LUA_MULTRET, 0);
        }

        LuaTable *CreateTable(const char* tableName)
        {
            return new LuaTable(m_state, tableName);
        }

        template <typename Ret, typename... Args>
        void Register(const char* name, Ret(*func)(Args...))
        {
            new lua::Function<1, Ret, Args...>(m_state, name, func);
            lua_setglobal(m_state, name);
        }

        template <typename... Args>
        void Register(const char* name, void(*func)(Args...))
        {
            new lua::Function<0, void, Args...>(m_state, name, func);
            lua_setglobal(m_state, name);
        }

        template <typename... Args>
        void Call(const char *funcName, const Args&... args)
        {
            int argsCount = sizeof...(args);
            lua_getglobal(m_state, funcName);
            lua::PushToStack(m_state, args...);
            lua_call(m_state, argsCount, 0);
        }

        template <typename Ret, typename... Args>
        Ret Call(const char *funcName, const Args&... args)
        {
            int argsCount = sizeof...(args);
            lua_getglobal(m_state, funcName);
            lua::PushToStack(m_state, args...);
            lua_call(m_state, argsCount, 1);

            Ret x = lua::GetFromStack<Ret>(m_state, -1);
            lua_pop(m_state, 1);

            return x;
        }

        void RegisterRaw(const char* name, lua_CFunction func)
        {
            lua_register(m_state, name, func);
        }

        lua_State* GetState() {
            return m_state;
        }

        ~LuaEnvironment() {
            lua_close(m_state);
        }
    private:
        lua_State * m_state;
    };
}}