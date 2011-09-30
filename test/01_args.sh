#!/usr/bin/env bash

# nosleep functional test 01:
# Check that command-line arguments are passed correctly to the invoked command.
# Uses helper/args.sh, which prints the number and content of its arguments.

argtest_cmd='helper/args.sh arg1 --arg2 - "arg 4"'

result1="$(eval $argtest_cmd)"
result2="$(eval ../nosleep $argtest_cmd)"

if [ "$result1" != "$result2" ] ; then
	{
		echo $0: Test failed.
		echo ">>> Expected output:"
		echo "$result1"
		echo ">>> Actual output:"
		echo "$result2"
		exit 1
	} >&2
fi

exit 0
