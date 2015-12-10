SRC := main.cpp
EXE := markov
INPUTDATA := data.txt
PROCDDATAFILE := preprocd.txt
DATAPREPROCESSOR := ./preprocess.sh

all: $(EXE) $(PROCDDATAFILE)
clean:
	rm -f $(EXE)
	rm -f $(PROCDDATAFILE)

$(EXE): $(SRC)
	g++ -W -std=c++11 $^ -o $@

$(PROCDDATAFILE): $(INPUTDATA)
	$(DATAPREPROCESSOR) $^ > $@
