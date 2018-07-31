#pragma once

#include <Core/Array.h>
#include <iostream>

namespace meta {
    struct Member;

    struct DataType {
        const char* Name;
        size_t Size;
        bool IsPointer;
        bool IsConst;
        gene::Array<Member> Members;

        DataType() :
            Name("<< No datatype available >>"), Size(0), IsPointer(false), IsConst(false) {}
    };

    struct Member {
        const char* Name;
        DataType *Type;
    };

    struct MetaDataRegistry {
        static MetaDataRegistry* Get() {
            static MetaDataRegistry registry;
            return &registry;
        }

        template <typename T>
        DataType* GetType() {
            static DataType t;
            return &t;
        }

        template <typename T>
        DataType *FillBasicData(const char* name, size_t size) {
            DataType *type = GetType<T>();
            type->Name = name;
            type->Size = size;
            type->IsPointer = std::is_pointer<T>::value;
            type->IsConst = std::is_const<T>::value;
            return type;
        }

        template <typename T>
        DataType* RegisterBasicType(const char* name, size_t size) {
            DataType *type = FillBasicData<T>(name, size);
            m_Types[name] = type;
            return m_Types[name];
        }

        template <typename T>
        DataType* CreateType(const char* name, size_t size) {
            DataType *type = FillBasicData<T>(name, size);
            return type;
        }

        void AddMember(DataType* objType, DataType* memberType, const char* memberName)
        {
            Member member;
            member.Name = memberName;
            member.Type = memberType;
            objType->Members.push_back(member);
        }

        void Insert(DataType* type) {
            m_Types[type->Name] = type;
        }

        DataType *EMPTY_DATA = new DataType;

        gene::Array<void(*)()> ClassTypeReflectors;

    private:
        gene::HashMap<std::string, DataType*> m_Types;
    };

    void DefaultRegistrations();
    void LibraryRegistrations();

    template <typename T>
    struct TypeRegister {
        TypeRegister() {
            T::Reflect();
        }
    };
}

inline std::ostream &operator<<(std::ostream &os, meta::DataType* const &m) {
    os << std::boolalpha;
    os << "\nType: " << m->Name << "\n";
    os << "\tSize: " << m->Size << " bytes\n";
    os << "\tIsPointer: " << m->IsPointer << "\n";
    os << "\tIsConst: " << m->IsConst << "\n\n";
    for (meta::Member& member : m->Members)
    {
        os << "\tMember Name: " << member.Name << "\n";
        os << "\t\tMember Type: " << member.Type->Name << "\n";
    }
    return os;
}

#define META_DEFINE_BASIC_START struct __MetaData__ { virtual void Init() {
#define META_DEFINE_BASIC_TYPE(type) meta::MetaDataRegistry::Get()->RegisterBasicType<type>(#type, sizeof(type));
#define META_DEFINE_BASIC_END  }}; static __MetaData__ __s_metaDataInstance__;

#define META_GET_DATA(type) meta::MetaDataRegistry::Get()->GetType<type>()

#define META_CLASS_REFLECTED(obj) static void Reflect(); static meta::TypeRegister<obj> _reflect;

#define __concat(x, y) x##y
#define __concat2(x, y) __concat(x, y)

#define META_CLASS_REFLECT_IMPL(obj) \
                                     meta::TypeRegister<obj> obj::_reflect; \
                                     void obj::Reflect() { \
                                        auto _meta_obj = meta::MetaDataRegistry::Get()->CreateType<obj>(#obj, sizeof(obj));

#define META_CLASS_MEMBER(type, name) meta::MetaDataRegistry::Get()->AddMember(_meta_obj, META_GET_DATA(type), #name);
#define META_CLASS_END_REFLECT_IMPL() meta::MetaDataRegistry::Get()->Insert(_meta_obj); } 

#define META_IMPL_FILE(id) void meta::impl_##id(){[](){}();}
#define META_INCLUDE_IMPL(id) void impl_##id();
#define META_PREP_IMPL(id) meta::impl_##id();

#include <All.Reflection.inl>