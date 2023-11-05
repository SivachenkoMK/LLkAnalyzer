#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "grammar.h"
#include "transition.h"
#include "helper_class.h"
#include "sequence_analyzer.h"

using namespace std;

int main() {
    ifstream inputFile("../grammar.txt");
    if (!inputFile.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    string line;
    int rowCount = -1;

    vector<char> terminals;
    vector<char> nonTerminals;
    char Axiom;

    vector<transition> transitions;

    vector<char> resultingSequence;

    while (getline(inputFile, line)) {
        rowCount++;
        switch (rowCount) {
            case 0: {
                stringstream stream(line);
                while (stream >> ws) {
                    char token;
                    if (stream >> token) {
                        terminals.push_back(token);
                    }
                }
            } break;
            case 1: {
                stringstream steam(line);
                while (steam >> ws) {
                    char token;
                    if (steam >> token) {
                        nonTerminals.push_back(token);
                    }
                }
            } break;
            case 2: Axiom = line[0];  break;
            case 3: {
                stringstream steam(line);
                while (steam >> ws) {
                    char token;
                    if (steam >> token) {
                        resultingSequence.push_back(token);
                    }
                }
            } break;
            default: {
                char from = line[0];
                vector<char> to;
                string toSequence = line.substr(5);
                for (char symbol: toSequence) {
                    to.push_back(symbol);
                }
                transitions.emplace_back(from, to);
            }
        }
    }

    auto *inputGrammar = new grammar(Axiom, terminals, nonTerminals, transitions);
    //vector<vector<char>> firstS = inputGrammar->first('S', static_definitions::getK());

    unordered_map<char, vector<string>> firstK;
    unordered_map<char, vector<string>> followK;
    vector<string> valuesForS = { "a", "a+", "a*", "(a", "((" };
    vector<string> valuesForA = { "e", "+a", "+("};
    vector<string> valuesForB = { "a", "a*", "(a", "((" };
    vector<string> valuesForC = { "e", "*a", "*("};
    vector<string> valuesForD = { "a", "(a", "((" };
    firstK['S'] = valuesForS;
    firstK['A'] = valuesForA;
    firstK['B'] = valuesForB;
    firstK['C'] = valuesForC;
    firstK['D'] = valuesForD;
    valuesForS = {"e", "*"};
    valuesForA = {"e", ")"};
    valuesForB = {"+", "e", ")"};
    valuesForC = {"+", "e", ")"};
    valuesForD = {"+", "*", "e", ")"};
    followK['S'] = valuesForS;
    followK['A'] = valuesForA;
    followK['B'] = valuesForB;
    followK['C'] = valuesForC;
    followK['D'] = valuesForD;
//    vector<string> followS = inputGrammar->followK(2, 'S', firstK);
//    vector<string> followA = inputGrammar->followK(1, 'A', firstK);
//    vector<string> followB = inputGrammar->followK(2, 'B', firstK);
//    vector<string> followC = inputGrammar->followK(1, 'C', firstK);
//    vector<string> followD = inputGrammar->followK(1, 'D', firstK);
    auto *table = new helper_class(firstK, followK, *inputGrammar);
    table->printMainTable();

    auto* analyzer = new sequence_analyzer(Axiom, resultingSequence, table->getMainTable(), *inputGrammar);
    bool result = analyzer->analyzeSequence();
    return 0;
}