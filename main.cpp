#include <unistd.h>
#include <chrono>
#include <random>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <map>
#include <vector>
#include <iterator>

std::default_random_engine gen =
    std::default_random_engine(std::chrono::system_clock::now()
        .time_since_epoch().count()
    );

size_t randomZeroToN(size_t n){
    std::uniform_int_distribution<size_t> d(0, n);
    return d(gen);
}

short twoChar2Short(char c1, char c2){
    short s = (c1 << 8) | (c2);
    return s;
}

class LetterCombo {
public:
    char first;
    char second;
    //int  count;

    LetterCombo(char c1, char c2)
        :first(c1), second(c2){}
    ~LetterCombo() {}

    bool operator<(const LetterCombo& rhs) const{
        short s1 = twoChar2Short(first, second);
        short s2 = twoChar2Short(rhs.first, rhs.second);
        return (s1 < s2);
    }

    bool operator==(const LetterCombo& r){
        return (first == r.first) && (second == r.second);
    }
};

class WordMarkovChain {
private:
    int _trainingSize;
    int _wordLengthAcc;
    std::map<LetterCombo, uint64_t> _map;

    LetterCombo selectNextCombo(char c){
        std::vector<LetterCombo> combos;
        std::vector<uint64_t> probs;
        auto mapIt = _map.begin();
        while(mapIt != _map.end()){
            if(mapIt->first.first == c){
                combos.push_back(mapIt->first);
                probs.push_back(mapIt->second);
                //std::cerr << "match" << std::endl;
            }
            ++mapIt;
        }
        if(combos.size() <= 1){
            return LetterCombo(0,0); // insufficent choices tell it to end gen
        }
        std::discrete_distribution<uint64_t> distrib(probs.begin(),probs.end());
        uint64_t idx = distrib(gen);
        return combos[idx];
    }
public:
    WordMarkovChain() {
        _trainingSize = 0;
        _wordLengthAcc = 0;
    }

    ~WordMarkovChain(){}

    void train(const std::string& w){
        _trainingSize++;
        // iterate and build list
        int sz = w.length();
        for(int i = 1; i < sz; i++) {
            _map[LetterCombo(w[i - 1], w[i])]++;
        }
        _wordLengthAcc += sz;
        //std::cerr << _map.size() << std::endl;
    }

    LetterCombo getRandomCombo(){
        std::map<LetterCombo, uint64_t>::iterator it = _map.begin();
        std::advance(it, randomZeroToN(_map.size()));
        return it->first;
    }

    std::string generate(){
        int sz = _wordLengthAcc / _trainingSize;
        std::string str;
        LetterCombo c = this->getRandomCombo();
        str += c.first;
        for(int i = 1; i < sz; i++){
            c = this->selectNextCombo(c.second);
            if(c == LetterCombo(0, 0)){
                return str;
            }
            str += c.first;
        }
        return str;
    }

    friend std::ostream& operator<<(std::ostream& out,
            const WordMarkovChain& c){
        out << "Trained on: " << c._trainingSize << " words" << std::endl;
        out << "Characters: " << c._wordLengthAcc << std::endl;
        out << "AvgWordLen: " << c._wordLengthAcc / c._trainingSize
            << std::endl;
        out << "Prob Keys : " << c._map.size() << std::endl;
        return out;
    }
};

/**************************************
*   Program Entry Point               *
**************************************/
int main(int argc, char** argv){
    std::ifstream infile("preprocd.txt");
    if(!infile.is_open()){
        std::cout << "Failed to open training data" << std::endl;
        return 0;
    }

    WordMarkovChain chain;
    // begin training of the markov chain
    std::string word;
    while(infile >> word){
        chain.train(word);
    }
    infile.close();
    std::cerr << chain << std::endl;
    std::cout << chain.generate() << std::endl;
}
