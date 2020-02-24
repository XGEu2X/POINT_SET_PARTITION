#!/bin/bash
[ ! -d "outs/" ] && mkdir outs

ins=(ins/*)

for ((i=0; i<${#ins[@]}; i++)); do
	filename=${ins[$i]}
	filename=${filename:4:-3}
	(./../build/AutoSearch < 'ins/'$filename'.in') >> 'outs/'$filename'.out';
	if((($i-1)%5==0))
	then
		sleep 300
	fi
	echo $filename'.in finished'
done
