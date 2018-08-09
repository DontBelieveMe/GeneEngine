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
			std::size_t LocalOffset;
			Member* Parent;

			template <typename U, typename T>
			void SetValue(U& object, const T& newValue) {
				void* memberData = (gene::byte*)&object + LocalOffset;
				memcpy(memberData, (void*)&newValue, Type->Size);
			}

			template <typename U, typename T>
			U *GetValue(T& object) {
				return GetValueFromVoidPointer<U>(&object);
			}

			template <typename U>
			U *GetValueFromVoidPointer(void*ptr) {
				void* ptr2 = ((gene::byte*) ptr) + LocalOffset;
				return (U*)ptr2;
			}
		};

		struct MetaDataRegistry {
		private:
			template <typename T>
			DataType *FillBasicData(const char* name, size_t size) {
				return PutBasicDataIntoType(GetType<T>(), name, size, std::is_pointer<T>::value, std::is_const<T>::value);
			}

		public:
			static MetaDataRegistry* Get();

			template <typename T>
			DataType* GetType() {
				static DataType t;
				return &t;
			}

			template <typename T>
			DataType* RegisterType(const char* name, size_t size) {
				DataType *type = FillBasicData<T>(name, size);
				m_Types[name] = type;
				return m_Types[name];
			}

			DataType *PutBasicDataIntoType(DataType* type, const char* name, size_t size, bool isPtr, bool isConst);
			void AddMember(DataType* objType, DataType* memberType, const char* memberName, std::size_t offset);
			void Insert(DataType* type);

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

std::ostream &operator<<(std::ostream &os, gene::reflection::DataType* const &m);


#define META_DEFINE_BASIC_START struct __MetaData__ { virtual void Init() {
#define META_DEFINE_BASIC_TYPE(type) gene::reflection::MetaDataRegistry::Get()->RegisterType<type>(#type, sizeof(type));
#define META_DEFINE_BASIC_END  }}; static __MetaData__ __s_metaDataInstance__;

#define META_GET_DATA(type) gene::reflection::MetaDataRegistry::Get()->GetType<type>()

#define META_CLASS_REFLECTED(obj) \
			gene::reflection::DataType* GetType() { return gene::reflection::MetaDataRegistry::Get()->GetType<obj>(); } \
			static void Reflect(); \
			static gene::reflection::TypeRegister<obj> _reflect;

#define META_CLASS_REFLECT_IMPL(obj) \
                                     gene::reflection::TypeRegister<obj> obj::_reflect; \
                                     void obj::Reflect() { \
										typedef obj ObjType; \
                                        auto _meta_obj = gene::reflection::MetaDataRegistry::Get()->RegisterType<obj>(#obj, sizeof(obj));

#define META_CLASS_DECLARE_MEMBER(type, name) gene::reflection::MetaDataRegistry::Get()->AddMember(_meta_obj, META_GET_DATA(type), #name, offsetof(ObjType, name));
#define META_CLASS_DECLARE_METHOD()
#define META_CLASS_END_REFLECT_IMPL() gene::reflection::MetaDataRegistry::Get()->Insert(_meta_obj); } 

#define META_IMPL_FILE(id) void gene::reflection::impl_##id(){[](){}();}
#define META_INCLUDE_IMPL(id) void impl_##id();
#define META_PREP_IMPL(id) gene::reflection::impl_##id();

#include <All.Reflection.inl>