#! /bin/bash

DIRECTORIES=$(ls -d */)
#DIRECTORIES=$(ls -d */ | grep 1485)

for directory in ${DIRECTORIES}; do
  echo "Testing case: ${directory} ..."
  pushd . > /dev/null
  cd $directory 
  rm -rf exe
  g++ -std=c++11 $(ls | grep *.cpp) -o exe
  
  ./exe < input > out
  
  if [[ $(cat out) != $(cat output) ]]; then
    echo "Busted..."
    if [[ $1 == '-v' ]]; then
      cat out
    else
      vimdiff <(cat out) <(cat output)
    fi
    exit 1
  fi
  popd > /dev/null
done
