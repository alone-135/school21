#!bin/bash

sudo timedatectl set-timezone Europe/Moscow

function input {
	HOSTNAME=$(hostname)
	TIMEZONE="$(cat /etc/timezone) UTC $(date +%:::z)"
	USER=$(whoami)
	OS=$(hostnamectl | awk '$1 == "Operating" && $2 == "System:" {print $3, $4, $5}')
	DATE=$(date +'%d %B %Y %T')
	UPTIME=$(uptime -p | awk '{print $2, $3, $4, $5}')
	UPTIME_SEC=$(cat /proc/uptime | awk '{print $1}')
	IP=$(hostname -I)
	MASK=$(ifconfig | grep "inet.*broadcast" | awk '{print $4}')
	GATEWAY=$(ip route | grep default | awk '{print $3}')
	RAM_TOTAL=$(free -h | sed -n '2'p | awk '{printf("%.3f Gb\n"), $2 / 1024}')
	RAM_USED=$(free -h | sed -n '2'p | awk '{printf("%.3f Gb\n"), $3 / 1024}')
	RAM_FREE=$(free -h | sed -n '2'p | awk '{printf("%.3f Gb\n"), $4 / 1024}')
	SPACE_ROOT=$(df -Th | sed -n '4'p | awk '{printf("%.2f Mb\n"), $3 * 1024}')
	SPACE_ROOT_USED=$(df -Th | sed -n '4'p | awk '{printf("%.2f Mb\n"), $4 * 1024}')
	SPACE_ROOT_FREE=$(df -Th | sed -n '4'p | awk '{printf("%.2f Mb\n"), $5 * 1024}')
}

function output {
    export buff=$(
        echo "HOSTNAME = ${HOSTNAME}"
        echo "TIMEZONE = ${TIMEZONE}"
        echo "USER = ${USER}"
        echo "OS = ${OS}"
        echo "DATE = ${DATE}"
        echo "UPTIME = ${UPTIME}"
        echo "UPTIME_SEC = ${UPTIME_SEC}"
        echo "IP = ${IP}"
        echo "MASK = ${MASK}"
        echo "GATEWAY = ${GATEWAY}"
        echo "RAM_TOTAL = ${RAM_TOTAL}"
        echo "RAM_USED = ${RAM_USED}"
        echo "RAM_FREE = ${RAM_FREE}"
        echo "SPACE_ROOT = ${SPACE_ROOT}"
        echo "SPACE_ROOT_USED = ${SPACE_ROOT_USED}"
        echo "SPACE_ROOT_FREE = ${SPACE_ROOT_FREE}"
    )
    IFS=""
    echo ${buff}
    echo "want to write the data to a file? (Y/N)"
    yes1='y'
    yes2='Y'
    read y
    if [[ "${y}" = "${yes1}" ]] || [[ "${y}" = "${yes2}" ]] ; then
	    echo ${buff} > $(date '+%d_%m_%Y_%H_%M_%S').status
	    echo "File saved :)"
    else
	    rm -rf *.status
	    echo "File removed :("
    fi
}
