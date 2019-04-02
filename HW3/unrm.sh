#!/bin/sh

#for all the file that in the input, the script calls mv to move files from
#$TRASH to current directory.

#Check if TRASH environment variable has been defined
if [ -z $TRASH ]
then
        echo "TRASH environment variable is not defined"
        exit 1
fi

for item
do
	mv $TRASH/$item .
	echo "Successful restore $item to current directory"
done
