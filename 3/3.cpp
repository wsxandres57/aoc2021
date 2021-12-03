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

std::string get_oxigen_rate(std::vector<std::string> input, std::string ganma_rate, bool epsilon) {
	std::vector<std::string> aux = input;
	std::vector<std::string> aux2;
	int zeros = 0;
	int ones = 0;
	std::string oxigen_rate;


	for (int i=0; i < ganma_rate.size()-1; ++i) {
		std::copy_if(aux.begin(), aux.end(), std::back_inserter(aux2), 
				[i, ganma_rate](std::string aux){ return aux[i] == ganma_rate[i]; });
		aux = aux2;
		std::cout << aux.size() << std::endl;
		aux2.clear();
	}

	if (aux.size() == 2){ 
		char s;
		if (epsilon) {
			s = '0';
		} else {
			s = '1';
		}

		for (int i=0; i < aux.size(); ++i) {
			if (aux[i][ganma_rate.size()-1] == s) {
				oxigen_rate = aux[i];
			}
		}
	} else {
		std::cout << aux.size() << std::endl;
		int zeros = 0;
		int ones = 0;
		for (int i=0; i < aux.size(); ++i) {
			std::cout << aux[i] << std::endl;
			if (aux[i][ganma_rate.size()-1] == '1') {
				ones++;
			} else {
				zeros++;
			}
		}
		
		//std::cout << ones << std::endl;
		//std::cout << zeros << std::endl;

		//char to_find = (ones>zeros) ? '0':'1';
		//for (int i=0; i < aux.size(); ++i) {
			//if (aux[i][ganma_rate.size()-1] == to_find) {
				//oxigen_rate = aux[i];
			//}
		//}

	}
	
	std::cout << "hola" << std::endl;

	return oxigen_rate;
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

	std::string oxigen_rate = get_oxigen_rate(input, ganma_rate, false);
	std::string co2_rate = get_oxigen_rate(input, epsilon_rate, true);
	std::cout << oxigen_rate << std::endl;
	std::cout << co2_rate << std::endl;

	//int oxigen = stoi(oxigen_rate, 0, 2);
	//int co2 = stoi(co2_rate, 0, 2);
	//int sol2 = oxigen*co2;
	//std::cout << oxigen << std::endl;
	//std::cout << co2 << std::endl;
	//std::cout << "Solution to part 2 is: " << sol2 << std::endl;


	return 0;
}
