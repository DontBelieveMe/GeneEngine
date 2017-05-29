#pragma once

namespace Gene { namespace Scripting {
	class MonoScript
	{
	public:
		MonoScript(const char *path);

		void Invoke();
	};
}}