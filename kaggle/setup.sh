#!/bin/bash

if [ -z $1 ]; then
  echo "Parameter must be give. Ex.: setup.sh spvfirstdatasciencecompetition"
  exit 1
fi

COMPETITION=$1
DATA_FOLDER=$COMPETITION/data
ZIP_FILE=$COMPETITION.zip

mkdir -p $DATA_FOLDER

cd $DATA_FOLDER
kaggle competitions download -c $COMPETITION

unzip $ZIP_FILE
rm -rf $ZIP_FILE
