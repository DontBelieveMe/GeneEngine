#pragma once
#include <Platform/Mono.h>


namespace Gene { namespace Scripting {
	class MonoEnviroment
	{
	private:
		MonoDomain *m_Domain;

	public:
		MonoEnviroment();
		~MonoEnviroment();
	};
}}