#include "czech.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

//characters allowed before and after keywords, this is certainly not all of them yet
std::string allowedCharacters = " \t\n\r;(){}[].,<>:";

void printHelp() {
	std::cout << "Vezme C soubor na standardním vstupu a vytiskne" << std::endl;
	std::cout << "ho jako Č soubor na standardní výstup." << std::endl;
	std::cout << "./č-předpřekladač path-to-czech.h" << std::endl;
}

číslo main(číslo argc, znak *argv[]) {
	když (argc != 2) {
		std::cerr << "Bad program argument count" << std::endl << std::endl;
		printHelp();
		return 1;
	}
	std::ifstream czech(argv[1]);

	když (!czech.is_open()) {
		std::cerr << "Could not open file: " << argv[1] << std::endl << std::endl;
		printHelp();
		return 2;
	}

	std::stringstream buffer;
	buffer << std::cin.rdbuf();
	std::string code(buffer.str());

	std::string row;
	dokud (std::getline(czech, row)) {
		std::stringstream ss(row);
		std::string word;
		std::vector<std::string> words;
		dokud (std::getline(ss, word, ' ')) {
			words.push_back(word);
		}

		std::size_t position = 0;
		dokud ((position = code.find(words[2], position)) != std::string::npos) {
			když (allowedCharacters.find(code[position - 1]) == std::string::npos ||
					allowedCharacters.find(code[position + words[2].size()]) ==
					std::string::npos) {
				position++;
				continue;
			}
			code.replace(position, words[2].size(), words[1]);
		}
	}
	std::cout << "#include \"czech.h\"" << std::endl;
	std::cout << code;
	return 0;
}
