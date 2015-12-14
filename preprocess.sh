#!/bin/bash
# Preprocess the data file to remove any characters that are not letters from
# the data file, and it capitializes all the characters in the data file.
# line ommments can exist in the data file, they begin with a hash(#).
# This script is for generating word markov chain data.
#
# USAGE
# ./preprocess.sh <SOURCE_DATA_FILES>

function filter-delete-comments() {
    sed -e '/^#/ d'
}

function filter-ucase() {
    tr 'a-z-' 'A-Z '
}

function filter-rm-nonalphabet() {
    tr -cd 'a-zA-Z \n'
}

function filter-spaces-2-newline() {
    sed -e 's/ /\n/g'
}

function filter-rm-blank-lines() {
    sed -e '/^$/d'
}

# accepts single arg - minimum word length
function filter-delete-short-words() {
    LEN=$(if [ -z ${var+x} ] ; then echo "1" ; else echo $var; fi)
    awk "length(\$0) > ${LEN}"
}

cat $@ | \
    filter-delete-comments | \
    filter-ucase | \
    filter-rm-nonalphabet | \
    filter-spaces-2-newline | \
    filter-rm-blank-lines | \
    filter-delete-short-words 1 | \
    sort | \
    uniq
