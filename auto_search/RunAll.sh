[ ! -d "outs/" ] && mkdir outs

ins=(ins/*)

for ((i=0; i<${#ins[@]}; i++)); do
	filename=${ins[$i]}
	echo $filename
	filename=${filename:4:-3}
	echo $filename
	((./../build/AutoSearch < 'ins/'$filename'.in') >> 'outs/'$filename'.out'; sleep 300) &
done
