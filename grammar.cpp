//
// Created by mikhail.syvachenko on 28.10.2023.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "grammar.h"

grammar::grammar(char axiom, vector<char> terminals, vector<char> nonTerminals, vector<transition> transitions) {
    this->axiom = axiom;
    this->terminals = std::move(terminals);
    this->nonTerminals = std::move(nonTerminals);
    this->transitions = std::move(transitions);
    this->nonTerminalAmount = int(getNonTerminals().size());
    this->terminalAmount = int(getTerminals().size());
    this->transitionsAmount = int(getTransitions().size());
}

grammar::~grammar() = default;

vector<char> grammar::getTerminals() {
    return terminals;
}

vector<char> grammar::getNonTerminals() {
    return nonTerminals;
}

vector<transition> grammar::getTransitions() {
    return transitions;
}

int grammar::getTerminalsAmount() const {
    return terminalAmount;
}

int grammar::getNonTerminalsAmount() const {
    return nonTerminalAmount;
}

int grammar::getTransitionsAmount() const {
    return transitionsAmount;
}

char grammar::getAxiom() const {
    return axiom;
}

vector<vector<char>> grammar::first(char letter, int k) {
    auto resultToConcatenate = this->first(letter, k, {});
    printVector(resultToConcatenate);

    vector<vector<char>> vector;
    return vector;
}

// Return format: first layer - terminals for a word, second layer - sequence of words, third layer - sequence for all combinations
vector<vector<vector<char>>> grammar::first(char letter, int k, vector<char> processedNonTerminals) {
    if (recursiveIterationBeyondLimit(letter, processedNonTerminals, k))
        return {{{}}};

    vector<char> allTerminals = getTerminals();

    if (find(allTerminals.begin(), allTerminals.end(), letter) !=
        allTerminals.end())
        return { { {letter} } };

    processedNonTerminals.push_back(letter);

    vector<transition> transitionsFromSpecifiedNonTerminal;

    for (int i = 0; i < getTransitionsAmount(); i++) {
        if (this->transitions[i].getFrom() == letter)
            transitionsFromSpecifiedNonTerminal.push_back(this->transitions[i]);
    }

    vector<vector<vector<char>>> result;
    for (int i = 0; i < transitionsFromSpecifiedNonTerminal.size(); i++) {
        if (static_definitions::isEpsilon(transitions[i].getTo())) {
            result.push_back({{static_definitions::getEpsilon()}});
            continue;
        }
        // Combine result into -> {
        // A -> BC (call B, call C) return { [ {c, d}, {e, f} ], [ {c, d}, {g} ] }
        // B - cd return { {c, d} }
        // C -> ef return { {e, f} }
        // C -> g return { {g} }

        for (int j = 0; j <= transitionsFromSpecifiedNonTerminal.size() && j < k; j++) {
            vector<vector<char>> subResults;
            char letterFrom = transitionsFromSpecifiedNonTerminal[i].getFrom();
            char currentLetter = transitionsFromSpecifiedNonTerminal[i].getTo()[j];

            cout << "Going from " << letterFrom << " to " << currentLetter << endl;
            vector<vector<vector<char>>> sequenceOfFirstForThisLetter = first(currentLetter, k,
                                                                              processedNonTerminals);

            vector<char> terminalLetters;
            for (const auto &firstForLetter: sequenceOfFirstForThisLetter) {
                for (const auto &word: firstForLetter) {
                    for (auto terminalLetter: word) {
                        terminalLetters.push_back(terminalLetter);
                    }
                }
                if (!terminalLetters.empty())
                    subResults.push_back(terminalLetters);
            }

            if (!subResults.empty())
                result.push_back(subResults);

            cout << (int) letterFrom << " " << letterFrom << ": ";
            printVector(result);
            cout << endl;
        }
    }

    vector<vector<char>> distinctResults;
    // Concatenate stuff
    // Introduce distinct stuff

    return result;
}

//vector<vector<char>> grammar::concatenateResults(vector<vector<vector<char>>> stepsResult, int k) {
//    vector<char> result;
//
//    for (const auto& sequence : stepsResult)
//    {
//        result.push_back('{');
//        for (const auto& element : sequence)
//        {
//            result.push_back(element);
//        }
//        result.push_back('}');
//    }
//
//    for (const auto letter : result)
//    {
//        cout << letter;
//    }
//}

void grammar::printVector(const vector<vector<vector<char>>>& vec) {
    std::cout << "{ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "[ ";
        for (size_t j = 0; j < vec[i].size(); ++j) {
            std::cout << "{ ";
            for (size_t k = 0; k < vec[i][j].size(); ++k) {
                std::cout << "'" << vec[i][j][k] << "'";
                if (k != vec[i][j].size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << " }";
            if (j != vec[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " ]";
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " }" << std::endl;
}

bool grammar::recursiveIterationBeyondLimit(char letter, vector<char> processedNonTerminals, int k) {
    int i = 0;
    for (auto element : processedNonTerminals) {
        if (element == letter)
            i++;
    }
    return i >= k;
}

#pragma clang diagnostic pop
