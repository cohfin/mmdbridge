@setlocal

@if "%1" == "" (
  @call build x86
  @call build x64
  @goto copy_inc
  @goto end
) else (
  if "%1" == "x86" (
    set GENERATOR="Visual Studio 12 2013"
	set BOOST_ADDRESS_MODEL=32
  ) else if "%1" == "x64" (
    set GENERATOR="Visual Studio 12 2013 Win64"
	set BOOST_ADDRESS_MODEL=64
  )

  @if "%2" == "" (
    @call build %1 Release
    @call build %1 Debug
    goto end
  ) else if "%2" == "Release" (
    set ZLIB_LIB=zlibstatic.lib
	set BOOST_VARIANT=release
  ) else if "%2" == "Debug" (
    set ZLIB_LIB=zlibstaticd.lib
	set BOOST_VARIANT=debug
  )
)

@rem goto copy

:zlib
@pushd src\zlib-1.2.8
@md build_%1_%2 & cd build_%1_%2
@echo on
cmake -G%GENERATOR% -DCMAKE_INSTALL_PREFIX:PATH="%~dp0src\%1\%2" ..
msbuild /p:Configuration=%2 /m:%NUMBER_OF_PROCESSORS% INSTALL.vcxproj
@popd

:hdf5
@pushd src\hdf5-1.8.14
@md build_%1_%2 & cd build_%1_%2
@echo on
cmake -G%GENERATOR% -DHDF5_BUILD_HL_LIB:BOOL=ON -DHDF5_STRICT_FORMAT_CHECKS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH="%~dp0src\%1\%2" ..
msbuild /p:Configuration=%2 /m:%NUMBER_OF_PROCESSORS% INSTALL.vcxproj
@popd

:ilmbase
@pushd src\ilmbase-2.2.0
@if exist Half\HalfLimits.h_ goto ilmbase_1
@pushd Half
@ren HalfLimits.h HalfLimits.h_
@powershell -Command "Set-Content HalfLimits.h ((Get-Content HalfLimits.h_) -replace '(#include \"half.h\")',(\"#include ^<algorithm^>`n\" + '$1'))"
@popd
:ilmbase_1
@if exist Imath\ImathLimits.h_ goto ilmbase_2
@pushd Imath
@ren ImathLimits.h ImathLimits.h_
@powershell -Command "Set-Content ImathLimits.h ((Get-Content ImathLimits.h_) -replace '(IMATH_INTERNAL_NAMESPACE_HEADER_ENTER)',(\"#include ^<algorithm^>`n`n\" + '$1'))"
@popd
:ilmbase_2
@md build_%1_%2 & cd build_%1_%2
cmake -G%GENERATOR% -DBUILD_SHARED_LIBS:BOOL=OFF -DNAMESPACE_VERSIONING:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH="%~dp0src\%1\%2" ..
msbuild /p:Configuration=%2 /m:%NUMBER_OF_PROCESSORS% INSTALL.vcxproj
@popd

:glew
@if "%1" == "x86" msbuild /p:Configuration=%2;Platform=Win32;OutDir=%~dp0src\%1\%2\lib;TargetName=glew32s /m:%NUMBER_OF_PROCESSORS% src\glew-1.12.0\build\vc12\glew_static.vcxproj
@if "%1" == "x64" msbuild /p:Configuration=%2;Platform=x64;OutDir=%~dp0src\%1\%2\lib;TargetName=glew32s /m:%NUMBER_OF_PROCESSORS% src\glew-1.12.0\build\vc12\glew_static.vcxproj

:glut
@pushd src\glut-3.7
@if exist include\GL\glut.h_ goto glut_1
@pushd include\GL
@ren glut.h glut.h_
@powershell -Command "Set-Content glut.h ((Get-Content glut.h_) -replace 'extern ([^^\"])','$1')"
@popd
:glut_1
@cd lib\glut
@if exist CMakeLists.txt goto glut_2
@echo CMAKE_MINIMUM_REQUIRED (VERSION 2.8)>> CMakeLists.txt
@echo PROJECT (glut32)>> CMakeLists.txt
@echo INCLUDE_DIRECTORIES (../../include)>> CMakeLists.txt
@echo ADD_LIBRARY (glut32 STATIC glut_8x13.c glut_9x15.c glut_bitmap.c glut_bwidth.c glut_cindex.c glut_cmap.c glut_cursor.c glut_dials.c glut_dstr.c glut_event.c glut_ext.c glut_fullscrn.c glut_gamemode.c glut_get.c glut_hel10.c glut_hel12.c glut_hel18.c glut_init.c glut_input.c glut_joy.c glut_key.c glut_keyctrl.c glut_keyup.c glut_mesa.c glut_modifier.c glut_mroman.c glut_overlay.c glut_roman.c glut_shapes.c glut_space.c glut_stroke.c glut_swap.c glut_swidth.c glut_tablet.c glut_teapot.c glut_tr10.c glut_tr24.c glut_util.c glut_vidresize.c glut_warp.c glut_win.c glut_winmisc.c win32_glx.c win32_menu.c win32_util.c win32_winproc.c win32_x11.c)>> CMakeLists.txt
@echo INSTALL (TARGETS glut32 ARCHIVE DESTINATION lib)>> CMakeLists.txt
@echo INSTALL (FILES ../../include/GL/glut.h DESTINATION include/GL)>> CMakeLists.txt
:glut_2
@md build_%1_%2 & cd build_%1_%2
cmake -G%GENERATOR% -DCMAKE_INSTALL_PREFIX:PATH="%~dp0src\%1\%2" ..
msbuild /p:Configuration=%2 /m:%NUMBER_OF_PROCESSORS% INSTALL.vcxproj
@popd

:boost
@pushd src\boost_1_57_0
@if not exist b2.exe call bootstrap
@if not exist user-config.jam (
  echo using python : 3.4 : : %~dp0python\include : %~dp0..\python\Win32 : ^<address-model^>32 ; > user-config.jam
  echo using python : 3.4 : : %~dp0python\include : %~dp0..\python\x64 : ^<address-model^>64 ; >> user-config.jam
)
b2 address-model=%BOOST_ADDRESS_MODEL% variant=%BOOST_VARIANT% --stagedir=%~dp0src\%1\%2 --with-program_options --with-python --with-thread -j%NUMBER_OF_PROCESSORS%
xcopy boost %~dp0src\%1\%2\include\boost /s /e /k /i /y
@popd

:alembic
@pushd src\alembic-1_05_08
@if exist CMakeLists.txt_ goto alembic_1
@ren CMakeLists.txt CMakeLists.txt_
@powershell -Command "Set-Content CMakeLists.txt ((Get-Content CMakeLists.txt_) -replace '-DOPENEXR_DLL','-DNOMINMAX')"
:alembic_1
@if exist examples/bin/AbcLs/AbcLs.cpp_ goto alembic_2
@pushd examples\bin\AbcLs
@ren AbcLs.cpp AbcLs.cpp_
@powershell -Command "Set-Content AbcLs.cpp ((Get-Content AbcLs.cpp_) -replace 'struct sigaction act;','//$0')"
@powershell -Command "Set-Content AbcLs.cpp ((Get-Content AbcLs.cpp) -replace 'sigemptyset\(&act.sa_mask\);','//$0')"
@powershell -Command "Set-Content AbcLs.cpp ((Get-Content AbcLs.cpp) -replace 'act.sa_handler = segfault_sigaction;','//$0')"
@powershell -Command "Set-Content AbcLs.cpp ((Get-Content AbcLs.cpp) -replace 'act.sa_flags = SA_SIGINFO;','//$0')"
@powershell -Command "Set-Content AbcLs.cpp ((Get-Content AbcLs.cpp) -replace 'sigaction\(SIGSEGV, &act, NULL\);','//$0')"
@popd
:alembic_2
@md build_%1_%2 & cd build_%1_%2
cmake -G%GENERATOR% -DCMAKE_PREFIX_PATH:PATH="%~dp0src\%1\%2\cmake" -DALEMBIC_NO_TESTS:BOOL=ON -DUSE_PYILMBASE:BOOL=OFF -DUSE_PRMAN:BOOL=OFF -DUSE_ARNOLD:BOOL=OFF -DUSE_MAYA:BOOL=OFF -DUSE_PYALEMBIC:BOOL=OFF -DZLIB_LIBRARY:FILEPATH="%~dp0src\%1\%2\lib\%ZLIB_LIB%" -DZLIB_INCLUDE_DIR:PATH="%~dp0src\%1\%2\include" -DBOOST_ROOT:PATH="%~dp0src\%1\%2" -DILMBASE_ROOT:PATH="%~dp0src\%1\%2" -DGlew_LIBRARY_DIR:PATH="%~dp0src\%1\%2\lib" -DGlew_INCLUDE_DIR:PATH="%~dp0src\glew-1.12.0\include" -DCMAKE_INSTALL_PREFIX:PATH="%~dp0src\%1\%2" ..
msbuild /p:Configuration=%2 /m:%NUMBER_OF_PROCESSORS% INSTALL.vcxproj
@popd
@endlocal

:copy_lib
xcopy src\%1\%2\lib\* %1\%2\ /s /e /k /y
xcopy src\%1\%2\alembic-1.5.8\lib\static\* %1\%2\ /s /e /k /y
@goto end

:copy_inc
xcopy src\x86\Release\include\* include\ /s /e /k /y
xcopy src\x86\Release\alembic-1.5.8\include\* include\ /s /e /k /y
xcopy src\glew-1.12.0\include\* include\ /s /e /k /y
xcopy src\boost_1_57_0\boost include\boost /s /e /k /i /y

:end
