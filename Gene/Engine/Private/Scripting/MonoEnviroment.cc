#include <Scripting/MonoEnviroment.h>

using namespace Gene::Scripting;

MonoEnviroment::MonoEnviroment()
{
	m_Domain = mono_jit_init("GeneScriptingMonoDomain");
}

MonoEnviroment::~MonoEnviroment()
{
	
}