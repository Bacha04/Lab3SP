#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <iomanip>

using namespace std;

enum TokenType {
    TOKEN_COMMENT,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_KEYWORD,
    TOKEN_VARIABLE,
    TOKEN_RESERVED,
    TOKEN_FUNCTION,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER,
    TOKEN_IDENTIFIER,
    TOKEN_UNKNOWN
   

};

map<TokenType, string> tokenTypeNames = {
    {TOKEN_COMMENT, "Comment"},
    {TOKEN_STRING, "String"},
    {TOKEN_NUMBER, "Number"},
    {TOKEN_KEYWORD, "Keyword"},
    {TOKEN_VARIABLE, "Variable"},
    {TOKEN_RESERVED, "Reserved"},
    {TOKEN_FUNCTION, "Function"},
    {TOKEN_OPERATOR, "Operator"},
    {TOKEN_DELIMITER, "Delimiter"},
    {TOKEN_IDENTIFIER, "Identifier"},
    {TOKEN_UNKNOWN, "Unknown"}
};


void processToken(const string& token, TokenType tokenType) {
    cout << setw(50) << left << token << setw(50) << left << tokenTypeNames[tokenType] << endl;
}

void tokenizePHP(const string& code) {
    regex numberRegex(R"(\b\d+(\.\d+)?\b|0x[0-9A-Fa-f]+)");
    regex stringRegex(R"(".*?")");
    regex commentRegex(R"(\/\*[\s\S\n]*?\*\/|\/\/.*$)");
    regex unixComment(R"(#.*$)");
    regex keywordRegex(R"(\b(if|else|while|for|try|catch|new|throw|foreach|as|return|never|parent)\b)");
    regex reservedRegex(R"(\b(function|echo|class|void|enum|case|print|extends|implements|final|private|public|trait|interface|private|protected|namespace|const|true|false|array|Exception)\b)");
    regex powerOperator(R"(\*\*)");
    regex dotOperator(R"(\.\=)");
    regex additionalOperators(R"(\+=|-=|/=|%=|==|===|\*=|!=|<=|>=|<=>|<>|!==|&&|!|\?{2}|and|or|xor|->|=>|\+\+|\-\-)");
    regex singleOperators(R"(\+|-|\*|/|%|=|&|\?)");
    regex delimiterRegex(R"([;,)({}\[\]])");
    regex variablesRegex(R"(\$[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*)");
    regex functionRegex(R"(\b[a-zA-Z_][a-zA-Z0-9_]*\s*\()");

    smatch match;
    string rest = code;
    cout << setw(50) << left << "Token" << setw(50) << left << "Type" << endl;
    cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

    while (regex_search(rest, match, commentRegex)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_COMMENT);
        rest.erase(start_position, match.str().length());
    }
    while (regex_search(rest, match, unixComment)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_COMMENT);
        rest.erase(start_position, match.str().length());
    }
    cout << "String" << endl;
    while (regex_search(rest, match, stringRegex)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_STRING);
        rest.erase(start_position, match.str().length());
    }
    cout << "Number" << endl;
    while (regex_search(rest, match, numberRegex)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_NUMBER);
        rest.erase(start_position, match.str().length());
    }
    cout << "Keyword" << endl;
    while (regex_search(rest, match, keywordRegex)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_KEYWORD);
        rest.erase(start_position, match.str().length());
    }
    cout << "Variable" << endl;
    while (regex_search(rest, match, variablesRegex)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_VARIABLE);
        rest.erase(start_position, match.str().length());
    }
    cout << "Reserved" << endl;
    while (regex_search(rest, match, reservedRegex)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_RESERVED);
        rest.erase(start_position, match.str().length());
    }
    cout << "Function" << endl;
    while (regex_search(rest, match, functionRegex))
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_FUNCTION);
        rest.erase(start_position, match.str().length());
    }
    //OPERATORS
    cout << "Operators" << endl;
    while (regex_search(rest, match, powerOperator)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_OPERATOR);
        rest.erase(start_position, match.str().length());
    }
    while (regex_search(rest, match, dotOperator)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_OPERATOR);
        rest.erase(start_position, match.str().length());
    }
    while (regex_search(rest, match, additionalOperators)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_OPERATOR);
        rest.erase(start_position, match.str().length());
    }
    while (regex_search(rest, match, singleOperators)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_OPERATOR);
        rest.erase(start_position, match.str().length());
    }
    cout << "Delimiters" << endl;
    while (regex_search(rest, match, delimiterRegex)) 
    {
        int start_position = rest.find(match.str());
        processToken(match.str(), TOKEN_DELIMITER);
        rest.erase(start_position, match.str().length());
    }

    cout << "Errors" << endl;

    cout << rest;

}

int main() {
   
    ifstream inputFile("test.txt");
    string code((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    tokenizePHP(code);

    return 0;
}