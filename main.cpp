#include <iostream>
#include <fstream>
#include <vector>
#include "Lexer/Token.h"
#include "Lexer/Lexer.cpp"
#include "Parser.h"
#include "Lexer/Scheme.h"
#include "Interpreter.h"
#include "DatalogProgram.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <input file>" << endl;
        return -1;
    };

    std::ifstream infile(argv[1]);
    if (!infile) {
        cout << "Unable to open " << argv[1] << " for input" << endl;
        return -1;
    }

    // use Lexer to scan file and create tokens
    stringstream fileStream;
    fileStream << infile.rdbuf();
    string line = fileStream.str();
    auto lexer = Lexer(line);
    vector<Token> tokens = lexer.scanFile();

    // use Parser to parse tokens and create datalogProgram
    auto parser = Parser(tokens);
    auto datalogProgram = DatalogProgram();
    parser.datalogProgram(datalogProgram);

    // use Interpreter to evaluate datalogProgram
    auto interpreter = Interpreter(datalogProgram);
    interpreter.evaluate();
    infile.close();

    return 0;
}