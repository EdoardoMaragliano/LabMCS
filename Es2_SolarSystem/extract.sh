#!/bin/bash

echo " " > fileInput
for i in $@
do 
    grep   $i effemeridi.h | grep "/\*" | awk '{print $1}' >> fileInput
    grep -A6 "// $i" effemeridi.h | tail -6 >> fileInput
    echo " " >> fileInput
done
