for i in {99990..100000}
do
	./gen $i 50 1000000000 > test_input
	pdiff hld_brute hld_impl test_input
	res=$?
	rm test_input
	if [ $res -ne 0 ]; then
		exit 1
	fi

done