#include <iostream>
#include <fstream>
#include <string>
#include <vector>


static std::vector<std::string> g_all_keys;

static void InitKeys() {
	std::ifstream infile("all_kernels.txt");
	std::string line;
	while (std::getline(infile, line)) {
		g_all_keys.push_back(line);
	}
}