#!/bin/bash

file='files/infile'
while read line; do
	echo $line
done < $file
