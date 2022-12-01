// Simon Liimatainen 2022
#include "Parser.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cassert>

using namespace std; // bad practice in general, but using this here to reduce typing

Parser::Parser(const std::string& filePath_) : filePath{filePath_}
{
	// check if file exists
	if (filesystem::exists(filePath)) { fileChecked = true; }
}


bool Parser::replace(const std::string key, uint32_t index, const std::string value)
{
	assert(fileChecked && "no file found");
	if (key.empty()) { return false; }
	// load file into memory
	ifstream fileInput;
	fileInput.open(filePath);
	if (fileInput.fail() || !fileChecked) { return false; }
	std::string fileContent;
	char c;
	while (fileInput >> std::noskipws >> c) { fileContent.push_back(c); }
	fileInput.close();
	if (fileContent.empty()) { return false; }

	// find key offsets
	std::vector<size_t> indices;
	size_t i = 0;
	while ((i = fileContent.find(key, i)) != std::string::npos) 
	{
		indices.push_back(i);
		i += key.length();
	}

	// select desired index occurrence offset
	size_t position = indices[index];
	std::cout << "\nPosition in file: " << position;

	auto insertPos = position + key.length();

	// calculate how many chars to remove (the old value) just look for next newline
	const auto wsPos = fileContent.find('\n', insertPos);
	size_t remCharsNum = wsPos - insertPos;

	// split content at insertion point
	std::string a = fileContent.substr(0, insertPos);
	const std::string b = fileContent.substr(insertPos + remCharsNum);
	// insert and recombine
	a.append(value);
	a.append(b);
	ofstream fileOutput;

	// opening stream with this constructor automatically erases the file
	fileOutput.open(filePath);
	if (fileOutput.fail()) { return false; }
	fileOutput << a; // write
	fileOutput.close();
	return true;
}