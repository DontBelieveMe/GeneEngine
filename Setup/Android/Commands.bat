:: will only install on device and not open
AndroidBuild.bat arm64-v8a install 

:: will install on device and open the app
AndroidBuild.bat arm64-v8a deploy 

:: filters to only include Gene logs and prints to stdout
adb logcat Gene:V *:S 

:: clears the log buffer
adb logcat -c
