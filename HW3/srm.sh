#!/bin/sh

#Check if TRASH environment variable has been defined
option=0
if [ -z $TRASH ]
then
	echo "TRASH environment variable is not defined"
	exit 1
fi

#create the trash folder if the $TRASH folder is not exist.
mkdir $TRASH 2>/dev/null || echo "Trash Can directory already exist! No need to create a new one!"

#Since I can use regular rm if srm is called with any option, I will need to use getopts to check if srm came with any options
while getopts "" opt;
do
	case "$opt" in
		\?) option=1;;
	esac
done
#if option is 1, then it means the input contains option, so the script will use
#regular rm to remove the file. Otherwise, the script will move the file to 
#$TRASH directory
if [ "$option" -eq 1 ]
then
	for item
	do
		rm $item
		echo "Removed file using regular rm command"
	done
else
	for item
	do	
		mv $item $TRASH
		echo "Successfuly srm file $item"
	done
fi









			
