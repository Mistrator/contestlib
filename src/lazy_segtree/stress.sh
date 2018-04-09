for i in {1..500}
do

	./gen $i 100000 1000000000 > test_input
	pdiff brute_test lazy_segtree test_input
	res=$?
	rm test_input
	if [ $res -ne 0 ]; then
		exit 1
	fi
done