mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --target ALL_BUILD --config Release
cd ..
copy .\build\Release\Bricks.exe .
pause