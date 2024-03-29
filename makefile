SRC := main2.cpp
EXE := markov
CXX_FLAGS := -Wall -std=c++11 -O2
INPUTDATA := \
	data/*.txt /usr/share/dict/words
PROCDDATAFILE := preprocd.txt
DATAPREPROCESSOR := ./preprocess.sh

all: $(EXE) 
clean:
	rm -f $(EXE)
	rm -f $(PROCDDATAFILE)

$(EXE): $(SRC)
	g++ $(CXX_FLAGS) $< -o $@

$(PROCDDATAFILE): $(INPUTDATA)
	$(DATAPREPROCESSOR) $^ > $@

# File Deps Graph
$(EXE): GenericMarkov.hh
