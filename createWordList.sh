#!/bin/bash
# Create a random word list for training the markov chain from the
# preprocessed data file.
# USAGE
#   ./createWordList.sh <N>
# [N] - size of word list, default is 100

LISTSIZE=${1:-100}

shuf -n $LISTSIZE preprocd.txt > words.list
