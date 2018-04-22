for i in {1..1000}
do
	./gen $i 100000 1000000000 > test_input
	./brute < test_input > corr_output
	./tested < test_input > user_output
	diff corr_output user_output > /dev/null
	res=$?

	if [ $res -ne 0 ]; then
		echo "Wrong answer"
		echo "Test input:"
		cat test_input
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
		exit 1
	fi
done
