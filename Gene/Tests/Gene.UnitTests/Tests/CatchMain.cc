#define CATCH_CONFIG_RUNNER
#include <Catch/catch.hpp>

#include <Platform/Window.h>

int GeneMain(int argc, char **argv)
{
	Catch::Session session;
	int cmdLineExecErr = session.applyCommandLine(argc, argv);
	
	if (cmdLineExecErr != 0) 
		return cmdLineExecErr;

	session.run();
    system("PAUSE");
}