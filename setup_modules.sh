##
## EPITECH PROJECT, 2021
## B-YEP-500-PAR-5-1-zia-emmanuel.blineau
## File description:
## setup_modules
##

#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m'

printf "${GREEN}▁▁▁▁▁▁${NC}Setup_Modules${GREEN}▁▁▁▁▁▁${NC}\n\n"

setup_unix()
{
    printf "${GREEN}Start Unix${NC} Setup ->\n"

    printf "${GREEN}Get${NC} Setup ->\n"
    cd ./modules/Get/ && ./setup_unix.sh && cd -
    
    printf "${GREEN}Logger${NC} Setup ->\n"
    cd ./modules/Logger && ./setup_unix.sh && cd -

    printf "${GREEN}Parser${NC} Setup ->\n"
    cd ./modules/Parser && ./setup_unix.sh && cd -

    printf "${GREEN}Ssl${NC} Setup ->\n"
    cd ./modules/ssl && ./setup_unix.sh ; cd -

    printf "${GREEN}PhpCgi${NC} Setup ->\n"
    cd ./modules/phpCgi && ./setup_unix.sh ; cd -
}

setup_windows()
{
    printf "${GREEN}Start Windows${NC} Setup ->\n"

    printf "${GREEN}Get${NC} Setup ->\n"
    ./modules/Get/setup_windows.ps1
    printf "${GREEN}Logger${NC} Setup ->\n"
    ./modules/Logger/setup_windows.ps1
    printf "${GREEN}Parser${NC} Setup ->\n"
    ./modules/Parser/setup_windows.ps1
    printf "${GREEN}Ssl${NC} Setup ->\n"
    ./modules/ssl/setup_windows.ps1
    printf "${GREEN}PhpCgi${NC} Setup ->\n"
    ./modules/phpCgi/setup_windows.ps1
}

case "$OSTYPE" in
    solaris*) printf "Your OS : SOLARIS\n" ;;
    darwin*)  printf "Your OS : OSX\n" ;; 
    linux*)   printf "Your OS : LINUX\n" ;;
    bsd*)     printf "Your OS : BSD\n" ;;
    msys*)    printf "Your OS : WINDOWS\n" ;;
    *)        printf "unknown: $OSTYPE\n" ;;
esac

PS3='Please enter your choice: '
options=("Windows" "Unix" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "Windows")
            setup_windows
            echo "Success !"
            break
            ;;
        "Unix")
            setup_unix
            echo "Success !"
            break
            ;;
        "Quit")
            break
            ;;
        *) echo "invalid option $REPLY";;
    esac
done