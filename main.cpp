#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "tree.hh"

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
        out << l.l << l.count;
    }
};

void printTreeStats(const tree<letter>& tr){
    std::cerr << "Max Depth: " << tr.max_depth() << std::endl;
    std::cerr << "Nodes: " << tr.size() << std::endl;
    std::cerr << "Training Set Size: " << gWordTrainingSetSize << std::endl;
}

int main(int argc, char** argv){
    std::ifstream infile("preprocd.txt");
    if(!infile.is_open()){
        std::cout << "Failed to open training data" << std::endl;
        return 0;
    }

    tree<letter> tr;
    tree<letter>::iterator treeTop = tr.insert(tr.begin(), letter(0));
    std::string word;
    while(infile >> word){
        gWordTrainingSetSize++;
        tree<letter>::iterator treeIt = treeTop, loc;
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
    printTreeStats(tr);
}
