for i in {1..100}
do
	echo -n "Test #$i: "
	./gen > test_input
	./segtree < test_input > corr_output
	# time (seconds), memory (kilobytes)
	(ulimit -t 1 -v 128000; /usr/bin/time -f "%e %M" -o exec_report ./sparse_segtree_prog < test_input > user_output)
	diff corr_output user_output > /dev/null
	res=$?

	if [ $res -ne 0 ]; then
		echo -e -n "\033[1;31mFailed \033[0m"
		cat exec_report
		echo "Test input:"
		cat test_input
		cp test_input failed_test
		echo ""
		echo "Correct output:"
		cat corr_output
		echo ""
		echo "User output:"
		cat user_output
	fi

	rm test_input
	rm corr_output
	rm user_output

	if [ $res -ne 0 ]; then
		rm exec_report
		exit 1
	fi
	echo -e -n "\033[1;32mAccepted \033[0m"
	cat exec_report
	rm exec_report
done
