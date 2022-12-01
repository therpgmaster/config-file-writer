// Simon Liimatainen 2022
#include <iostream>
#include <string>
#include "Parser.h"

int main(int argc, char* argv[])
{
	std::cout << "Simon Liimatainen 2022\n";
	std::string fileName(argv[1]);
	std::string idx(argv[2]);
	std::string val(argv[3]);
	if (argc < 3) { std::cout << "\ntoo few arguments\n"; }

	Parser parser(fileName);
	const auto result = parser.replace("SocketIp=", stoi(idx), val);
	if (!result) { std::cout << "\n\nERROR\n"; }
	else { std::cout << "\n\nOperation done\n"; }


	return result;
}