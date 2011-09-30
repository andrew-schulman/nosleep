#!/bin/bash

# Test script:
# Print the number of command-line arguments, and the list
# of all command-line arguments with which the script was
# invoked.

echo argc=${#@}
for ((i = 0; i<=${#@}; ++i)) ; do
	echo argv[$i]=${!i}
done
