#!bin/bash

nfcount=`ls -l | grep ^- | wc -l`
dircount=`ls -l | grep ^d | wc -l`
sfcount=`ls -l | grep ^p | wc -l`
volume=`du -sh | cut -d"." -f1`
files1=`ls`
onlydir=`ls -l | grep ^d | rev | cut -f 1 -d ' ' | rev`
upcount=`cd .. | ls -l | wc -l`
count=`ls -l | wc -l` ## have to -1  = number of
files=`ls`
nowx=2
nowy=30
plusx=6
plusy=15


prin_dot()
{
echo `tput cup 2 30`[31m"     __ "
echo `tput cup 3 30`[31m"/---/ |"
echo `tput cup 4 30`[31m"|  d  |"
echo `tput cup 5 30`[31m"-------"
echo `tput cup 6 30`[31m"..   "
echo [0m
}

#####background frame#######
echo `tput cup 1 1` "===================================================================================================="
echo `tput cup 32 1` "*****************************************information************************************************"
echo `tput cup 40 1` "*****************************************information************************************************"
echo `tput cup 42 1` "===================================================================================================="

for (( i = 2 ; i < 32 ; i++ ))
do
echo `tput cup $i 23` "|"
done

for (( i = 2 ; i < 42 ; i++ ))
do
echo `tput cup $i 1` "|"
done

for (( i = 2 ; i < 42 ; i++ ))
do
echo `tput cup $i 100` "|"
done
#############################################################################first frame
cd $PWD/..
firstx=2
firsty=3
echo `tput cup $firstx $firsty`[31m".."
countnum=1
for files in *
do
	firstx=`expr $firstx + 1`
	if [ "`stat -c %F $files`" = "디렉토리" ]
	then
	echo [34m
	tput cup $firstx $firsty
	echo "`stat -c %n $files`"
	countnum=`expr $countnum + 1`

	elif [ "`stat -c %F $files`" = "FIFO" ]
	then
	echo [32m
	tput cup $firstx $firsty
	echo "`stat -c %n $files`"
	countnum=`expr $countnum + 1`

	elif [ "`stat -c %a $files`" = "755" ]
	then
	echo [31m
	tput cup $firstx $firsty
	echo "`stat -c %n $files`"
	countnum=`expr $countnum + 1`

	else
	echo [0m
	tput cup $firstx $firsty
	echo "`stat -c %n $files`"
	countnum=`expr $countnum + 1`
	
	fi

	if [ "$countnum" == 21 ] #because the first line of `ls` is total
	then
	break
	fi
done
echo [0m
cd - 
#############################################################################second frame
x=30
first=0
y=2
var=0
line=1
letscount=5

prin_dot
for files in *
do
	var=`expr $var + 1`
	if [ $line -eq 1 ]
	then
	first=15


        if [ "`stat -c %F $files`" = "디렉토리" ]
        then
	tput cup $y `expr $x + $first`
	echo [34m"     __"
        tput cup `expr $y + 1` `expr $x + $first`
	echo  "/---/ |"
        tput cup `expr $y + 2` `expr $x + $first`
	echo  "|  d  |"
        tput cup `expr $y + 3` `expr $x + $first`
	echo  "-------"
        tput cup `expr $y + 4` `expr $x + $first`
	echo  "`stat -c %n $files`" [0m 
        x=`expr $x + 15`
        if [ `expr $var % 4` -eq 0 ]
        then
        line=`expr $line + 1`
        y=`expr $y + 6`
        x=30
        var=0
	fi	

        elif [ "`stat -c %a $files`" = "755" ]
        then
        tput cup $y `expr $x + $first`
	echo [31m"_______"
        tput cup `expr $y + 1` `expr $x + $first`
	echo  "|     |"
        tput cup `expr $y + 2` `expr $x + $first`
	echo  "|  x  |"
        tput cup `expr $y + 3` `expr $x + $first`
	echo  "-------"
        tput cup `expr $y + 4` `expr $x + $first`
	echo  "`stat -c %n $files`" [0m
	x=`expr $x + 15`
        if [ `expr $var % 4` -eq 0 ]
        then
        line=`expr $line + 1`
        y=`expr $y + 6`
        x=30
        var=0
	fi	

        elif [ "`stat -c %F $files `" = "FIFO" ]
        then
        tput cup $y `expr $x + $first`
	echo [32m"_______"
        tput cup `expr $y + 1` `expr $x + $first`
	echo "|     |"
        tput cup `expr $y + 2` `expr $x + $first`
	echo "|  s  |"
        tput cup `expr $y + 3` `expr $x + $first`
	echo "-------"
        tput cup `expr $y + 4` `expr $x + $first`
	echo "`stat -c %n $files`" [0m 
	x=`expr $x + 15`	
        if [ `expr $var % 4` -eq 0 ]
        then
        line=`expr $line + 1`
        y=`expr $y + 6`
        x=30
        var=0
	fi

        else 
        tput cup $y `expr $x + $first`
	echo [0m"_______"
        tput cup `expr $y + 1` `expr $x + $first`
	echo "|     |"
        tput cup `expr $y + 2` `expr $x + $first`
	echo "|  o  |"
        tput cup `expr $y + 3` `expr $x + $first`
	echo "-------"
        tput cup `expr $y + 4` `expr $x + $first`
	echo "`stat -c %n $files`"
        x=`expr $x + 15`
       	if [ `expr $var % 4` -eq 0 ]
	then
	line=`expr $line + 1`
	y=`expr $y + 6`
	x=30
	var=0
	fi
	fi
	
	
	else
	
	first=0
	

        if [ "`stat -c %F $files`" = "디렉토리" ]
        then
        tput cup $y `expr $x + $first`
        echo [34m"     __"
        tput cup `expr $y + 1` `expr $x + $first`
        echo  "/---/ |"
        tput cup `expr $y + 2` `expr $x + $first`
        echo  "|  d  |"
        tput cup `expr $y + 3` `expr $x + $first`
        echo  "-------"
        tput cup `expr $y + 4` `expr $x + $first`
        echo  "`stat -c %n $files`" [0m
        x=`expr $x + 15`
        letscount=`expr $letscount + 1`
	if [ `expr $var % 5` -eq 0 ]
        then
        line=`expr $line + 1`
        y=`expr $y + 6`
        x=30
        var=0
	fi	

        elif [ "`stat -c %a $files`" = "755" ]
        then
        tput cup $y `expr $x + $first`
        echo [31m"_______"
        tput cup `expr $y + 1` `expr $x + $first`
        echo  "|     |"
        tput cup `expr $y + 2` `expr $x + $first`
        echo  "|  x  |"
        tput cup `expr $y + 3` `expr $x + $first`
        echo  "-------"
        tput cup `expr $y + 4` `expr $x + $first`
        echo  "`stat -c %n $files`" [0m
        x=`expr $x + 15`
        letscount=`expr $letscount + 1`
	if [ `expr $var % 5` -eq 0 ]
        then
        line=`expr $line + 1`
        y=`expr $y + 6`
        x=30
        var=0
	fi

        elif [ "`stat -c %F $files `" = "FIFO" ]
        then
        tput cup $y `expr $x + $first`
        echo [32m"_______"
        tput cup `expr $y + 1` `expr $x + $first`
        echo "|     |"
        tput cup `expr $y + 2` `expr $x + $first`
        echo "|  s  |"
        tput cup `expr $y + 3` `expr $x + $first`
        echo "-------"
        tput cup `expr $y + 4` `expr $x + $first`
        echo "`stat -c %n $files`" [0m
        x=`expr $x + 15`
        letscount=`expr $letscount + 1`
	if [ `expr $var % 5` -eq 0 ]
        then
        line=`expr $line + 1`
        y=`expr $y + 6`
        x=30
        var=0
	fi

        else
        tput cup $y `expr $x + $first`
        echo [0m"_______"
        tput cup `expr $y + 1` `expr $x + $first`
        echo "|     |"
        tput cup `expr $y + 2` `expr $x + $first`
        echo "|  o  |"
        tput cup `expr $y + 3` `expr $x + $first`
        echo "-------"
        tput cup `expr $y + 4` `expr $x + $first`
        echo "`stat -c %n $files`"
        x=`expr $x + 15`
	letscount=`expr $letscount + 1`		
	if [ `expr $var % 5` -eq 0 ]
        then
        y=`expr $y + 6`
        x=30
        line=`expr $line + 1`
	fi
     	fi
	fi
	if [ "$letscount" == "25" ]
	then
	break
	fi

done


#####first infomation frame########
echo `tput cup 33 23` "file name : `stat -c %n $files`"
echo `tput cup 34 23` "file type : `stat -c %F $files`"
echo `tput cup 35 23` "file size : `stat -c %s $files`"
echo `tput cup 36 23` "creation time : `stat -c %z $files`"
echo `tput cup 37 23` "permission : `stat -c %a $files`"
echo `tput cup 38 23` "absolute path : `pwd $files`"

###########

#####second infomation frame#######
echo `tput cup 41 33` `expr $count - 1`  total     $dircount dir    $nfcount file    $sfcount sfile    $volume byte
##########################################################Lets move
tput cup 2 30
while true
do
read -n1 -s a
        if [ $a == "" ]
        then
        read -n1 -s b
                if [ $b == "[" ]
                then
                read -n1 -s c
                        if [ $c == "A" ]
                        then
                                if [ $nowx == 2 ]
                                then
                                        tput cup $nowx $nowy
                                else
                                        nowx=`expr $nowx - $plusx`
                                        tput cup $nowx $nowy
                                fi

                        elif [ $c == "B" ]
                        then
                                if [ $nowx == 26 ]
                                then
                                        tput cup $nowx $nowy
                                else
                                        nowx=`expr $nowx + $plusx`
                                        tput cup $nowx $nowy
                                fi

                        elif [ $c == "C" ]
                        then
                                if [ $nowy == 90 ]
                                then
                                        tput cup $nowx $nowy
                                else
                                        nowy=`expr $nowy + $plusy`
                                        tput cup $nowx $nowy
                                fi


                        elif [ "D" ]
                        then
                                if [ $nowy == 30 ]
                                then
                                        tput cup $nowx $nowy
                                else
                                        nowy=`expr $nowy - $plusy`
                                        tput cup $nowx $nowy
                                fi
                        fi
                fi
        fi
done

