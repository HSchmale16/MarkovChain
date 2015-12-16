#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MarkovLib.hh"
#include "tree.hh"

class SentenceMarkovChain {
private:
    struct WordCount {
        std::string str;
        uint64_t count;

        WordCount()
            :count(0) {}
        WordCount(std::string s)
            :str(s), count(0) {}
    };

    uint64_t _trainSetSize; // lines in training set
    tree<WordCount> _tree;
public:
    SentenceMarkovChain(){
        _trainSetSize = 0;
        _tree.insert(_tree.begin(), std::string());
    }

    void train(const std::string& sent){
        _trainSetSize++;
        std::stringstream ss(sent);
        std::string str;
        while(ss >> str){

        }
    }

    friend std::ostream& operator<<(std::ostream& out,
            const SentenceMarkovChain& c){
        out << "SentencesTrainingSet: " << c._trainSetSize << std::endl;
        out << "TreeSize: " << c._tree.size() << std::endl;
        out << "TreeDepth: " << c._tree.max_depth() << std::endl;
        return out;
    }
};

/**************************************
*   Program Entry Point               *
**************************************/
int main(int argc, char** argv){
    std::ifstream infile("/home/hschmale/MarkovChain/preprocd.txt");
    if(!infile.is_open()){
        std::cout << "Failed to open training data" << std::endl;
        return 0;
    }

    WordMarkovChain chain;
    // begin training of the markov chain
    std::string line;
    while(getline(infile, line)){
        chain.train(line);
    }
    infile.close();
    std::cerr << chain << std::endl;
    chain.printProbsGraph(std::cout);
    //std::cout << chain.generate() << std::endl;
}
