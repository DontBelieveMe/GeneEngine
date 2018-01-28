#  OpenGL Function Loader (GLFL) v1.2.2 (generator script)
#  Copyright (C) 2017 Egor Mikhailov <blckcat@inbox.ru>
#
#  This software is provided '"'"'as-is'"'"', without any express or implied
#  warranty.  In no event will the authors be held liable for any damages
#  arising from the use of this software.
#
#  Permission is granted to anyone to use this software for any purpose,
#  including commercial applications, and to alter it and redistribute it
#  freely, subject to the following restrictions:
#
#  1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#  2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#  3. This notice may not be removed or altered from any source distribution.

rm -rf out
mkdir out
mkdir out/GLFL

#    F I L E S
echo 'Preparing files'

# Replace new lines with ~
sed -e ':a' -e 'N' -e '$!ba' -e 's/\n/~/g' gl.xml >out/glxml_
# Remove comments
perl -pi -e 's|<!--.*?-->||g' out/glxml_
perl -pi -e 's|/\*.*?\*/||g' out/glxml_
perl -pi -e 's|<comment>.*?</comment>||g' out/glxml_
# Remove extra spaces and new lines
perl -pi -e 's|>[ \t]*(~?)[ ~\t]*<|>\1<|g' out/glxml_
# Restore new lines
perl -p -e 's|~|\n|g' out/glxml_ >out/glxml


#    T Y P E S
echo 'Parsing types'

# Grep types and remove useless ones
grep -P -o '<type([^s][^>]*)?>.*?</type>' out/glxml_ | grep -P 'name="inttypes"' -v - | grep -P 'khronos_' -v - | grep -P '#include' -v - >out/types
perl -pi -e 's|~|\n|g' out/types
# Remove tags
perl -pi -e 's|<[^>]*>||g' out/types
# Fix formatting
perl -pi -e 's|\( \*|\(\*|g' out/types
perl -pi -e 's|,([A-Za-z])|, \1|g' out/types


#    E N U M E R A T O R S
echo 'Parsing enumerators'

# Grep enumerators and remove duped ones (We are assuming that enumerators with `api=".."` are always dupes (usually from extensions). We remove all such enumerators except ones with `api="gl"`.)
grep -P '<enum .*value' out/glxml | perl -p -e 's|api="gl"||g' - | grep -Pv 'api="' - >out/enumerators
# Convert to defines
perl -pi -e 's/<enum .*?(name|value)="(.*?)".*?(name|value)="(.*?)".*?>/#define \2                                                                                                                      \4/g' out/enumerators
perl -pi -e 's|(-?[0-9][0-9A-Za-z_]*)( +)([A-Za-z_][0-9A-Za-z_]*)|\3\2\1|g' out/enumerators
perl -pi -e 's|(#[0-9A-Za-z_ ]{0,64})([0-9A-Za-z_]*) *(-?[0-9][0-9A-Za-z_]*)|\1\2 \3|g' out/enumerators


#    F U N C T I O N S
echo 'Parsing functions'

# Grep functions
grep -P -o '<command( [^/>]*?|)>.*?</command>' out/glxml_ >out/functions
# Remove disguised new lines
perl -pi -e 's|~||g' out/functions
# Workaround for the spec bug: Sometimes there is `<proto><ptype>BLAH</ptype>` instead of `<proto>BLAH`
perl -pi -e 's|(<proto[^>]*?>[A-Za-z0-9_ *&]*)<ptype[^>]*?>([A-Za-z0-9_ *&]*)</ptype>([A-Za-z0-9_ *&]*<name)|\1\2\3 |g' out/functions
# Workaround for the spec bug: Sometimes there is `<param>BLAH<name>BLAH</name></param>` instead of `<param><ptype>BLAH</ptype><name>BLAH</name></param>`
perl -pi -e 's|(<param[^>]*?>) *([^<]*) *<name|\1<ptype>\2</ptype><name|g' out/functions
# Find function return types and names
perl -pi -e 's|<command[^>]*?> *<proto[^>]*?>([A-Za-z0-9_ *&]*)<name[^>]*?> *([A-Za-z0-9_]*) *</name> *</proto> *|<#\1;\2#><@|g' out/functions
perl -pi -e 's|</command>|@>|g' out/functions
# Find argument types and names
perl -pi -e 's|<param[^>]*?>([A-Za-z0-9_ *&]*)<ptype[^>]*?>([A-Za-z0-9_ *&]*)</ptype>([A-Za-z0-9_ *&]*)<name[^>]*?> *([A-Za-z0-9_]*) *</name>([A-Za-z0-9_ *&[\]]*)</param>|<<\1\2\3;\4;\5>>|g' out/functions
# Remove extra spaces
perl -pi -e 's| *; *|;|g' out/functions
perl -pi -e 's|<([#@<]) *|<\1|g' out/functions
perl -pi -e 's| *([#@>])>|\1>|g' out/functions
# Remove useless tags
perl -pi -e 's|</?vecequiv[^>]*?>||g' out/functions
perl -pi -e 's|</?alias[^>]*?>||g' out/functions
perl -pi -e 's|</?glx[^>]*?>||g' out/functions
# Insert commas
perl -pi -e 's|>><<|>>,<<|g' out/functions


#    V E R S I O N S
echo 'Parsing versions'

# Grep versions
grep -Po '<feature( [^/>]*?|)>.*?</feature>' out/glxml_ | \
# Remove disguised new lines
perl -pe 's|~||g' | \
# Find names
perl -pe 's|<feature[^>]*api *= *"(.*?)([0-9]*)"[^>]*number *= *"([0-9]*?\.[0-9]*?)"[^>]*>|<#\1;\1\2;\3#><@|g' | \
perl -pe 's|</?feature[^>]*?>|@>|g' | \
# Remove useless tags
perl -pe 's|<remove[^>]*?>.*?</remove>||g' | \
perl -pe 's|</?enum[^>]*?>||g' | \
perl -pe 's|</?type[^>]*?>||g' | \
perl -pe 's|</?require[^>]*?>||g' | \
# Find function names
perl -pe 's|<command [^>]*?name *= *"([^"]*)"[^>]*?>|<<\1>>,|g' | \
perl -pe 's|,@>|@>|g' | \
# Sort
sort - >out/versions


#    E X T E N S I O N S
echo 'Parsing extensions'

# Grep extensions
grep -P -o '<extension [^>]*?([^/]>.*?</extension>|/>)' out/glxml_ >out/extensions
# Remove disguised new lines
perl -pi -e 's|~||g' out/extensions
# Find names
perl -pi -e 's|<extension[^>]*?name *= *"([^"]*)"[^>]*?supported *= *"([^"]*)"[^>]*?/>|<#\1;\2#><@@>|g' out/extensions
perl -pi -e 's|<extension[^>]*?name *= *"([^"]*)"[^>]*?supported *= *"([^"]*)"[^>]*>|<#\1;\2#><@|g' out/extensions
perl -pi -e 's|</extension>|@>|g' out/extensions
# Remove useless tags
perl -pi -e 's|</?enum[^>]*?>||g' out/extensions
perl -pi -e 's|</?type[^>]*?>||g' out/extensions
perl -pi -e 's|</?require[^>]*?>||g' out/extensions
# Find function names
perl -pi -e 's|<command [^>]*?name *= *"([^"]*)"[^>]*?>|<<\1>>,|g' out/extensions
perl -pi -e 's|,@>|@>|g' out/extensions




#    G L F L . H
echo 'Generating glfl.h'

echo >out/GLFL/glfl.h \
"___LICENSE_TEXT_HERE___

#ifndef GLFL_H_INCLUDED
#define GLFL_H_INCLUDED

#include <cstddef>
#include <cstdint>

#ifdef GLFL_ENABLE_PROXY
#include <iostream>
#include <string>
#include <type_traits>
#include <cstdlib>
#endif


/* -- HOW TO USE --
 *
 * Create your window and context. Then do:
 *
 *     glfl::set_function_loader(..);
 *     glfl::load_*(..);
 *
 * After that you can call OpenGL functions.
 *
 * If you have multiple GL windows, you should first do following:
 *
 *     glfl::context my_context;
 *     glfl::set_context(my_context);
 *
 * \`glfl::set_context(..)\` determines which context is affected by \`glfl::load_*()\` and other functions.
 * When you call \`gl*()\` functions, pointers from the active context are used.
 *
 * There is a special \`0\` context which is active by default (you should use it if you have only one window).
 *
 *
 * To enable function hooking (intercepting calls), define GLFL_ENABLE_PROXY prior to inclusion of this header.
 * This macro is checked only at first inclusion.
 *
 * By default call hook will log all OpenGL calls.
 * It has some settings which are described below.
 *
 * You can provide a custom hook by defining GLFL_PROXY_NAME as a name of a proxy class.
 * The interface such class must provide is not documented. Default proxy implementation is located in glfl_proxy_proto__.h.
 *
 */

/* -- CALLING CONVENTIONS --
 *
 * All GL function pointers must be labeled as GLFL_API to enforce a proper calling convention.
 *
 *     void GLFL_API func(int x) {...}
 *
 *     void (GLFL_API *ptr)(int) = func;
 *
 * \`GLFL_API\` is defined as \`APIENTRY\` or \`__stdcall\` or \`\` (nothing) if it was not already defined by user prior to inclusion of this header.
 * Pointers from glfl::context, as well as optional fake (proxy) functions are labeled as GLFL_API.
 *
 */


#ifndef GLFL_API
// This logic was copied from GLEW.
#  ifdef APIENTRY
#    define GLFL_API APIENTRY
#  else
#    if defined(__MINGW32__) || defined(__CYGWIN__) || (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#      define GLFL_API __stdcall
#    else
#      define GLFL_API
#    endif
#  endif
#endif

"
cat out/types >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
"

#if __cplusplus >= 201700L
#  define GLFL_CPP17(...) __VA_ARGS__
#else
#  define GLFL_CPP17(...)
#endif

#define GLFL_NODISCARD   GLFL_CPP17([[nodiscard]])
#define GLFL_FALLTHROUGH GLFL_CPP17([[fallthrough]];)


namespace glfl
{
    struct context;

    /* Returns a pointer to the current context.
     * There is a default context which is active by default.
     * If \`set_active_context()\` wasn't called yet and the default context
     * wasn't used in any way, this function returns 0. */
    GLFL_NODISCARD const context *active_context();

    /* Makes a context active.
     * set_active_context(0) activates the default context. */
    void set_active_context(context *);

    /* A special function for getting OpenGL function addresses should be provided by your window creating library. */
    using function_loader_t = void *(*)(const char *);
    void set_function_loader(function_loader_t);

    /* Holds loaded function pointers. */
    struct context
    {"
echo >>out/GLFL/glfl.h -e "        void *ptrs["`echo '.' | cat out/functions - | grep -Pc '^.' -`"] {};"
echo >>out/GLFL/glfl.h \
"
        function_loader_t function_loader = 0;

        ~context()
        {
            if (this == active_context())
                set_active_context(0);
        }
    };

    /* Load all standard functions. */
    void load_all_versions();
    /* Load all standard functions and all extensions. */
    void load_everything();

    /* Load OpenGL versions.
     * Specifying an incorrect major+minor combinaton will load the newest version. */"
grep -Po '<#[^;]*;' out/versions | uniq | perl -p -e 's|<#([^;]*);|    void load_\1(int major, int minor);\n    void load_\1();|g' - >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
"
    /* The interface of the default (logging) proxy.
     * Functions below have no effect if it's disabled. You may reuse the interface for your own proxy. */
    namespace proxy
    {
        /* Functions marked as 'internal' should only be used in the implementation of the proxy.
         * Calls to functions marked 'msg' are logged unless the message callback is disabled; see below. */

        /* If enabled, \`glGetError()\` is called after each OpenGL function call except itself.
         * Enabled by default. */
        /*msg*/ void check_errors(bool);
        GLFL_NODISCARD bool check_errors();

        /* If enabled with \`check_errors\`, the program will be terminated
         * if the automatic call to \`glGetError\` reports any errors.
         * Enabled by default. */
        /*msg*/ void stop_on_errors(bool);
        GLFL_NODISCARD bool stop_on_errors();

        /* If enabled, all strings passed to GL functions are printed.
         * Otherwise they are printed as pointers.
         * Disabled by default. */
        /*msg*/ void print_string_arguments(bool);
        GLFL_NODISCARD bool print_string_arguments();


        /* Disable 'print' callback.
         * Since default 'message' and 'error' callbacks use \`print()\`, they won't print anything too. */
        /*msg*/ void disable_logging(bool);

        /* Disable 'message' callback. */
        void disable_messages(bool);


        using print_function_t = void (*)(const char *);

        /* Sets a callback for logging.
         * It has to add '\n' at the end of the string.
         * The default implementation is \`std::puts()\` (wrapped into a lambda). */
        void set_print_function(print_function_t);

        /* Calls the above callback. */
        void print(const char *);

        /* Similar to \`set_print_function\` but the string should be visually emphasized somehow.
         * The default implementation uses \`print()\`, so you don't have to override it separately.
         * The default implementation also appends '\n' to the beginning of the string; you probably should do the same. */
        void set_message_function(print_function_t);

        /* Calls the above callback. */
        void message(const char *);

        /* Similar to \`set_print_function\` but the string should be visually emphasized as error.
         * The default implementation uses \`print()\`, so you don't have to override it separately.
         * The default implementation also appends '\n' to the beginning of the string; you probably should do the same. */
        void set_error_function(print_function_t);

        /* Calls the above callback.
         * Then, if \`stop_on_errors\` is set, stops the program. */
        void error(const char *);


        /* This is incremented each time a GL function is called.
         * The default value is 0. Feel free to reset it. */
        GLFL_NODISCARD unsigned long long draw_call_count();
        /*msg*/ void reset_draw_call_count();
        /*internal*/ void incr_draw_call_count();


        /* The location of the last call.
         * Note that the actual call locations are not registered.
         * Rather, the last location where a function name was used is saved.
         * The difference is only noticeable when using function pointers. */
        GLFL_NODISCARD int line();
        GLFL_NODISCARD const char *file();
        /*internal*/ void location(const char *file, int line);
        /*internal*/ GLFL_NODISCARD bool line_changed(); // Calling this function resets the flag.
        /*internal*/ GLFL_NODISCARD bool file_changed(); // Calling this function resets the flag.


        /*internal*/ constexpr int index_of_glGetError = ___INDEX_OF_GLGETERROR___;
        /*internal*/ using type_of_glGetError = ___TYPE_OF_GLGETERROR___;


        /*internal*/
        struct function_info
        {
            enum class type {other, enumeration, boolean, bitfield};
            const char *name;
            const char *const *param_names;
            type return_type;
            const type *param_types;
        };

        /*internal*/ GLFL_NODISCARD const function_info &get_function_info(int index);
    }

"
grep -Pn 'glGetError#' out/functions | perl -pe 's|^([^:]*).*$|perl -pi -e "s/___INDEX_OF_GLGETERROR___/\1/g" out/GLFL/glfl.h|g' | source /dev/stdin
grep -P 'glGetError#' out/functions | perl -pe 's|<#([^;]*);[^#]*#><@([^@]*)@>|perl -pi -e "s/___TYPE_OF_GLGETERROR___/\1 (GLFL_API *)(\2)/g" out/GLFL/glfl.h|g' | \
perl -pe 's|>>,<<|>>, <<|g' | perl -pe 's|<<([^;]*);[^;]*;([^>]*)>>|\1\2|g' | source /dev/stdin
echo >>out/GLFL/glfl.h '    /* Load extensions. */'
perl -p -e 's|<#([^;]*);([^#]*)#><@[^@]*@>|    void load_extension_\1(); // \2|g' out/extensions >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
'}
'

cat out/enumerators >>out/GLFL/glfl.h
echo >>out/GLFL/glfl.h \
'
#ifdef GLFL_ENABLE_PROXY
#  include "glfl_proxy_proto__.h"
#else
#  include "glfl_simple_proto__.h"
#endif

#endif'


#    G L F L _ _ S I M P L E _ P R O T O _ _ . H
echo 'Generating glfl_simple_proto__.h'

echo >out/GLFL/glfl_simple_proto__.h \
'___LICENSE_TEXT_HERE___
'
cat -n out/functions | \
perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);([^#]*)#><@([^@]*)@>|#define \3                                                                     =(void(), (\2 (GLFL_API *)(\4))::glfl::active_context()->ptrs[\1])|g' | \
perl -pe 's|(#[0-9A-Za-z_(), ]{0,64})([0-9A-Za-z_(),]*) *=(.*)$|\1\2 \3|g' | perl -pe 's|<<([^;]*);[^;]*;([^>]*)>>|\1\2|g' >>out/GLFL/glfl_simple_proto__.h


#    G L F L _ P R O X Y _ P R O T O _ _ . H
echo 'Generating glfl_proxy_proto__.h'

echo >out/GLFL/glfl_proxy_proto__.h \
'___LICENSE_TEXT_HERE___

#ifndef GLFL_PROXY_NAME
#  define GLFL_PROXY_NAME ::glfl::proxy::impl::default_proxy
#endif

namespace glfl
{
    namespace proxy
    {
        namespace impl
        {
            template <typename T> std::enable_if_t<std::is_arithmetic<T>::value, std::string> to_string(T obj)
            {
                return std::to_string(obj);
            }
            template <typename T> std::enable_if_t<std::is_pointer<T>::value, std::string> to_string(T obj)
            {
                if (obj == 0)
                    return "0x0 (0)";
                std::string ret;
                uintptr_t n = uintptr_t(obj);
                while (n)
                {
                    ret = ("0123456789abcdef"[n % 16]) + ret;
                    n /= 16;
                }
                return "0x" + ret + " (" + std::to_string(uintptr_t(obj)) + ")";
            }
            inline std::string to_string(const char *obj)
            {
                if (print_string_arguments())
                    return std::string("\"") + obj + "\"";
                else
                    return to_string<const void *>(obj);
            }

            template <typename T> std::string bool_to_string(T obj)
            {
                return (obj ? "true" : "false");
            }
            template <typename T> std::string enum_to_string(T obj)
            {
                if (obj == 0)
                    return "0x0 (0)";
                std::string ret;
                uintptr_t n = uintptr_t(obj);
                while (n)
                {
                    ret = ("0123456789abcdef"[n % 16]) + ret;
                    n /= 16;
                }
                ret = "0x" + ret;
                if (int(obj) < 0)
                    ret += " (" + std::to_string(int(obj)) + ")";
                return ret;
            }
            template <typename T> std::string bitfield_to_string(T obj)
            {
                if (obj == 0)
                    return "0x0";
                std::string ret;
                uintptr_t n = uintptr_t(obj);
                while (n)
                {
                    ret = ("0123456789abcdef"[n % 16]) + ret;
                    n /= 16;
                }
                return "0x" + ret;
            }

            template <typename T> std::string to_string(T obj, const function_info::type &type)
            {
                switch (type)
                {
                    case function_info::type::enumeration: return enum_to_string(obj);
                    case function_info::type::boolean    : return bool_to_string(obj);
                    case function_info::type::bitfield   : return bitfield_to_string(obj);
                    default:                               return impl::to_string(obj);
                }
            }

            inline void errors()
            {
                if (!check_errors() || active_context()->ptrs[index_of_glGetError] == 0)
                    return;

                std::string message;
                GLenum value;
                while ((value = type_of_glGetError(active_context()->ptrs[index_of_glGetError])()) != 0)
                {
                    if (message.size())
                        message += ", ";
                    switch (value)
                    {
                        case GL_INVALID_ENUM:                  message += "INVALID ENUM";                  break;
                        case GL_INVALID_VALUE:                 message += "INVALID VALUE";                 break;
                        case GL_INVALID_OPERATION:             message += "INVALID OPERATION";             break;
                        case GL_INVALID_FRAMEBUFFER_OPERATION: message += "INVALID FRAMEBUFFER OPERATION"; break;
                        case GL_OUT_OF_MEMORY:                 message += "OUT OF MEMORY";                 break;
                        case GL_STACK_UNDERFLOW:               message += "STACK UNDERFLOW";               break;
                        case GL_STACK_OVERFLOW:                message += "STACK OVERFLOW";                break;
                        default:                               message += "UNKNOWN";                       break;
                    }
                }
                if (message.size())
                {
                    error(("OPENGL ERROR: " + message).c_str());
                }
            }

            inline void print_location()
            {
                bool new_line = line_changed();
                bool new_file = file_changed();

                if (new_line || new_file)
                {
                    if (new_file)
                        print(file());

                    print(std::to_string(line()).c_str());
                }
            }

            inline void print_name(int index)
            {
                const auto &info = get_function_info(index);
                print((std::string("    ") + info.name).c_str());
            }

            template <typename ...P> void print_params(int index, const P &... params)
            {
                (void)index;
                using dummy_array = int[];
                int pos = 0;
                dummy_array{0, (print((std::string("        ") + get_function_info(index).param_names[pos] + " = " + to_string(params, get_function_info(index).param_types[pos])).c_str()), pos++, 0)...};
            }

            template <typename T> void print_result(int index, const T &value)
            {
                print(("         -> " + to_string(value, get_function_info(index).return_type)).c_str());
            }

            template <int Index, typename ReturnType, typename ...ParamTypes>
            struct default_proxy
            {
                static ReturnType GLFL_API func(ParamTypes ... args)
                {
                    print("");
                    print_location();
                    print_name(Index);
                    print_params(Index, args...);

                    if (active_context()->ptrs[Index] && active_context()->ptrs[Index] != active_context()->ptrs[0])
                    {
                        ReturnType ret = ((ReturnType (GLFL_API *)(ParamTypes...))active_context()->ptrs[Index])(args...);
                        print_result(Index, ret);
                        errors();
                        incr_draw_call_count();
                        return ret;
                    }
                    else
                    {
                        error("FUNCTION NOT LOADED");
                        return {};
                    }
                }
            };

            template <int Index, typename ...ParamTypes>
            struct default_proxy<Index, void, ParamTypes...>
            {
                static void GLFL_API func(ParamTypes ... args)
                {
                    print("");
                    print_location();
                    print_name(Index);
                    print_params(Index, args...);

                    if (active_context()->ptrs[Index] && active_context()->ptrs[Index] != active_context()->ptrs[0])
                    {
                        ((void (GLFL_API *)(ParamTypes...))active_context()->ptrs[Index])(args...);
                        errors();
                        incr_draw_call_count();
                    }
                    else
                        error("NOT LOADED");
                }
            };
        }
    }
}

'
cat -n out/functions | \
perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);gl([^#]*)#><@([^@]*)@>|#define gl\3                                                                     =(void(0), ::glfl::proxy::location(__FILE__, __LINE__), GLFL_PROXY_NAME<\1,\2,\4>::func)|g' | \
perl -pe 's|(#[0-9A-Za-z_(), ]{0,64})([0-9A-Za-z_(),]*) *=(.*)$|\1\2 \3|g' | perl -pe 's|<<([^;]*);[^;]*;([^>]*)>>|\1\2|g' | perl -pe 's|,>|>|g' >>out/GLFL/glfl_proxy_proto__.h


#    G L F L _ F U N C _ I N D I C E S . H
echo 'Generating glfl_func_indices.h'

echo >out/GLFL/glfl_func_indices.h \
'___LICENSE_TEXT_HERE___

#ifndef GLFL_FUNC_INDICES_H_INCLUDED
#define GLFL_FUNC_INDICES_H_INCLUDED

namespace glfl
{
    namespace indices
    {
        constexpr int invalid = 0;'
cat -n out/functions | perl -pe 's|[\t ]*([0-9]*)[\t ]*<#[^;]*;gl([^#]*)#><@[^@]*@>|        constexpr int \2 = \1;|g' >>out/GLFL/glfl_func_indices.h
echo >>out/GLFL/glfl_func_indices.h \
'    }
}

#endif'


#    G L F L . C P P
echo 'Generating glfl.cpp'

echo >out/glfl.cpp \
'___LICENSE_TEXT_HERE___

#include "GLFL/glfl.h"
#include "GLFL/glfl_func_indices.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>


namespace glfl
{
    static context *current_context = 0, *default_context = 0;

    static void make_sure_context_exists()
    {
        if (current_context == 0)
        {
            current_context = default_context = new context;
        }
    }

    const context *active_context()
    {
        return current_context;
    }
    void set_active_context(context *c)
    {
        current_context = c;
        make_sure_context_exists();
    }
    void set_function_loader(function_loader_t ptr)
    {
        make_sure_context_exists();
        current_context->function_loader = ptr;
        current_context->ptrs[0] = current_context->function_loader("meow");
    }

    namespace proxy
    {
        static print_function_t print_func   = [](const char *str){std::puts(str);},
                                message_func = [](const char *str){print(('"'"'\n'"'"' + std::string(60, '"'"'-'"'"') + '"'"'\n'"'"' + std::string(6, '"'"' '"'"') + str + '"'"'\n'"'"' + std::string(60, '"'"'-'"'"')).c_str());},
                                error_func   = [](const char *str){print(('"'"'\n'"'"' + std::string(60, '"'"'='"'"') + '"'"'\n'"'"' + std::string(6, '"'"' '"'"') + str + '"'"'\n'"'"' + std::string(60, '"'"'='"'"')).c_str());};
        static bool logging_enabled = 1,
                    messages_enabled = 1;

        static void toggle_feature(const char *name, bool &cur_value, bool new_value)
        {
            if (cur_value != new_value)
            {
                if (&cur_value == &logging_enabled)
                    logging_enabled = 1;
                message((std::string(name) + (new_value ? " - enabled" : " - disabled")).c_str());
                cur_value = new_value;
            }
        }


        static bool call_glgeterror = 1;
        void check_errors(bool x)
        {
            toggle_feature("Checking GL errors", call_glgeterror, x);
        }
        bool check_errors()
        {
            return call_glgeterror;
        }

        static bool exit_on_error = 1;
        void stop_on_errors(bool x)
        {
            toggle_feature("Stopping on GL errors", exit_on_error, x);
        }
        bool stop_on_errors()
        {
            return exit_on_error;
        }

        static bool print_str_args = 0;
        void print_string_arguments(bool x)
        {
            toggle_feature("Printing string arguments", print_str_args, x);
        }
        bool print_string_arguments()
        {
            return print_str_args;
        }


        void disable_logging(bool x)
        {
            toggle_feature("Logging", logging_enabled, !x);
        }
        void disable_messages(bool x)
        {
            messages_enabled = !x; // Sic! No \`toggle_feature()\`.
        }

        void set_print_function(print_function_t ptr)
        {
            print_func = ptr;
        }
        void print(const char *str)
        {
            if (!logging_enabled)
                return;
            print_func(str);
        }
        void set_message_function(print_function_t ptr)
        {
            message_func = ptr;
        }
        void message(const char *str)
        {
            if (!messages_enabled)
                return;
            message_func(str);
        }
        void set_error_function(print_function_t ptr)
        {
            error_func = ptr;
        }
        void error(const char *str)
        {
            error_func(str);
            if (stop_on_errors())
            {
                message("Stop");
                std::exit(1);
            }
        }


        static unsigned long long draw_calls = 0;

        unsigned long long draw_call_count()
        {
            return draw_calls;
        }
        void reset_draw_call_count()
        {
            if (draw_calls != 0)
                message(("Draw calls == " + std::to_string(draw_calls)).c_str());
            draw_calls = 0;
        }
        void incr_draw_call_count()
        {
            draw_calls++;
        }


        static int cur_line = 0, last_line = 0;
        static const char *cur_file = "", *last_file = "";
        int line()
        {
            return cur_line;
        }
        const char *file()
        {
            return cur_file;
        }
        void location(const char *file, int line)
        {
            cur_line = line;
            cur_file = file;
        }
        bool line_changed()
        {
            if (cur_line != last_line)
            {
                last_line = cur_line;
                return 1;
            }
            else
                return 0;
        }
        bool file_changed()
        {
            if (std::strcmp(cur_file, last_file))
            {
                last_file = cur_file;
                return 1;
            }
            else
                return 0;
        }
    }

    void load_all_versions()
    {'
grep -Po '<#[^;]*;' out/versions | uniq | perl -p -e 's|<#([^;]*);|        load_\1();|g' - >>out/glfl.cpp
echo >>out/glfl.cpp \
'    }

    void load_everything()
    {
        load_all_versions();'
perl -p -e 's|<#([^;]*);[^#]*#><@[^@]*@>|        load_extension_\1();|g' out/extensions >>out/glfl.cpp
echo >>out/glfl.cpp \
'    }

    #define GLFL_LOAD_FUNCTION(name) ((context *)(active_context()))->ptrs[indices::name] = active_context()->function_loader("gl" #name);
'
grep -Po '<#[^;]*;[^;]*;[^#]*#>' out/versions | \
perl -p -e 's|<#[^;]*;([^;]*);[^#]*#>|\1|g' | \
uniq | \
perl -p -e 's~^(.*)$~echo "    void load_version_\1(int major, int minor)
    {
        major &= 0xffff;
        minor &= 0xffff;
        switch (0x10000 * major + minor)
        {
          default:" >>out/glfl.cpp
grep -P ";\1;" out/versions | tac >>out/glfl.cpp
echo "        }\n    }" >>out/glfl.cpp
perl -pi -e "s/<#[^;]*;[^;]*;([^.]*)\.([^#]*)#><@/          GLFL_FALLTHROUGH\n          case 0x10000 * \\1 + \\2:\n/g" out/glfl.cpp
perl -pi -e "s/<<gl([^>]*)>>,/            GLFL_LOAD_FUNCTION(\\1);\n/g" out/glfl.cpp
perl -pi -e "s/<<gl([^>]*)>>/            GLFL_LOAD_FUNCTION(\\1);/g" out/glfl.cpp
perl -pi -e "s/@>//g" out/glfl.cpp~g' | source /dev/stdin
echo >>out/glfl.cpp ''

grep -Po '#[^;]*;' out/versions | uniq | \
perl -pe 's~#([^;]*);~echo "<##tab##>void load_\1(int major, int minor)<##lf##><##tab##>{<##lf##>" | xargs echo -n >>out/glfl.cpp
grep -Po "<#\1;[^;]*;" out/versions | uniq | perl -pe "s&<#([^;]*);([^;]*);&grep -Po -m1 \\"<#\\1;\\2;[^#]*#>\\" out/versions | perl -pe \\"s:<#[^;]*;[^;]*;([^.]*)\\.([^#]*)#>:<##tab##><##tab##>if (0x10000 * major + minor >= 0x10000 * \\\\\\\\1 + \\\\\\\\2 \\&\\& :g\\" | xargs echo -n >>out/glfl.cpp
tac out/versions | grep -Po -m1 \\"<#\\1;\\2;[^#]*#>\\" - | perl -pe \\"s:<#[^;]*;[^;]*;([^.]*)\\.([^#]*)#>:\<##space##>0x10000 * major + minor <= 0x10000 * \\\\\\\\1 + \\\\\\\\2)<##lf##><##tab##><##tab##>{<##lf##><##tab##><##tab##><##tab##>load_version_\\\\2(major, minor);<##lf##><##tab##><##tab##><##tab##>return;<##lf##><##tab##><##tab##>}<##lf##>:g\\" | xargs echo -n >>out/glfl.cpp&g" | source /dev/stdin
tac out/versions | grep -Po -m1 \"<#\1;([^;]*);\" - | perl -pe \"s&<#[^;]*;([^;]*);&<##tab##><##tab##>load_version_\\1(major, minor);<##lf##>&g\" | xargs echo -n >>out/glfl.cpp
echo "<##tab##>}<##lf##><##tab##>void load_\1()<##space##>{load_\1(-1,-1);}<##lf##>" >>out/glfl.cpp~g' | source /dev/stdin
perl -pi -e 's|<##space##>| |g' out/glfl.cpp
perl -pi -e 's|if \([^)]*\)<##lf##><##tab##><##tab##>\{[^}]*\}<##lf##><##tab##><##tab##>(load_version_[^(]*\(major, minor\);)|\1|g' out/glfl.cpp
perl -pi -e 's|if \(0x10000 \* major \+ minor >= 0x10000 \* ([^ ]*) \+ ([^ ]*) && 0x10000 \* major \+ minor <= 0x10000 \* \1 \+ \2\)|if (major == \1 && minor == \2)|g' out/glfl.cpp
perl -pi -e 's|<##tab##>|    |g' out/glfl.cpp
perl -pi -e 's|<##lf##>|\n|g' out/glfl.cpp
echo >>out/glfl.cpp ''

perl -pe 's|<#([^;]*);[^#]*#><@@>|    void load_extension_\1() {}|g' out/extensions >>out/glfl.cpp
perl -pi -e 's|<#([^;]*);[^#]*#><@([^@]*)@>|    void load_extension_\1()\n    {\n\2    }|g' out/glfl.cpp
perl -pi -e 's|>>,<<|>><<|g' out/glfl.cpp
perl -pi -e 's|<<gl([^>]*)>>|        GLFL_LOAD_FUNCTION(\1);\n|g' out/glfl.cpp

echo >>out/glfl.cpp '
    namespace proxy
    {
        const function_info &get_function_info(int index)
        {
            static constexpr const char *pnames0[] {""};'
cat -n out/functions | perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);([^#]*)#><@([^@]*)@>|            static constexpr const char *pnames\1\[\] {\4};|g' | \
perl -pe 's|<<[^;]*;([^;]*);[^>]*>>|"\1"|g' | perl -pe 's|\[\] \{\};|[] {""};|g' | perl -pe 's|","|", "|g' >>out/glfl.cpp
echo >>out/glfl.cpp '
            using e = function_info::type;
            static constexpr function_info::type ptypes0[] {e::other};'
cat -n out/functions | perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);([^#]*)#><@([^@]*)@>|            static constexpr e ptypes\1\[\] {\4};|g' | perl -pe 's|>>,<<|>>, <<|g' | \
perl -pe 's|<<GLenum;[^;]*;>>|e::enumeration|g' | perl -pe 's|<<GLbitfield;[^;]*;>>|e::bitfield|g' | perl -pe 's|<<GLboolean;[^;]*;>>|e::boolean|g' | \
perl -pe 's|<<[^>]*>>|e::other|g' | perl -pe 's|\[\] \{\};|[] {e::other};|g' >>out/glfl.cpp
echo >>out/glfl.cpp '
            static constexpr function_info ret[]
            {
                {"<null>", pnames0, e::other, ptypes0},'
cat -n out/functions | perl -pe 's|[\t ]*([0-9]*)[\t ]*<#([^;]*);([^#]*)#><@([^@]*)@>|                {"\3", pnames\1, <<\2;;>>, ptypes\1},|g' | \
perl -pe 's|<<GLenum;[^;]*;>>|e::enumeration|g' | perl -pe 's|<<GLbitfield;[^;]*;>>|e::bitfield|g' | perl -pe 's|<<GLboolean;[^;]*;>>|e::boolean|g' | \
perl -pe 's|<<[^>]*>>|e::other|g' >>out/glfl.cpp
echo >>out/glfl.cpp '            };
            return ret[index];
        }
    }
}'


# License
cd out
find -regextype posix-extended -regex '.*\.(h|cpp)' -exec perl -pi -e 's|___LICENSE_TEXT_HERE___|/*
  OpenGL Function Loader (GLFL) v1.2.2
  Copyright (C) 2017 Egor Mikhailov <blckcat\@inbox.ru>

  This software is provided '"'"'as-is'"'"', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/|g' {} \;
cd ..


# Remove temporary files
rm -f out/*.bak
rm -f out/GLFL/*.bak
rm -f out/glxml
rm -f out/glxml_
