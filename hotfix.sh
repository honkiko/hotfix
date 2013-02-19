#!/bin/bash

print_help()
{
	echo "Usage: $0 pid"
	echo "  pid: pid of process to patch"
}

if [ $# != 1 ]; then
	print_help
	exit
fi

kill -s SIGUSR2 $1
