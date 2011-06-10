#/bin/ksh 


gcc -W -Wall -c gui.c
[[ $? -ne 0 ]] && exit 1

gcc -W -Wall -c fenetre.c
[[ $? -ne 0 ]] && exit 2

gcc -W -Wall -lcurses fenetre.o gui.o -o gui.out
[[ $? -ne 0 ]] && exit 3
