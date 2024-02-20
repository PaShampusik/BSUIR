//
//Lexer of Golang, written by Shchirov Pavel. Regex were restrickted.
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>

//keywords set
std::unordered_set<std::string> keywords = { "break", "default", "func", "interface", "select",
								   "case", "defer", "go", "map", "struct",
								   "chan", "else", "goto", "package", "switch",
								   "const", "fallthrough", "if", "range", "type",
								   "continue", "for", "import", "return", "var",
								   "bool", "byte", "complex64", "complex128",
								   "float32", "float64", "int", "int8", "int16",
								   "int32", "int64", "rune", "string", "uint",
								   "uint8", "uint16", "uint32", "uint64", "uintptr" };

// Operators set
std::unordered_set<std::string> operators = { "+", "-", "*", "/", "%", "=", "==", "!=", ":=",
									"<", ">", "<=", ">=", "&&", "||", "!", "+=", "-=", "*=", "/=",
									"&", "|", "^", "<<", ">>", "++", "--" };

std::unordered_set<std::string> punctuators = { "{", "}", "(", "[", ",", "\"", ")", "]", ";" };

std::vector<std::string> tokenTypes = { "Keyword", "Operator", "Operand", "Punctuator", "Constant" };

enum TokenType {
	KEYWORD,
	OPERATOR,
	OPERAND,
	PUNCTUATOR,
	CONSTANT
};

static void determineType(std::string currentLexeme, std::string lastLexeme);
static std::pair<std::string, int> findConstant(const std::string& code, size_t index, char ender);
static std::pair<bool, std::string> lecsicError(std::string str, std::unordered_set<std::string> keywords);
static std::pair<bool, std::string> overflowError(std::string str, std::unordered_set<std::string> keywords);

/*TODO
type, через последнюю лексему
func,
нужно в токене хранить айдишник, по нему же потом можно и область видимости ебнуть
константы через последнюю лексему
аргументы функции парсить через find constant, но учитывать запятую
*/

struct Token {
	TokenType type;
	std::string lexeme;
	std::string err = "";
};

bool isWhitespace(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

bool isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

//TOKENS//////////////////
std::vector<Token> tokens;
//TOKENS//////////////////

std::vector<Token> lex(const std::string& code) {
	std::string currentLexeme, lastLexeme;
	auto constant = std::pair < std::string, int>();

	for (size_t i = 0; i < code.length(); ++i) {
		char c = code[i];
		constant = std::pair < std::string, int>();
		if (isWhitespace(c)) {
			determineType(currentLexeme, lastLexeme);
			std::swap(currentLexeme, lastLexeme);
			currentLexeme.clear();
		}
		else {
			if (punctuators.contains(std::string(1, c))) {
				if (c == '(') {
					determineType(currentLexeme, lastLexeme);
					constant = findConstant(code, i, ')');
				}
				else if (c == '[') {
					determineType(currentLexeme, lastLexeme);
					constant = findConstant(code, i, ']');
				}
				else if (c == ';') {
					determineType(currentLexeme, lastLexeme);
					determineType(std::string(";"), currentLexeme);
				}
				else if (c == '\"') {
					determineType(currentLexeme, lastLexeme);
					constant = findConstant(code, i, '\"');
				}
				else if (c == '\{' || c == '\}') {
					determineType(currentLexeme, lastLexeme);
				}
				currentLexeme = "";
				i = (constant.second == 0) ? i : (constant.second + 1);

			}
			else {
				currentLexeme += c;
			}
		}
	}

	return tokens;
}

static void determineType(std::string currentLexeme, std::string lastLexeme) {
	if (!currentLexeme.empty()) {
		Token token;
		token.lexeme = currentLexeme;
		lastLexeme = currentLexeme;

		if (keywords.contains(currentLexeme)) {
			token.type = KEYWORD;
		}
		else if (operators.contains(currentLexeme)) {
			token.type = OPERATOR;
		}
		else if (punctuators.contains(currentLexeme)) {
			token.type = PUNCTUATOR;
		}
		else {
			if ((currentLexeme[currentLexeme.length() - 1] == '+' && currentLexeme[currentLexeme.length() - 2] == '+') || (currentLexeme[currentLexeme.length() - 1] == '-' && currentLexeme[currentLexeme.length() - 2] == '-')) {
				Token newtoken;
				std::string newlexema = "";
				for (int i = currentLexeme.length() - 2; i < currentLexeme.length(); i++) {
					newlexema += currentLexeme[i];
				}
				newtoken.lexeme = newlexema;
				newtoken.type = OPERATOR;
				token.lexeme = currentLexeme.erase(currentLexeme.length() - 2);
				token.type = OPERAND;
				tokens.push_back(token);
				token = newtoken;
				currentLexeme = token.lexeme;
			}
			auto result = lecsicError(currentLexeme, keywords);
			if (result.first) {
				token.type = KEYWORD;
				token.err = "ERROR! Did you mean " + result.second + "? You have lecsic error, writing " + currentLexeme;
			}
			token.type = OPERAND;

			auto result2 = overflowError(currentLexeme, keywords);
			if (result2.first) {
				token.type = KEYWORD;
				token.err = "Warning! Did you mean " + result2.second + "? You have lecsic variety, writing " + currentLexeme;
			}

			auto result3 = overflowError(currentLexeme, operators);
			if (result3.first) {
				token.type = KEYWORD;
				token.err = "Warning! Did you mean " + result3.second + "? You have lecsic variety, writing " + currentLexeme;
			}

		}

		tokens.push_back(token);
		currentLexeme.clear();
	}
	return;
}

static std::pair <std::string, int> findConstant(const std::string& code, size_t index, char ender) {
	std::string constant;
	std::string opener = std::string(1, code[index]);
	index++;
	while (code[index] != ender) {
		constant += code[index];
		index++;
	}
	determineType(opener, "");
	determineType(constant, opener);
	determineType(std::string(1, ender), constant);
	return std::pair(constant, index);
}

static std::pair<bool, std::string> lecsicError(std::string str, std::unordered_set<std::string> keywords) {
	std::unordered_map<char, int> frequency, copy;
	for (int i = 0; i < str.length(); i++) {
		frequency[str[i]]++;
	}
	for (auto const& x : keywords) {
		if (str.length() == x.length()) {
			copy = frequency;
			for (int i = 0; i < str.length(); i++) {
				copy[x[i]]--;
			}
			for (auto const& y : copy) {
				if (y.second == 0) {
					continue;
				}
				else {
					goto mark;
				}

			}
			return std::pair<bool, std::string>(true, x);
		}
	mark:
		continue;
	}
	return std::pair<bool, std::string>(false, "");
}

static std::pair<bool, std::string> overflowError(std::string str, std::unordered_set<std::string> keywords) {
	std::string newstring = "";
	for (int i = 0; i < str.length(); i++) {
		for (int j = i; j < str.length(); j++) {
			newstring += str[j];
			if (keywords.contains(newstring) && abs((int)(newstring.length() - str.length())) < 2) {
				return std::pair<bool, std::string>(true, newstring);
			}
		}
		newstring = "";
	}
	return std::pair<bool, std::string>(false, "");
}

void SetConsoleRedColor() {
	std::cout << "\033[31m"; 
}

void SetConsoleYellowColor() {
	std::cout << "\033[33m"; 
}


// Функция для сброса цвета текста в консоли в стандартный
void ResetConsoleColor() {
	std::cout << "\033[0m";
}

int main() {

	std::ifstream inputFile("test.txt");

	if (!inputFile) {
		std::cerr << "Failed to open file." << std::endl;
		return 1;
	}

	std::string code;
	std::string line;

	while (std::getline(inputFile, line)) {
		code += line + '\n';
	}

	inputFile.close();

	std::vector<Token> tokens = lex(code);

	auto i = 0;
	for (const Token& token : tokens) {
		std::cout << i << " Type: " << tokenTypes[token.type] << ", Lexeme: " << token.lexeme << " ";
		if (token.err != "") {
			SetConsoleRedColor(); // Покрасить текст в красный цвет
			if (token.err[0] == 'W') {
				SetConsoleYellowColor(); // Покрасить текст в красный цвет
			}
			std::cout << token.err;
			ResetConsoleColor(); // Вернуть цвет текста в стандартный
		}
		std::cout << std::endl;
		i++;
	}

	return 0;
}