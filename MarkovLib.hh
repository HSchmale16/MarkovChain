#ifndef MARKOV_LIB_HH_INC
#define MARKOV_LIB_HH_INC

#include <vector>
#include <random>
#include <map>
#include <iterator>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>

static std::default_random_engine gen =
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
    /// The number of words this markov chain has been trained on.
    int _trainingSize;
    /// The number of bytes that have been used to train this chain.
    int _wordLengthAcc;
    /// Contains the probabilities of the machine going to another state
    std::map<LetterCombo, uint64_t> _map;

    LetterCombo selectNextCombo(char c){
        std::vector<LetterCombo> combos;
        std::vector<uint64_t> probs;
        auto mapIt = _map.begin();
        while(mapIt != _map.end()){
            if(mapIt->first.first == c){
                combos.push_back(mapIt->first);
                probs.push_back(mapIt->second);
            }
            ++mapIt;
        }
        std::discrete_distribution<uint64_t> distrib(probs.begin(),probs.end());
        uint64_t idx = distrib(gen);
        return combos[idx];
    }

    /**\brief Prints the probability of a certain letter transforming into
     * another letter.
     * \param c the letter value to select from.
     * \param out The stream to write to
     */
    void printLetterProbs(char c, std::ostream& out){
        std::vector<LetterCombo> combos;
        std::vector<uint64_t> probs;
        auto mapIt = _map.begin();
        while(mapIt != _map.end()){
            if(mapIt->first.first == c){
                combos.push_back(mapIt->first);
                probs.push_back(mapIt->second);
            }
            ++mapIt;
        }
        uint64_t acc = 0; // accumlater
        for(uint64_t i : probs){
            acc += i;
        }
        // print it out
        for(size_t i = 0; i < combos.size(); i++){
            double per = (double)probs[i]/(double)acc;
            out << c << ',' << combos[i].second << ','
                << per << std::endl;
        }
    }
public:
    WordMarkovChain() {
        _trainingSize = 0;
        _wordLengthAcc = 0;
    }

    ~WordMarkovChain(){}

    /**\brief Train the chain from a word
     */
    void train(const std::string& w){
        _trainingSize++;
        // iterate and build list
        int sz = w.length();
        for(int i = 1; i < sz; i++) {
            _map[LetterCombo(w[i - 1], w[i])]++;
        }
        _map[LetterCombo(w[w.length() - 1], 0)]++;
        _wordLengthAcc += sz;
        //std::cerr << _map.size() << std::endl;
    }

    LetterCombo getRandomCombo(){
        std::map<LetterCombo, uint64_t>::iterator it = _map.begin();
        std::advance(it, randomZeroToN(_map.size()));
        return it->first;
    }

    /**\brief Generates a word from the internal chain.
     * \return A string of the word being generated.
     */
    std::string generate(){
        std::string str;
        LetterCombo c = this->getRandomCombo();
        str += c.first;
        for(;;){
            c = this->selectNextCombo(c.second);
            str += c.first;
            if(c.second == 0){
                return str;
            }
        }
        return str;
    }

    void printProbsGraph(std::ostream& out);

    friend std::ostream& operator<<(std::ostream& out,
            const WordMarkovChain& c);
};

void WordMarkovChain::printProbsGraph(std::ostream& out){
    for(char c = 'A'; c <= 'Z'; c++){
        this->printLetterProbs(c, out);
    }
}

std::ostream& operator<<(std::ostream& out, const WordMarkovChain& c){
    out << "Trained on: " << c._trainingSize << " words" << std::endl;
    out << "Characters: " << c._wordLengthAcc << std::endl;
    out << "AvgWordLen: " << c._wordLengthAcc / c._trainingSize
        << std::endl;
    out << "Prob Keys : " << c._map.size() << std::endl;
    return out;
}

#endif //MARKOV_LIB_HH_INC
