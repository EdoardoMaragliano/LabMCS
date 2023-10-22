#!/bin/bash
rm fileInput
echo " " >> fileInput
for planet in $@
do
    echo "$planet">>fileInput
    grep "/\* $planet" effemeridi.h | awk '{print $1}' >> fileInput
    grep -A6 "// $planet" effemeridi.h | grep -v "// $planet" >> fileInput
    echo " " >> fileInput
done
