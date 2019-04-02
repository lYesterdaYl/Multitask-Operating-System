#!/bin/sh

#calls ls -l to print out the information of all files in $TRASH directory.

#Check if TRASH environment variable has been defined
if [ -z $TRASH ]
then
        echo "TRASH environment variable is not define"
        exit 1
fi

ls -l $TRASH	
