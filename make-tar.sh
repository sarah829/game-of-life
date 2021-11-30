#!/bin/bash
# creates tar of bin/GameOfLife

user=$(whoami)
read_me_name=README-template.md
dir_path=/Users/$user/Programming/game-of-life/tars
name=GameOfLife
output="$name".tar.gz

# make folder for tar
mkdir $dir_path/GameOfLife
cp "$dir_path"/../bin/$name "$dir_path"/$name/$name
cp "$dir_path"/$read_me_name "$dir_path"/$name/README.md
echo $(date +%Y-%m-%d) >> $dir_path/$name/README.md

tar -C "$dir_path" -czf "$dir_path"/"$output" $name
rm -r "$dir_path"/$name
echo "tar created"