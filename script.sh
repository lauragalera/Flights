#!/bin/bash
DIR=./jocProves/*.txt
EXEC=aviacio

for file in $DIR
do
   	./$EXEC < $file
	printf "\n\n\n"
done
