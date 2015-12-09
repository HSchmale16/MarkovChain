#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "tree.hh"
//#include "tree_util.hh"

struct letter {
    uint32_t l : 8; // the letter
    uint32_t count : 24;

    letter(){
        l = 0;
        count = 0;
    }

    letter(char c){
        l = c;
        count = 0;
    }
};

void initMarkovTreeNode(tree<letter>& tr,
        tree<letter>::iterator& it, int depth){
    for(char c = 'A'; c <= 'Z'; c++){
        tr.append_child(it, letter(c));
        if(depth > 0){
            initMarkovTreeNode(tr, it, depth - 1);
        }
    }
}

void initMarkovTree(tree<letter>& tr, int depth){
    for(char c = 'A'; c <= 'Z'; c++){
        tree<letter>::iterator node = tr.insert(tr.begin(), letter(c));
        if(depth > 0){
            initMarkovTreeNode(tr, node, depth - 1);
            std::cout << c << std::endl;
        }
    }
}

int main(int argc, char** argv){
    std::ifstream infile("preprocd.txt");
    if(!infile.is_open()){
        std::cout << "Failed to open training data" << std::endl;
        return 0;
    }
    // build markov chain for words
    tree<letter> tr;
    std::string word;
    initMarkovTree(tr, 10);
    while(infile >> word){
    }
}
