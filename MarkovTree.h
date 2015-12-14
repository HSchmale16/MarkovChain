#ifndef MARKOVTREE_H_INC
#define MARKOVTREE_H_INC

// size of the training set in words
int gWordTrainingSetSize = 0;

class letter {
public:
    uint64_t l : 8;      //!< the letter
    uint64_t count : 56; //!< times occured

    letter(){
        l = 0;
        count = 1;
    }

    letter(char c){
        l = c;
        count = 1;
    }

    letter(char le, int c)
        :l(le), count(c) {}

    bool operator==(char c){
        return this->l == c;
    }

    friend bool operator==(letter l1, letter l2){
        return (l1.l == l2.l) && (l1.count == l2.count);
    }

    friend std::ostream& operator<<(std::ostream& out, letter& l){
        out << (char)l.l << "-" << l.count;
        return out;
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
            std::cout << "    ";
        }
        std::cout << (*sib) << std::endl;
        ++sib;
    }
}

void trainMarkovChain(tree<letter>& tr, std::string& word){
    gWordTrainingSetSize++;
    tree<letter>::iterator treeIt = tr.begin(), loc;
    for(size_t i = 0; i < word.length(); i++){
        tree<letter>::sibling_iterator b = treeIt.begin(), e = treeIt.end();
        loc = std::find(b, e, word[i]);
        if(loc == treeIt.end()){
            // insert new node
            loc = tr.append_child(treeIt, letter(word[i]));
            loc->count++;
            treeIt = loc;
        }else{
            // increment times found count for that letter in position
            loc->count++;
        }
        treeIt = loc;
    }
}

std::string generateFromMarkovChain(tree<letter>& tr){
    //std::cerr << "Generating" << std::endl;
    // generator only used here but needs to maintain state between calls
    static std::default_random_engine gen =
        std::default_random_engine(std::chrono::system_clock::now()
            .time_since_epoch().count()
        );
    std::array<int64_t, 255> probs;
    tree<letter>::iterator treeTop = tr.begin();
    std::string str;
    do {
        tree<letter>::sibling_iterator beg = treeTop.begin(),
            end = treeTop.end();
        // get probs
        int idx = 0;
        std::fill(probs.begin(), probs.end(), 0);
        for(auto it = beg; it != end; ++it){
            probs[it->l - 32] = it->count;
            idx++;
        }
        std::discrete_distribution<int> distrib(probs.begin(), probs.end());
        // pick out the letter
        idx = distrib(gen);
        str += (char)(idx + 32);
        treeTop = std::find(beg, end, letter(idx + 32, probs[idx]));
        if(treeTop == tr.end()){
            std::cerr << "Early Exixt because end" << std::endl;
            return str;
        }
    } while(tr.max_depth(treeTop));
    return str;
}


#endif // MARKOVTREE_H_INC
