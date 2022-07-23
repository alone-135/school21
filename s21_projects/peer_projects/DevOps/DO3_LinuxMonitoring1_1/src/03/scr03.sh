#!/bin/bash

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
        echo -e "${color_input}HOSTNAME${clear} = ${color_output}${HOSTNAME}${clear}"
        echo -e "${color_input}TIMEZONE${clear} = ${color_output}${TIMEZONE}${clear}"
        echo -e "${color_input}USER${clear} = ${color_output}${USER}${clear}"
        echo -e "${color_input}OS${clear} = ${color_output}${OS}${clear}"
        echo -e "${color_input}DATE${clear} = ${color_output}${DATE}${clear}"
        echo -e "${color_input}UPTIME${clear} = ${color_output}${UPTIME}${clear}"
        echo -e "${color_input}UPTIME_SEC${clear} = ${color_output}${UPTIME_SEC}${clear}"
        echo -e "${color_input}IP${clear} = ${color_output}${IP}${clear}"
        echo -e "${color_input}MASK${clear} = ${color_output}${MASK}${clear}"
        echo -e "${color_input}GATEWAY${clear} = ${color_output}${GATEWAY}${clear}"
        echo -e "${color_input}RAM_TOTAL${clear} = ${color_output}${RAM_TOTAL}${clear}"
        echo -e "${color_input}RAM_USED${clear} = ${color_output}${RAM_USED}${clear}"
        echo -e "${color_input}RAM_FREE${clear} = ${color_output}${RAM_FREE}${clear}"
        echo -e "${color_input}SPACE_ROOT${clear} = ${color_output}${SPACE_ROOT}${clear}"
        echo -e "${color_input}SPACE_ROOT_USED${clear} = ${color_output}${SPACE_ROOT_USED}${clear}"
        echo -e "${color_input}SPACE_ROOT_FREE${clear} = ${color_output}${SPACE_ROOT_FREE}${clear}"
    )
    IFS=""
    echo ${buff}
}
