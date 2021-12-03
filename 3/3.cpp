#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>

std::vector<std::string> parse_input(std::string input_file) {
	std::string readed;
	std::vector<std::string> parsed_input;
	std::ifstream input(input_file);

	while (input >> readed) {
		parsed_input.push_back(readed);
	}

	return parsed_input;
}

int part_one(std::vector<std::string> input) {
	std::string gannma_rate;
	std::string epsilon_rate;

	for (int i = 0; i < input[0].size(); ++i) {
		int zeros = 0;
		int ones = 0;
		for (std::string position: input) {
			if (position[i] == '0') {
				zeros++;
			} else {
				ones++;
			}
		}

		if (zeros > ones) {
			gannma_rate.push_back('0');
		} else {
			gannma_rate.push_back('1');
		}
	}

	int gannma = stoi(gannma_rate, 0, 2);
	/*  TODO: ~operator works but it prints -23, need to check how convert it to positive int
	 *  int beta = ~ganma;
	std::cout << gannma << std::endl;
	std::cout << beta << std::endl;
	 * */

	for (char s: gannma_rate) {
		if (s == '0') {
			epsilon_rate.push_back('1');
		} else {
			epsilon_rate.push_back('0');
		}
	}

	std::cout << epsilon_rate << std::endl;
	int epsilon = std::stoi(epsilon_rate, 0, 2);

	std::cout << gannma << std::endl;
	std::cout << epsilon << std::endl;

	return gannma*epsilon;
}


int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}
	
	std::string input_file = argv[1];

	std::vector<std::string> input = parse_input(input_file);
	int sol1 = part_one(input);
	std::cout << "Solution to part 1 is: " << sol1 << std::endl;
	//std::pair<int, int> sol2 = part_two(input);
	return 0;
}
