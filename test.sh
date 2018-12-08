#!/bin/bash

tests=(
"7 2
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com" 

"7 3
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com"

"7 100
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
maps.com quora.com"

"17 5
one four
two one
two five
three one
three two
three eleven
four one
six one
six three
seven one
seven three
eight one
eight three
nine three
ten three
eleven one
eleven three"

"10 1
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
maps.com quora.com
quoa.co maps.edu
quora.com ufl.com
quora.com facebok.co.in"

"7 10000
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
gmail.com maps.com"

"7 8
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
maps.com quora.com"

"10 5
google.com gmail.com
google.com maps.com
facebook.com ufl.edu
ufl.edu google.com
ufl.edu gmail.com
maps.com facebook.com
maps.com quora.com
quoa.co maps.edu
quora.com ufl.com
quora.com facebok.co.in"

"80 2
a b
a c
a d
a e
a f
a g
a h
a i
a j
a k
a l
a m
a n
a o
a p
a q
a r
a s
a t
a u
x b
x c
x d
x e
x f
x g
x h
x i
x j
x k
x l
x m
x n
x o
x p
x q
x r
x s
x t
x u
y b
y c
y d
y e
y f
y g
y h
y i
y j
y k
y l
y m
y n
y o
y p
y q
y r
y s
y t
y u
z b
z c
z d
z e
z f
z g
z h
z i
z j
z k
z l
z m
z n
z o
z p
z q
z r
z s
z t
z u")


ans=(
"facebook.com 0.20
gmail.com 0.20
google.com 0.10
maps.com 0.30
ufl.edu 0.20" 

"facebook.com 0.30
gmail.com 0.15
google.com 0.10
maps.com 0.25
ufl.edu 0.20"

"facebook.com 0.00
gmail.com 0.00
google.com 0.00
maps.com 0.00
quora.com 0.00
ufl.edu 0.00"

"eight 0.00
eleven 0.02
five 0.00
four 0.47
nine 0.00
one 0.27
seven 0.00
six 0.00
ten 0.00
three 0.00
two 0.02"

"facebok.co.in 0.10
facebook.com 0.10
gmail.com 0.10
google.com 0.10
maps.com 0.10
maps.edu 0.10
quoa.co 0.10
quora.com 0.10
ufl.com 0.10
ufl.edu 0.10"

"facebook.com 0.24
gmail.com 0.18
google.com 0.12
maps.com 0.24
ufl.edu 0.24"

"facebook.com 0.00
gmail.com 0.01
google.com 0.01
maps.com 0.01
quora.com 0.00
ufl.edu 0.01"

"facebok.co.in 0.01
facebook.com 0.01
gmail.com 0.03
google.com 0.01
maps.com 0.01
maps.edu 0.00
quoa.co 0.00
quora.com 0.01
ufl.com 0.01
ufl.edu 0.01"

"a 0.00
b 0.01
c 0.01
d 0.01
e 0.01
f 0.01
g 0.01
h 0.01
i 0.01
j 0.01
k 0.01
l 0.01
m 0.01
n 0.01
o 0.01
p 0.01
q 0.01
r 0.01
s 0.01
t 0.01
u 0.01
x 0.00
y 0.00
z 0.00")


trim() {

    # remove leading whitespace characters
    var="${1#"${1%%[![:space:]]*}"}"
    # remove trailing whitespace characters
    var="${var%"${var##*[![:space:]]}"}"   
}

if [ ! -f "StudentsToGrade/"$1"/TEST" ]; then
   echo "$1" >> Results/results.csv
   exit 0
fi

i=0
correct_cnt=0
for case in "${tests[@]}"; do
    

    res="$(echo -e "$case" | timeout 12 StudentsToGrade/"$1"/TEST)"
    trim "$res"
    res="$var"
    if [ "$res" == "${ans[$i]}" ]; then
        rtn_arr[$i]=1
        correct_cnt=$((correct_cnt + 1))
    else
        rtn_arr[$i]=0
    fi

    i=$((i + 1))
done
total=${#tests[@]}
frac="$correct_cnt/$total"
rtn="$(echo "${rtn_arr[*]}")"
rtn=${rtn// /,}
echo "$1,$rtn,'$frac" >> Results/results.csv

