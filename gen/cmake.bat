
pushd ..\

echo Generating Make Files
call git submodule update --init --recursive
call vendor\premake\premake5.exe cmake

PAUSE
