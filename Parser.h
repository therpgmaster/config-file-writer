// Simon Liimatainen 2022
#pragma once

#include <string>
#include <vector>

class Parser
{
public:
	Parser(const std::string& filePath_);
	// searches for a key string in the file, uses index if multiple exist, and replaces the value following it, returns true if successful
	bool replace(const std::string key, uint32_t index, const std::string value);

private:
	std::string filePath;
	bool fileChecked = false;

};
