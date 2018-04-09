for i in {1..100}
do

	./gen $i 500000 1000000000000 > test_input
	pdiff treap_brute treap test_input
	res=$?
	rm test_input
	if [ $res -ne 0 ]; then
		exit 1
	fi
done