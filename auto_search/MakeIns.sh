#!/bin/bash

[ ! -d "ins/" ] && mkdir ins/

alg=(1 2)

nl=5
for ((c1=0; c1<=$nl; c1++))
do
	let a=10+2*$c1
	n[$c1]=$a
done
r=(0.5 1)

popSize=(60)
Cm=(0.1 0.2 0.3)
Cp=(0.5 0.75 1)
randSettlers=(6)

iterations=100
method=(1 2 3 4)

for _alg in ${alg[*]}
do
	for _n in ${n[*]}
	do
		let lt=_n/2
		let res=lt%2
		if [ $res -eq 0 ]
		then
			let lt-=2
		else
			let lt-=1
		fi
		let lt=(lt-4)/2

		for ((c1=0; c1<=lt; c1++))
		do
			let _t=4+c1*2
			for _r in ${r[*]}
			do
				if (($_alg==1))
				then
					for _method in ${method[*]}
					do
echo -e $_alg'\n'$_n'\n'$_t'\n'$_r'\n'$iterations'\n'$_method > 'ins/'$_alg'_'$_n'_'$_t'_'$_r'_'$iterations'_'$_method'.in'
					done
				else
					for _popSize in ${popSize[*]}
					do
						for _Cm in ${Cm[*]}
						do
							for _Cp in ${Cp[*]}
							do
								for _randSettlers in ${randSettlers[*]}
								do
									for _method in ${method[*]}
									do
echo -e $_alg'\n'$_n'\n'$_t'\n'$_r'\n'$_popSize'\n'$_Cm'\n'$_Cp'\n'$_randSettlers'\n'$iterations'\n'$_method > 'ins/'$_alg'_'$_n'_'$_t'_'$_r'_'$_popSize'_'$_Cm'_'$_Cp'_'$_randSettlers'_'$iterations'_'$_method'.in'
									done
								done
							done
						done
					done
				fi
			done
		done
	done
done
