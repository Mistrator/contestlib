for i in {1..2}
do
	./gen 100000 1000000000000000000 > test_input
	pdiff brute miller_rabin test_input
	res=$?
	rm test_input
	if [ $res -ne 0 ]; then
		exit 1
	fi

done