EXE := markov
INPUTDATA := data.txt
PROCDDATAFILE := preprocd.txt
DATAPREPROCESSOR := ./preprocess.sh

all: $(EXE) $(PROCDDATAFILE)
clean:
	rm -f $(EXE)
	rm -f $(PROCDDATAFILE)

$(EXE): main.cpp
	g++ -g -std=c++11 $< -o $@

$(PROCDDATAFILE): $(INPUTDATA)
	$(DATAPREPROCESSOR) $^ > $@
