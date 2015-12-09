#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "tree.hh"

struct letter {
    uint8_t l : 8; // the letter
    uint32_t count : 24;
};

void initMarkovTree(tree<letter>& tr, int depth){

}

int main(int argc, char** argv){
    std::ifstream infile("preprocd.txt");
    if(!infile.is_open()){
        std::cout << "Failed to open training data" << std::endl;
        return 0;
    }
    // build markov chain for words
    tree<letter> tr;
    initMarkovTree(tr, 20);
    std::string word;
    while(infile >> word){
    }
}
