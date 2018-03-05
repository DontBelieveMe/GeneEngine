@ECHO OFF

set build_dir=../Build
set android_api_ver=24


IF NOT DEFINED ANDROID_NDK (
	echo Enviroment variable ANDROID_NDK is not set and I politely request you do so. Chop chop!
	EXIT /B
)

IF NOT DEFINED ANDROID_HOME (
	echo Enviroment variable ANDROID_HOME is not set and I politely request you do so. Chop chop!
	EXIT /B
)

"%ANDROID_HOME%/tools/android" list targets | find "android-%android_api_ver%" >nul 2>&1

IF ERRORLEVEL 1 (
	echo Cannot target that android API version. Not installed! Sorry :(
	EXIT /B
)

set cmake_defs=-DANDROID_NATIVE_API_LEVEL=android-%android_api_ver% -DCMAKE_TOOLCHAIN_FILE=../Setup/android.toolchain.cmake -DCMAKE_BUILD_TOOL="%ANDROID_NDK%/prebuilt/windows-x86_x64\bin\make.exe"
set gen=cmake -G"MinGW Makefiles" %cmake_defs% -H../ -B%build_dir%
 
set build=cmake --build %build_dir%

IF "%1" == "--gen" (

	%gen%
)

IF "%2" == "--gen" (
	%gen%
)

IF "%1" == "--build" (
	%build%
)

IF "%2" == "--build" (
	%build%
)