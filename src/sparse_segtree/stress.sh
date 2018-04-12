for i in {99980..100000}
do
	./gen $i 100000 1000000000 > test_input
	pdiff segtree sparse_segtree test_input
	res=$?
	rm test_input
	if [ $res -ne 0 ]; then
		exit 1
	fi

done