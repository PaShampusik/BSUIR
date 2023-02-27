#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main()
{
    ifstream file("example.cpp");
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    int num_operators = count_operators(code);
    int operand_count = count_operands(code);
    int unique_operators = count_unique_operators(code);
    int unique_operands = count_unique_operands(code);

    cout << "Total number of operators in the program: " << num_operators << endl;
    cout << "Total number of operands in the program: " << operand_count << endl;
    cout << "Total number of unique operands in the program: " << operand_count << endl;
    cout << "Total number of unique operators in the program: " << operand_count << endl;


    return 0;
}

int count_operands(string code) {
    int operand_count = 0;
    string code; // строка с кодом программы

    // считываем код программы из стандартного ввода (можно заменить на чтение из файла)
    getline(std::cin, code);

    // регул€рное выражение дл€ поиска операндов
    regex operand_regex(R"(\b[A-Za-z_][A-Za-z0-9_]*\b)");

    // итераторы дл€ перебора всех найденных операндов
    auto operand_begin = sregex_iterator(code.begin(), code.end(), operand_regex);
    auto operand_end = sregex_iterator();

    // перебираем все найденные операнды и увеличиваем счетчик
    for (auto i = operand_begin; i != operand_end; ++i) {
        operand_count++;
    }

    return operand_count;
}

int count_unique_operators(const std::string& program) {
    const unordered_set<string> operators = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||",
        "!", "&", "|", "^", "<<", ">>", "~", "++", "--", "+=", "-=", "*=", "/=", "%=",
        "<<=", ">>=", "&=", "|=", "^=", "?", ":", ",", "->*", ".*", ".", "->", "(", ")",
        "[", "]", "{", "}", ";", ":", "#", "##", "<%", "%>", "%:", "%:%:"
    };

    unordered_set<string> uniqueOperators;
    string currentOperator;

    for (size_t i = 0; i < program.size(); ++i) {
        const char c = program[i];
        if (isalpha(c) || isdigit(c) || c == '_') {
            // the current character is part of an identifier or keyword
            currentOperator += c;
        }
        else {
            // the current character is not part of an identifier or keyword
            if (!currentOperator.empty()) {
                if (operators.count(currentOperator) > 0) {
                    // we have found a unique operator
                    uniqueOperators.insert(currentOperator);
                }
                currentOperator.clear();
            }
        }
    }

    return uniqueOperators.size();
}

int count_operators(string code) {
    int count = 0;
    string operators[] = { "+", "-", "*", "/", "%", "++", "--", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "<<", ">>", "~", ".", "->", "()", "[]", "new", "delete", "sizeof", "typeid", "dynamic_cast", "static_cast", "const_cast", "reinterpret_cast", "if", "else", "switch", "case", "default", "while", "do", "for", "break", "continue", "goto", "return", "try", "throw", "catch", "const", "static", "extern", "inline", "friend", "typedef", "struct", "class", "union", "enum", "virtual", "private", "protected", "public" };
    for (int i = 0; i < code.length(); i++) {
        if (code[i] == '/' && code[i + 1] == '/') { // ignore comments
            while (code[i] != '\n' && i < code.length()) {
                i++;
            }
        }
        else if (code[i] == '/' && code[i + 1] == '*') { // ignore multi-line comments
            while (code[i] != '*' || code[i + 1] != '/') {
                i++;
            }
            i++;
        }
        else if (code[i] == '\"') { // ignore strings
            i++;
            while (code[i] != '\"' && i < code.length()) {
                i++;
            }
        }
        else if (code[i] == '\'') { // ignore characters
            i++;
            while (code[i] != '\'' && i < code.length()) {
                i++;
            }
        }
        else if (code[i] == '#') { // ignore preprocessor directives
            while (code[i] != '\n' && i < code.length()) {
                i++;
            }
        }
        else {
            for (int j = 0; j < sizeof(operators) / sizeof(string); j++) {
                if (code.substr(i, operators[j].length()) == operators[j]) {
                    count++;
                    i += operators[j].length() - 1;
                    break;
                }
            }
        }
    }
    return count;
}

int count_unique_operands(const string& program) {
    std::unordered_map<std::string, int> operands;
    std::stringstream ss(program);

    // ѕеребираем каждое слово в программе.
    std::string word;
    while (ss >> word) {
        // ≈сли слово не €вл€етс€ оператором или числом, то добавл€ем его в словарь операндов.
        if (word != "if" && word != "else" && word != "for" && word != "while" && word != "do" &&
            word != "switch" && word != "case" && word != "break" && word != "continue" &&
            word != "return" && word != "goto" && word != "+" && word != "-" && word != "*" &&
            word != "/" && word != "%" && word != "++" && word != "--" && word != "=" &&
            word != "+=" && word != "-=" && word != "*=" && word != "/=" && word != "%=" &&
            word != "==" && word != "!=" && word != ">" && word != "<" && word != ">=" &&
            word != "<=" && word != "&&" && word != "||" && word != "!" && word != "&" &&
            word != "|" && word != "^" && word != "~" && word != "<<" && word != ">>" &&
            word != "sizeof" && word != "new" && word != "delete" && word != "new[]" && word != "delete[]") {
            ++operands[word];
        }
    }

    return operands.size();
}