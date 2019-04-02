#!/bin/sh

#Check if TRASH environment variable has been defined
if [ -z $TRASH ]
then
        echo "TRASH environment variable is not define"
        exit 1
fi

if [ $# -gt 0 ]
then
	#The script will print error message and exit if input has more than 0
	#arguments.
	echo "durm does not take any arguments!"
	exit 1
else
	#I usd grep to cut out the total size part and print it in a sentence
	#du c and h option provide total size and better format to read
	echo "If trash command is used, you can free $(du -ch $TRASH |grep total) total space"
fi	
