@echo off

:: Set a bunch of variables (obvs)
set build_dir=..\..\Build
set src_dir=..\
set ndk_dir=I:/android-ndk-r12b

set app_name=Gene.Sandbox
set package_name=com.gene.sandbox

if "%1" == "clean" (
	rmdir %build_dir% /s /q
	cd %~dp0
	exit /b 0
)

set abi=%1

mkdir %build_dir%

copy AndroidManifest.xml %build_dir%\AndroidManifest.xml
copy android.toolchain.cmake %build_dir%\android.toolchain.cmake

xcopy res %build_dir%\res /e /i /y /s

cd %build_dir%

:: Generate android project files (needed for ant)
call android update project --path . --target android-24 -n Gene.Sandbox

call :check_for_errors

:: Generate the makefile
call cmake -DCMAKE_TOOLCHAIN_FILE=android.toolchain.cmake -DANDROID_ABI=%abi% DCMAKE_BUILD_TOOL="%ndk_dir%/prebuilt/windows-x86_x64/bin/make.exe" -G"MinGW Makefiles" -DANDROID_NDK=%ndk_dir% -DANDROID_NATIVE_API_LEVEL=android-24 -DLIBRARY_OUTPUT_PATH_ROOT=. -B. -H%src_dir%

call :check_for_errors

:: Build the project
call cmake --build .

if %errorlevel% neq 0 (
	cd %~dp0
	exit /b %errorlevel%
)
:: Run ant (generate APK and package resources etc...)
call ant debug

call :check_for_errors

:: If we need to deploy upload the APK to the device and then open it
if "%2" == "deploy" (
	:: Upload the APK to the device
	call adb install -r bin/%app_name%-debug.apk
	
	:: Run/open the app
	call adb shell monkey -p %package_name% -c android.intent.category.LAUNCHER 1
)

if "%2" == "install" (
	call adb install -r bin/%app_name%-debug.apk
)

cd %~dp0

:check_for_errors
if %errorlevel% neq 0 (
	cd %~dp0
	exit /b %errorlevel%
)
exit /b 0