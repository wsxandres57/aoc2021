#include <algorithm>
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

std::string get_ganma_rate(std::vector<std::string> input) {
	std::string gannma_rate;

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

	return gannma_rate;
}

std::string get_epsilon_rate(std::string ganma_rate) {
	std::string epsilon_rate;

	for (char s: ganma_rate) {
               if (s == '0') {
                       epsilon_rate.push_back('1');
               } else {
                       epsilon_rate.push_back('0');
               }
       }

	return epsilon_rate;
}

std::string get_oxigen_rate(std::vector<std::string> input) {
	// this is the worst solution in order, I am not taking advantage of part 1
	std::vector<std::string> sol = input;
	std::vector<std::string> aux;
	
	for (int i = 0; i < input.at(0).size(); ++i) {
		int zeros = 0;
		int ones = 0;
		for (std::string position: sol) {
			if (position.at(i) == '1'){
				ones++;
			} else {
				zeros++;
			}
		}

		if (ones > zeros) {
			std::copy_if(sol.begin(), sol.end(), std::back_inserter(aux),
					[i](std::string sol){return sol.at(i) == '1';});
		} else if (zeros > ones) {
			std::copy_if(sol.begin(), sol.end(), std::back_inserter(aux),
					[i](std::string sol){return sol.at(i) == '0';});
		} else {
			std::copy_if(sol.begin(), sol.end(), std::back_inserter(aux),
					[i](std::string sol){return sol.at(i) == '1';});
		}

		sol = aux;
		aux.clear();
	}

	return sol[0];
}

std::string get_co2_rate(std::vector<std::string> input) {
	// this is the worst solution in order, I am not taking advantage of part 1
	std::vector<std::string> sol = input;
	std::vector<std::string> aux;
	
	for (int i = 0; i < input.at(0).size() && sol.size() > 1; ++i) {
		int zeros = 0;
		int ones = 0;
		for (std::string position: sol) {
			if (position.at(i) == '1'){
				ones++;
			} else {
				zeros++;
			}
		}

		if (ones < zeros) {
			std::copy_if(sol.begin(), sol.end(), std::back_inserter(aux),
					[i](std::string sol){return sol.at(i) == '1';});
		} else if (zeros < ones) {
			std::copy_if(sol.begin(), sol.end(), std::back_inserter(aux),
					[i](std::string sol){return sol.at(i) == '0';});
		} else {
			for (std::string s: sol)
				std::cout << s << std::endl;
			std::copy_if(sol.begin(), sol.end(), std::back_inserter(aux),
					[i](std::string sol){return sol.at(i) == '0';});
		}

		sol = aux;
		aux.clear();
	}

	return sol[0];
}


int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}
	
	std::string input_file = argv[1];

	std::vector<std::string> input = parse_input(input_file);
	std::string ganma_rate = get_ganma_rate(input);
	std::string epsilon_rate = get_epsilon_rate(ganma_rate);

	int ganma = stoi(ganma_rate, 0, 2);
	/*  TODO: ~operator works but it prints -23, need to check how convert it to positive int
	 *  int beta = ~ganma;
	std::cout << gannma << std::endl;
	std::cout << beta << std::endl;
	 * */
	int epsilon = stoi(epsilon_rate, 0, 2);

	int sol1 = ganma*epsilon;
	std::cout << "Solution to part 1 is: " << sol1 << std::endl;

	std::string oxigen_rate = get_oxigen_rate(input);
	std::string co2_rate = get_co2_rate(input);
	std::cout << oxigen_rate << std::endl;
	std::cout << co2_rate << std::endl;

	int oxigen = stoi(oxigen_rate, 0, 2);
	int co2 = stoi(co2_rate, 0, 2);
	int sol2 = oxigen*co2;
	//std::cout << oxigen << std::endl;
	//std::cout << co2 << std::endl;
	std::cout << "Solution to part 2 is: " << sol2 << std::endl;


	return 0;
}
