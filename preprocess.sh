#!/bin/bash
# Preprocess the data file to remove any characters that are not letters from
# the data file, and it capitializes all the characters in the data file.
# line ommments can exist in the data file, they begin with a hash(#).
#
# USAGE
# ./preprocess.sh <SOURCE_DATA_FILES>

cat $@ | \
    sed -e '/^#/ d' | \
    tr 'a-z-' 'A-Z ' | tr -cd 'A-Z \n' | \
    sed -e 's/ /\n/g' | sed -e '/^$/d' | \
    sort
