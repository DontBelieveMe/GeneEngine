#pragma once

#include <Core/Array.h>
#include <GeneCommon.h>
#include <iostream>

namespace gene {
	namespace reflection {
		struct Member;

		struct DataType {
			const char*				Name;
			size_t					Size;
			bool					IsPointer;
			bool					IsConst;
			gene::Array<Member>		Members;
			std::size_t				Id;


			Member*					GetMemberByName(const char* memberName);

			DataType();
		};

		struct Member {
			const char* Name;
			DataType *Type;
			std::size_t Offset;

			template <typename U, typename T>
			void SetValue(U& object, const T& newValue) {
				void* memberData = (gene::byte*)&object + Offset;
				memcpy(memberData, (void*)&newValue, Type->Size);
			}

			template <typename U, typename T>
			U *GetValue(T& object) {
				return GetValueFromVoidPointer<U>(&object);
			}

			template <typename U>
			U *GetValueFromVoidPointer(void*ptr) {
				void* ptr2 = ((gene::byte*) ptr) + Offset;
				return (U*)ptr2;
			}
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

			DataType *PutBasicDataIntoType(DataType* type, const char* name, size_t size, bool isPtr, bool isConst);

			template <typename T>
			DataType *FillBasicData(const char* name, size_t size) {
				return PutBasicDataIntoType(GetType<T>(), name, size, std::is_pointer<T>::value, std::is_const<T>::value);
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

			void AddMember(DataType* objType, DataType* memberType, const char* memberName, std::size_t offset);

			void Insert(DataType* type) {
				m_Types[type->Name] = type;
			}

			DataType *EMPTY_DATA = new DataType;

			static void DefaultRegistrations();
		private:
			gene::HashMap<std::string, DataType*> m_Types;
		};

		void LibraryRegistrations();

		template <typename T>
		struct TypeRegister {
			TypeRegister() {
				T::Reflect();
			}
		};
	}
}

inline std::ostream &operator<<(std::ostream &os, gene::reflection::DataType* const &m) {
    os << std::boolalpha;
    os << "\nType: " << m->Name << "\n";
    os << "\tSize: " << m->Size << " bytes\n";
    os << "\tIsPointer: " << m->IsPointer << "\n";
    os << "\tIsConst: " << m->IsConst << "\n\n";
    for (gene::reflection::Member& member : m->Members)
    {
        os << "\tMember Name: " << member.Name << "\n";
        os << "\t\tMember Type: " << member.Type->Name << "\n";
    }
    return os;
}

#define META_DEFINE_BASIC_START struct __MetaData__ { virtual void Init() {
#define META_DEFINE_BASIC_TYPE(type) gene::reflection::MetaDataRegistry::Get()->RegisterBasicType<type>(#type, sizeof(type));
#define META_DEFINE_BASIC_END  }}; static __MetaData__ __s_metaDataInstance__;

#define META_GET_DATA(type) gene::reflection::MetaDataRegistry::Get()->GetType<type>()

#define META_CLASS_REFLECTED(obj) static void Reflect(); static gene::reflection::TypeRegister<obj> _reflect;

#define __concat(x, y) x##y
#define __concat2(x, y) __concat(x, y)

#define META_CLASS_REFLECT_IMPL(obj) \
                                     gene::reflection::TypeRegister<obj> obj::_reflect; \
                                     void obj::Reflect() { \
										typedef obj ObjType; \
                                        auto _meta_obj = gene::reflection::MetaDataRegistry::Get()->CreateType<obj>(#obj, sizeof(obj));

#define META_CLASS_DECLARE_MEMBER(type, name) gene::reflection::MetaDataRegistry::Get()->AddMember(_meta_obj, META_GET_DATA(type), #name, offsetof(ObjType, name));
#define META_CLASS_DECLARE_METHOD()
#define META_CLASS_END_REFLECT_IMPL() gene::reflection::MetaDataRegistry::Get()->Insert(_meta_obj); } 

#define META_IMPL_FILE(id) void gene::reflection::impl_##id(){[](){}();}
#define META_INCLUDE_IMPL(id) void impl_##id();
#define META_PREP_IMPL(id) gene::reflection::impl_##id();

#include <All.Reflection.inl>