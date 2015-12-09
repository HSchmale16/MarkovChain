#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "tree.hh"

// size of the training set in words
int gWordTrainingSetSize = 0;

class letter {
public:
    uint64_t l : 8; // the letter
    uint64_t count : 56;

    letter(){
        l = 0;
        count = 0;
    }

    letter(char c){
        l = c;
        count = 0;
    }

    bool operator==(char c){
        return this->l == c;
    }

    friend std::ostream& operator<<(std::ostream& out, letter& l){
        out << (char)l.l << "-" << l.count;
    }
};

void printTreeStats(const tree<letter>& tr){
    std::cerr << "Max Depth: " << tr.max_depth() << std::endl;
    std::cerr << "Nodes: " << tr.size() << std::endl;
    std::cerr << "Training Set Size: " << gWordTrainingSetSize << std::endl;
}

void printTree(const tree<letter>& tr){
    if(tr.empty())
        return;
    tree<letter>::iterator sib = tr.begin(),
        end = tr.end();
    while(sib != end){
        for(int i = 0; i < tr.depth(sib); ++i){
            std::cout << "  ";
        }
        std::cout << (*sib) << std::endl;
        ++sib;
    }
}

void trainMarkovChain(tree<letter>& tr, std::string& word){
    gWordTrainingSetSize++;
    tree<letter>::iterator treeIt = tr.begin(), loc;
    for(int i = 0; i < word.length(); i++){
        tree<letter>::sibling_iterator b = treeIt.begin(), e = treeIt.end();
        loc = std::find(b, e, word[i]);
        if(loc == treeIt.end()){
            // insert new node
            loc = tr.append_child(treeIt, letter(word[i]));
            loc->count++;
            treeIt = loc;
            continue;
        }else{
            // increment times found count for that letter in position
            loc->count++;
        }
    }
}

/**************************************
*   Program Entry Point               *
**************************************/
int main(int argc, char** argv){
    std::ifstream infile("preprocd.txt");
    if(!infile.is_open()){
        std::cout << "Failed to open training data" << std::endl;
        return 0;
    }

    // create the tree for the markov chain
    tree<letter> tr;
    // insert the root node of the chain
    // required so that child nodes can be appended to it
    tree<letter>::iterator treeTop = tr.insert(tr.begin(), letter(0));

    // begin training of the markov chain
    std::string word;
    while(infile >> word){
        trainMarkovChain(tr, word);
    }
    printTree(tr);
    printTreeStats(tr);
}
