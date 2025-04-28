#!/bin/bash

JUMP_HOST=tiaoban
REMOTE_USER=sipeed         
REMOTE_HOST=192.168.31.43      
PASSWORD=licheepi        
PORT=22
REMOTE_FILE_PATH=GEMM_test 


for arg in "$@"; do
    case $arg in
        M=*)
            M="${arg#*=}"
            ;;
        N=*)
            N="${arg#*=}"
            ;;
        K=*)
            K="${arg#*=}"
            ;;
        *)
            echo "Invalid argument: $arg"
            exit 1
            ;;
    esac
done


if [ -z "$M" ] || [ -z "$N" ] || [ -z "$K" ]; then
    echo "Usage: $0 M=<value> N=<value> K=<value>"
    exit 1
fi


MKDIR_COMMANDS="mkdir -p $REMOTE_FILE_PATH"
RUNNING_COMMANDS="cd $REMOTE_FILE_PATH; ./gemm_program $M $N $K 10"


echo "sshpass -p \"$PASSWORD\" ssh -o ProxyJump=$JUMP_HOST $REMOTE_USER@$REMOTE_HOST -p $PORT \"$MKDIR_COMMANDS\""
sshpass -p "$PASSWORD" ssh -o ProxyJump=$JUMP_HOST $REMOTE_USER@$REMOTE_HOST -p $PORT "$MKDIR_COMMANDS"

LOCAL_FILE_PATH=./build/gemm_program
echo "sshpass -p \"$PASSWORD\" ssh -o ProxyJump=$JUMP_HOST \"$REMOTE_USER@$REMOTE_HOST\" -p $PORT \"rm -f $REMOTE_FILE_PATH/$(basename $LOCAL_FILE_PATH)\""
sshpass -p "$PASSWORD" ssh -o ProxyJump=$JUMP_HOST "$REMOTE_USER@$REMOTE_HOST" -p $PORT "rm -f $REMOTE_FILE_PATH/$(basename $LOCAL_FILE_PATH)"

echo "sshpass -p \"$PASSWORD\" scp -o ProxyJump=$JUMP_HOST -P $PORT \"$LOCAL_FILE_PATH\" \"$REMOTE_USER@$REMOTE_HOST:$REMOTE_FILE_PATH\""
sshpass -p "$PASSWORD" scp -o ProxyJump=$JUMP_HOST -P $PORT "$LOCAL_FILE_PATH" "$REMOTE_USER@$REMOTE_HOST:$REMOTE_FILE_PATH"


if [ $? -eq 0 ]; then
    echo "File transferred successfully."
else
    echo "Error: File transfer failed."
    exit 1  
fi

echo "sshpass -p \"$PASSWORD\" ssh -o ProxyJump=$JUMP_HOST $REMOTE_USER@$REMOTE_HOST -p $PORT \"$RUNNING_COMMANDS\""
sshpass -p "$PASSWORD" ssh -o ServerAliveInterval=8 -o ServerAliveCountMax=3 -o ProxyJump=$JUMP_HOST $REMOTE_USER@$REMOTE_HOST -p $PORT "$RUNNING_COMMANDS"