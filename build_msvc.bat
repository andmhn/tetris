mkdir build
mkdir bin
robocopy sfml-msvc/lib  build sfml-graphics.lib sfml-window.lib sfml-system.lib
robocopy sfml-msvc/bin  bin sfml-graphics-2.dll sfml-window-2.dll sfml-system-2.dll
copy pixel_font.ttf bin
cd build

REM building...
cl -c ../src/border_utils.cpp    -I ../include -I ../sfml-msvc/include
cl -c ../src/components.cpp      -I ../include -I ../sfml-msvc/include
cl -c ../src/event_handler.cpp   -I ../include -I ../sfml-msvc/include
cl -c ../src/grid_entry.cpp      -I ../include -I ../sfml-msvc/include
cl -c ../src/instance.cpp        -I ../include -I ../sfml-msvc/include
cl -c ../src/tetromino.cpp       -I ../include -I ../sfml-msvc/include
cl -c ../src/utils.cpp           -I ../include -I ../sfml-msvc/include
cl -DMSVC -c ../drivers/main.cpp -I ../include -I ../sfml-msvc/include

REM linking
cl main.obj border_utils.obj components.obj event_handler.obj grid_entry.obj instance.obj tetromino.obj utils.obj sfml-graphics.lib sfml-window.lib sfml-system.lib

copy main.exe ..\bin\tetris.exe
cd ..