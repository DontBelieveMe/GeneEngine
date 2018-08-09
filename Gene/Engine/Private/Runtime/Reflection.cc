#include <Runtime/Reflection.h>

META_DEFINE_BASIC_START
    META_DEFINE_BASIC_TYPE(char)
    META_DEFINE_BASIC_TYPE(signed char)
    META_DEFINE_BASIC_TYPE(unsigned char)

    META_DEFINE_BASIC_TYPE(int)
    META_DEFINE_BASIC_TYPE(signed int)
    META_DEFINE_BASIC_TYPE(unsigned int)
    META_DEFINE_BASIC_TYPE(unsigned)

    META_DEFINE_BASIC_TYPE(short int)
    META_DEFINE_BASIC_TYPE(unsigned short int)
    META_DEFINE_BASIC_TYPE(signed short int)
    META_DEFINE_BASIC_TYPE(short)

    META_DEFINE_BASIC_TYPE(float)
    META_DEFINE_BASIC_TYPE(double)
    META_DEFINE_BASIC_TYPE(long double)
    
    META_DEFINE_BASIC_TYPE(bool)
    
    META_DEFINE_BASIC_TYPE(long)
    META_DEFINE_BASIC_TYPE(long int)
    META_DEFINE_BASIC_TYPE(signed long int)
    META_DEFINE_BASIC_TYPE(unsigned long int)
    META_DEFINE_BASIC_TYPE(long long)

    META_DEFINE_BASIC_TYPE(wchar_t)
META_DEFINE_BASIC_END

using namespace gene::reflection;

void MetaDataRegistry::DefaultRegistrations()
{
	__s_metaDataInstance__.Init();
	LibraryRegistrations();
}

DataType::DataType() :
	Name("<< No datatype available >>"), Size(0), IsPointer(false), IsConst(false)
{}

Member *DataType::GetMemberByName(const char* memberName)
{
	for (Member& member : Members) {
		if (strcmp(member.Name, memberName) == 0) return &member;
	}

	return nullptr;
}

DataType* MetaDataRegistry::PutBasicDataIntoType(DataType* type, const char* name, size_t size, bool isPtr, bool isConst)
{
	type->Name = name;
	type->Size = size;
	type->IsPointer = isPtr;
	type->IsConst = isConst;
	type->Id = std::hash<std::string>{}(name);
	return type;
}

void MetaDataRegistry::AddMember(DataType* objType, DataType* memberType, const char* memberName, std::size_t offset)
{
	Member member;
	member.Name = memberName;
	member.Type = memberType;
	member.LocalOffset = offset;
	
	objType->Members.push_back(member);
}


void MetaDataRegistry::Insert(DataType* type) {
	m_Types[type->Name] = type;
}

MetaDataRegistry* MetaDataRegistry::Get() {
	static MetaDataRegistry registry;
	return &registry;
}

std::ostream &operator<<(std::ostream &os, gene::reflection::DataType* const &m) {
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