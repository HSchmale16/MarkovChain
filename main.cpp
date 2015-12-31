#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MarkovLib.hh"


/**************************************
*   Program Entry Point               *
**************************************/
int main(int argc, char** argv){
    std::ifstream infile("/home/hschmale/MarkovChain/words.list");
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
    //std::cout << chain.generate() << std::endl;
}
