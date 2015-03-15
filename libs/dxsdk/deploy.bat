xcopy "%DXSDK_DIR%Include\*" "%~dp0include" /s /e /i /k /y
xcopy "%DXSDK_DIR%\Lib\*" "%~dp0lib" /s /e /i /k /y

powershell -Command "sc %~dp0include\d3dx9core.h (New-Object System.Text.RegularExpressions.Regex '#ifdef __cplusplus\n#ifdef UNICODE', Multiline).Replace([string]::Join(\"`n\", (gc %~dp0include\d3dx9core.h)), \"#if defined(__cplusplus) ^&^& !defined(CINTERFACE)`n#ifdef UNICODE\")"
