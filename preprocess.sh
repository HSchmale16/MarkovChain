#!/bin/bash
# Preprocess the data file to remove any characters that are not letters from
# the data file, and it capitializes all the characters in the data file.
# line ommments can exist in the data file, they begin with a hash(#).
# This script is for generating word markov chain data.
#
# USAGE
# ./preprocess.sh <SOURCE_DATA_FILES>

cat $@ | \
    sed -e '/^#/ d' | \
    tr 'a-z-' 'A-Z ' | \
    tr -cd 'a-zA-Z \n' | \
    sed -e 's/ /\n/g' | \
    sed -e '/^$/d' | \
    awk 'length($0)>1' | \
    sort | \
    uniq
