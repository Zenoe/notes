#!/bin/bash

# sh wait -t 5 -i 2 -c ls -s test
# run the provided command and grep check the provided string
# within given timeout

wait_timeout=60
cmdStr=
checkStr=
interval=1

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -t|--timeout)
    wait_timeout="$2"
    shift # past argument
    shift # past value
    ;;
    -s|--checkstr)
    checkStr="$2"
    shift # past argument
    shift # past value
    ;;
    -c|--cmdStr)
    cmdStr="$2"
    shift # past argument
    shift # past value
    ;;
    -i|--interval)
    interval="$2"
    shift # past argument
    shift # past value
    ;;
    --default)
    DEFAULT=YES
    shift # past argument
    ;;
    *)    # unknown option
    POSITIONAL+=("$1") # save it in an array for later
    shift # past argument
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

function conditionCheck()
{
    cmd=$1
    checkStr=$2

    if [ -z $checkStr ]; then
      "${cmd[@]}"
    else
      "${cmd[@]}" | grep $checkStr
    fi

    if [ $? -eq 0 ]; then
        true
    else
        false
    fi
}

if [ -z $cmdStr ]; then
  echo "provide command to be checked"
  exit 0
fi

echo "cmd: $cmdStr; check: $checkStr"

wait_time=1
while (! conditionCheck $cmdStr  $checkStr) && [[ $wait_time -le $wait_timeout ]]; do
    sleep $interval
    echo "waits for $wait_time"
    wait_time=$((wait_time + 1))
done
