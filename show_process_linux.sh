ls /proc | grep -E [0-9] | sort -g  > file # zapisuje do pliku 'file' nazwy wszystkich aktualnie uruchomionych procesów

IFS=$'\n' read -d '' -r -a pid < file

if [ "$1" = "-p" ]
then
    Z=`grep -c "[^$]" file`  # Z == ilość linii w pliku file, tzn ilość obecnie uruchomionych procesów
    
    Z=$((Z-1)) # Z - 1, aby zgadzały się z indeksami tablicy 'pid'

    for number in `seq 0 $Z`
    do    
        echo -n "${pid[number]} " #wypisuje pid procesu    
        ppid=`cat /proc/${pid[number]}/status 2>error | grep -Ei "ppid" | grep -Eo "[0-9]*$"`  # PPID
        uid=`cat /proc/${pid[number]}/status 2>error| grep -Ei "uid" | grep -Eo "[0-9]*$"`  # uid
        #uname=`cat /etc/passwd | grep -E ":$uid:" | grep -Eo "^[[:alpha:]]*"`
        #id 103 | grep -Eo "[[:digit:]]*([[:alpha:]]*)" | grep -Ev "^[0-9]" | grep -A 1 "uid" | tail -1
        uname=`id $uid | grep -Eo "[[:digit:]]*([[:alpha:]]*)" | grep -Ev "^[0-9]" | grep -A 1 "uid" | tail -1`
        pname=`cat /proc/${pid[number]}/comm 2>error`    

        echo  -n $ppid  ""
        echo  -n $uid ""
        echo  -n "($uname)" ""     
        echo  -n "$pname" "" 
        echo    
    done
rm file
elif [ "$1" = "-u" ] 
then

    me=`whoami` #nazwa uzytkownika który uruchomił skrypt
    ls -l /proc | grep -E "$me" | grep -Eo "[[:digit:]]*$" | sort -g > file_user # zapisuje do pliku 'file_user' nazwy wszystkich aktualnie uruchomionych procesów użytkownika którego nazwę przechowuje zmienna '$me'
    
    IFH=$'\n' read -d '' -r -a pid2 < file_user # przypisuje do tablicy 'pid2' nazwy procesów

    ZZ=`grep -c "[^$]" file_user`               # ZZ = ilość procesów    

    Z=$((Z-1))    
   
    for number1 in `seq 0 $ZZ`                 # pętla wykunująca się tyle razy, ile wynosi ilość procesów
    do    
        echo -n "${pid2[number1]} "
    
        ppid=`cat /proc/${pid2[number1]}/status 2>error | grep -Ei "ppid" | grep -Eo "[0-9]*$"`  # PPID
        #uid=`cat /proc/${pid2[number1]}/status 2>error| grep -Ei "uid" | grep -Eo "[0-9]*$"`  # UID
        #uname=`cat /etc/passwd | grep -E ":$uid:" | grep -Eo "^[[:alpha:]]*"`
        #id 103 | grep -Eo "[[:digit:]]*([[:alpha:]]*)" | grep -Ev "^[0-9]" | grep -A 1 "uid" | tail -1

        #uname=`id $uid | grep -Eo "[[:digit:]]*([[:alpha:]]*)" | grep -Ev "^[0-9]" | grep -A 1 "uid" | tail -1`
        uname="$me"
        pname=`cat /proc/${pid2[number1]}/comm 2>error`
        katalog_roboczy=`ls -l /proc/${pid2[number1]}/cwd 2>error | grep -Eo "\-+>+*+[[:blank:]]+.*$" 2>error | cut -b 4- `   

        #echo  -n $ppid  ""
        #echo  -n $uid ""
        #echo  -n "($uname)" "" 
    
        echo  -n "$pname " " " 
        echo  -n "$katalog_roboczy" " " 
        echo  
    done

rm file_user
rm file
elif [ -z $1 ] # jeżeli argument wywołania skryptu ma zerową długość
then
    echo Nie podano parametru

elif [ ! $1 = -p -a ! $1 = -u ]  # jeżeli nie jest to ani '-p', ani '-u'
then
    echo Podano bledny parametr
fi



