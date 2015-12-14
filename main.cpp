#include <string>
#include <iostream>
#include <fstream>
//#include "MarkovLib.hh"
#include "tree.hh"

class SentenceMarkovChain {
private:
    int _trainSetSize; // lines in training set
    tree<std::string> _tree;
public:
    SentenceMarkovChain(){
        _trainSetSize = 0;
    }

    void train(std::string& sent){
        _trainSetSize++;
    }
    
    friend std::ostream& operator<<(std::ostream& out,
            const SentenceMarkovChain& c){
        out << "SentencesTrainingSet: " << c._trainSetSize << std::endl;
        return out;
    }
};

/**************************************
*   Program Entry Point               *
**************************************/
int main(int argc, char** argv){
    std::ifstream infile("./data/aligned.simple");
    if(!infile.is_open()){
        std::cout << "Failed to open training data" << std::endl;
        return 0;
    }

    SentenceMarkovChain chain;
    // begin training of the markov chain
    std::string line;
    while(getline(infile, line)){
        chain.train(line);
    }
    infile.close();
    std::cerr << chain << std::endl;
    //std::cout << chain.generate() << std::endl;
}
