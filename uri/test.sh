#! /bin/bash

DIRECTORIES=$(ls -d */)
#DIRECTORIES=$(ls -d */ | grep 1485)

for directory in ${DIRECTORIES}; do
  echo "Test ${directory}"
  pushd . > /dev/null
  cd $directory 
  rm -rf exe
  g++ -std=c++11 $(ls | grep *.cpp) -o exe
  
  out=$(./exe < input)
  real=$(cat output)
  
  if [[ $out != $real ]]; then
    echo "${directory} failed"
    echo "Result:"
    echo "$out"
    echo "Expected:" 
    echo "$real"
    exit 1
  fi
  popd > /dev/null
done
