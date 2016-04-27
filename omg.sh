#!/bin/bash

CMESSAGE="$1"

#Colors
red=$(tput setaf 1)             #  red
grn=$(tput setaf 2)             #  green
cya=$(tput setaf 6)             #  cyan
txtbld=$(tput bold)             #  Bold
bldred=${txtbld}$(tput setaf 1) #  red
bldgrn=${txtbld}$(tput setaf 2) #  green
bldylw=${txtbld}$(tput setaf 3) #  yellow
bldblu=${txtbld}$(tput setaf 4) #  blue
bldppl=${txtbld}$(tput setaf 5) #  purple
bldcya=${txtbld}$(tput setaf 6) #  cyan
txtrst=$(tput sgr0)             #  Reset

#Clear up & Start fresh
echo -e '\0033\0143'
clear



echo -e "$txtrst"" __  __   "$bldcya"  ______   "$bldppl"  ______   "$bldblu"  __  __   "$bldgrn"  ______   "$bldylw"  ______   "$bldred"  ______    "
echo -e "$txtrst""/\ \_\ \  "$bldcya" /\  __ \  "$bldppl" /\  ___\  "$bldblu" /\ \/ /   "$bldgrn" /\  __ \  "$bldylw" /\  == \  "$bldred" /\___  \   "
echo -e "$txtrst""\ \  __ \ "$bldcya" \ \  __ \ "$bldppl" \ \ \____ "$bldblu" \ \  _|-. "$bldgrn" \ \  __ \ "$bldylw" \ \  __<  "$bldred" \/_/  /__  "
echo -e "$txtrst"" \ \_\ \_\ "$bldcya" \ \_\ \_\ "$bldppl" \ \_____\ "$bldblu" \ \_\ \_\ "$bldgrn" \ \_\ \_\ "$bldylw" \ \_\ \_\ "$bldred"  /\_____\ "
echo -e "$txtrst""  \/_/\/_/"$bldcya"   \/_/\/_/"$bldppl"   \/_____/"$bldblu"   \/_/\/_/"$bldgrn"   \/_/\/_/"$bldylw"   \/_/ /_/"$bldred"   \/_____/ ""$txtrst"

echo -e "${cya}Step 1: ${bldppl}Add files${txtrst}"
git add -A

echo -e ""

echo -e "${cya}Step 2: ${bldppl}Commit changes${txtrst}"

if [ "$CMESSAGE" == "" ]
then
	echo -e "${grn}Insert commit message: ${txtrst}"
	read message
	git commit -m $message
else
	git commit -m "$CMESSAGE"
fi

echo -e ""

echo -e "${cya}Step 3: ${bldppl}Push changes${txtrst}"
git push origin master

echo -e ""

echo -e "Have a great day :)"
