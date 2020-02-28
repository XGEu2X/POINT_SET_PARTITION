#!/bin/bash
[ ! -d "outs/" ] && mkdir outs

r=(0.5 1)
popSize=(60)
Cm=(0.1 0.2 0.3)
Cp=(0.5 0.75 1)
randSettlers=(6)
iterations=100
method=(2 3 4)

for((n=14; n<16; n=n+2)); do
let half=n/2;

for((t=4; t<$half; t=t+2));do
echo $n' '$t
for _r in ${r[*]}; do

for _popSize in ${popSize[*]}; do
	for _Cm in ${Cm[*]};do
	for _Cp in ${Cp[*]};do
		for _randSettlers in ${randSettlers[*]};do
			for _iterations in ${iterations[*]};do
				for _method in ${method[*]};do
./../build/AutoSearchArgs $n $t $_r $_popSize $_Cm $_Cp $_randSettlers $iterations $_method >> 'outs/'$n' '$t' '$_r' '$_popSize' '$_Cm' '$_Cp' '$_randSettlers' '$iterations' '$_method'.out'
				done
			done
		done
	done
	done
done

done

done

done
