#!/bin/bash

clear

SECONDS=0

rm out.bmp
rm valgrind.log

# ディレクトリが存在するか確認
# directory="./build/"

# if [ -d "$directory" ]; then
#    echo "directory:" "$directory found"
#    rm -rf "$directory"
#    echo "directory:" "$directory" " was deleted."

#    mkdir "$directory"
#    echo "directory:" "$directory" " was created."

# else
#    mkdir  "$directory"
# fi

tree > tree.txt

# ninjaでbuildする
cmake -B ./build -G Ninja
cd ./build
ninja -t clean
ninja
cd ..

# ./build/main

valgrind --leak-check=full --track-origins=yes --log-file=valgrind.log ./build/main

runtime=$SECONDS

echo $runtime  "[sec]"
