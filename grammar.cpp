//
// Created by mikhail.syvachenko on 28.10.2023.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include <algorithm>
#include <set>
#include <utility>
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

vector<char> grammar::first(char letter, int k) {
    return this->first(letter, k, {});
}

vector<char> grammar::first(char letter, int k, vector<char> processedNonTerminals) {
    if (find(processedNonTerminals.begin(), processedNonTerminals.end(), letter) != processedNonTerminals.end())
        return {};

    vector<char> currentTerminals = getTerminals();

    if (find(currentTerminals.begin(), currentTerminals.end(), letter) !=
        currentTerminals.end())
        return {letter};

    processedNonTerminals.push_back(letter);

    vector<transition> transitionsFromSpecifiedNonTerminal;
    vector<char> result;

    for (int i = 0; i < getTransitionsAmount(); i++) {
        if (this->transitions[i].getFrom() == letter)
            transitionsFromSpecifiedNonTerminal.push_back(this->transitions[i]);
    }

    for (int i = 0; i < transitionsFromSpecifiedNonTerminal.size(); i++) {
        int epsilonTrimmedIndex = 0;
        while (transitionsFromSpecifiedNonTerminal[i].getTo()[epsilonTrimmedIndex] == getEpsilon()) {
            epsilonTrimmedIndex++;
            if (epsilonTrimmedIndex == transitionsFromSpecifiedNonTerminal[i].getTo().size()) {
                epsilonTrimmedIndex = -1;
                break;
            }
        }

        if (epsilonTrimmedIndex == -1) {
            result.push_back(getEpsilon());
            continue;
        }

        vector<char> subFirst = first(transitionsFromSpecifiedNonTerminal[i].getTo()[epsilonTrimmedIndex], k,
                                      processedNonTerminals);
        for (char terminal: subFirst)
            result.push_back(terminal);
    }

    set<char> resultDistinctSet(result.begin(), result.end());
    vector<char> resultDistinct(resultDistinctSet.begin(), resultDistinctSet.end());

    return resultDistinct;
}

bool grammar::isEpsilon(vector<char> word) {
    vector<char> epsilonVector = getEpsilonVector();
    return word.size() == epsilonVector.size() && equal(word.begin(), word.end(), epsilonVector.begin());
}

vector<char> grammar::getEpsilonVector() {
    vector<char> epsilonVector = {'e'};
    return epsilonVector;
}

char grammar::getEpsilon() {
    return 'e';
}

#pragma clang diagnostic pop
