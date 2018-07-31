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

        template <typename TT, typename T>
        TT *FillBasicData(const char* name, size_t size) {
            TT *type = new TT;
            type->Name = name;
            type->Size = size;
            type->IsPointer = std::is_pointer<T>::value;
            type->IsConst = std::is_const<T>::value;
            return type;
        }

        template <typename T>
        DataType* RegisterBasicType(const char* name, size_t size) {
            DataType *type = FillBasicData<DataType, T>(name, size);
            m_Types.insert(std::make_pair(name, type));
            return m_Types[name];
        }

        template <typename T>
        DataType* CreateType(const char* name, size_t size) {
            DataType *type = FillBasicData<DataType, T>(name, size);
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
            m_Types.insert(std::make_pair(type->Name, type));
        }

        DataType *EMPTY_DATA = new DataType;
        
        DataType* GetData(const char* name) {
            DataType* type = m_Types[name];
            bool hasType = m_Types.find(name) != m_Types.end();
            if (!hasType) {
                m_Types[name] = EMPTY_DATA;
            } else {
                if (type == nullptr) 
                    return EMPTY_DATA;
            }
            return type;
        }

        gene::Array<void(*)()> ClassTypeReflectors;

    private:
        gene::HashMap<std::string, DataType*> m_Types;
    };

    void DefaultRegistrations();
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

#define META_GET_DATA(type) meta::MetaDataRegistry::Get()->GetData(#type)

#define META_CLASS_REFLECTED static void Reflect();

#define META_CLASS_REFLECT_IMPL(obj) struct _tmp_ { _tmp_() { meta::MetaDataRegistry::Get()->ClassTypeReflectors.push_back(&obj::Reflect); }}; \
                                      static _tmp_ _t; void obj::Reflect() { auto _meta_obj = meta::MetaDataRegistry::Get()->CreateType<obj>(#obj, sizeof(obj));
#define META_CLASS_MEMBER(type, name) meta::MetaDataRegistry::Get()->AddMember(_meta_obj, META_GET_DATA(type), #name);
#define META_CLASS_END_REFLECT_IMPL() meta::MetaDataRegistry::Get()->Insert(_meta_obj); } 