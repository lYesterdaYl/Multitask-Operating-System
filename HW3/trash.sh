#!/bin/sh

#Check if TRASH environment variable has been defined
if [ -z $TRASH ]
then
        echo "TRASH environment variable is not defined"
        exit 1
fi

if [ $# -gt 0 ]
then
	#The script will print error message and exitif input has more than 0
	# argument.
       	echo "trash does not take any arguments!"
        exit 1
else
	#recursivly removing all the files from the directory $TRASH, but the
	#directory will remain.
	echo "Removing all files in $TRASH"
	rm -rf $TRASH/*
	echo "Successfully removed all files in $TRASH"
fi
