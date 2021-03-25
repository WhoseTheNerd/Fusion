@echo off
pushd ..
del /S *.vcxproj
del /S *.sln
del /S *.vcxproj.*
rmdir /S /Q "bin"
rmdir /S /Q "bin-int"
popd