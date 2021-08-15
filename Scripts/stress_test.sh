#!/usr/bin/sh

green=$(tput setaf 71);
red=$(tput setaf 1);
blue=$(tput setaf 32);
orange=$(tput setaf 178);
bold=$(tput bold);
reset=$(tput sgr0);

# If you use C++ Generator
# g++ -std=c++17 gen.cpp -o gen || { echo ${bold}${orange}Compilation Error${reset} in gen.cpp; exit 1; }

# If you use Python Generator (must have shebang)
cp gen.py ./gen || { echo ${bold}${orange}File Error:${reset} gen.py must exist; exit 1; }
chmod +x ./gen

g++ -std=c++17 app.cpp -o original || { echo ${bold}${orange}Compilation Error${reset} in $1.cpp; exit 1; }
g++ -std=c++17 brute.cpp -o brute || { echo ${bold}${orange}Compilation Error${reset} in $2.cpp; exit 1; }

if [ $# -eq 1 ]
    then
        max_tests=$1
    else
        max_tests=10
fi

diff_found=0
i=1

while [ $i -le $max_tests ]
do
    ./gen > input.txt

    ./original < input.txt > original_output.txt
    
    ./brute < input.txt > brute_output.txt

    if diff --tabsize=1 -F --label --side-by-side --ignore-space-change original_output.txt brute_output.txt > dont_show_on_terminal.txt; then
        echo "${orange}Test Case #$i: ${bold}${green}OK${reset}"
    else
        echo "${orange}Test Case #$i: ${bold}${red}FAIL${reset}"
        diff_found=1
        break
    fi

    i=$((i+1))
done

if [ $diff_found -eq 1 ]
then
    echo "${blue}${bold}Input: ${reset}"
    cat input.txt
    cat input.txt > breaking_case.txt
    echo ""

    echo "${red}${bold}Output: ${reset}"
    cat original_output.txt
    echo ""

    echo "${green}${bold}Expected: ${reset}"
    cat brute_output.txt
    echo ""
fi

rm input.txt
rm gen
rm original
rm brute
rm original_output.txt
rm brute_output.txt
rm dont_show_on_terminal.txt
