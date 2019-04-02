#!/bin/sh

default_option="-lS"

#I want to use getopts to filter out all the invalid input ls option. When the options contain valid ls option, I set getopts to do nothing because it is much easier to do just ls -l -S -d "$@" later in code since all the invalid input will be filter out by the getopts.
while getopts "aAbBcCdDFgGhHiklLmnNopqQrRsSTwxZ1" opt; do
	case $opt in
		#for each valid option,it will do nothing, and let getopts to continue to scan until
		#there is invalid option
		
		#for each invalid option,it will print an error message and exit
		a);;
		A);;
                b);;
                c);;
                C);;
                D);;
                f);;
                F);;
                g)
			echo "Please do not use -g option."
                        exit 1;;
                G);;
                h);;
                H);;
                i)
                        echo "Please do not use -i option."
                        exit 1;;
                I);;
                k);;
                l);;
                L);;
                m);;
                n);;
                N);;
                o);;
                p);;
                q);;
                Q);;
                r);;
                R);;
                s)
                        echo "Please do not use -s option."
                        exit 1;;
                S);;
                t);;
                T);;
                u);;
                U);;
                v);;
                w);;
                X);;
                1);;
		Z);;
		?)
			echo "Please enter valid ls input"
			exit 1;;
	esac
done

if [ $# -eq 0 ]
then
	ls -l -S
else
	#Since getops already filter out all possible invalid ls options, the only error
	#should be having invalid file names or directory
	ls -l -S -d "$@" 2>/dev/null || echo "You need to enter valid file names or directory"
fi

