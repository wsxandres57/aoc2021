#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_vector(std::vector<u_int>& v){
	for(u_int& i: v)
		std::cout << i << ", ";

	std::cout << std::endl;
}

std::vector<int> parse_input(std::string filename){
	std::vector<int> initial_states;
	std::string parsed;
	std::string line;
	std::ifstream input(filename);
	std::getline(input, line);

	for(char& c: line){
		if (c == ',') {
			initial_states.push_back(std::stoi(parsed));
			parsed.clear();
		} else {
			parsed.push_back(c);
		}
	}
	
	initial_states.push_back(std::stoi(parsed));
	return initial_states;
}

int part_one(std::vector<int> intial_states){
	int i;
	for (i = 0; i < 80; ++i) {
		size_t fishes = intial_states.size();
		for(int j=0; j < fishes; ++j) {
			if (intial_states[j] == 0) {
				intial_states[j] = 6;
				intial_states.push_back(8);
			} else {
				intial_states[j] -= 1;
			}
		}
	}

	return intial_states.size();
}

long long int part_two(std::vector<int> initial_states){
	std::vector<long long int> fishes_by_state = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for(int& i: initial_states)
		fishes_by_state[i] += 1;

	for (int i = 0; i < 256; ++i) {
		long long int aux = fishes_by_state[8];
		long long int aux2 = fishes_by_state[7];
		long long int aux3 = fishes_by_state[6];
		long long int aux4 = fishes_by_state[5];
		long long int aux5 = fishes_by_state[4];
		long long int aux6 = fishes_by_state[3];
		long long int aux7 = fishes_by_state[2];
		long long int aux8 = fishes_by_state[1];
		long long int aux9 = fishes_by_state[0];

		fishes_by_state[8] = aux9;
		fishes_by_state[7] = aux;
		fishes_by_state[6] = aux2 + aux9;
		fishes_by_state[5] = aux3;
		fishes_by_state[4] = aux4;
		fishes_by_state[3] = aux5;
		fishes_by_state[2] = aux6;
		fishes_by_state[1] = aux7;
		fishes_by_state[0] = aux8;
	}

	return std::accumulate(fishes_by_state.begin(), fishes_by_state.end(), 0LL);

}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}

	std::string input_file = argv[1];
	std::vector<int> initial_states = parse_input(input_file);
	int fishes = part_one(initial_states);
	std::cout << fishes << std::endl;

	long long int fishes2 = part_two(initial_states);
	std::cout << fishes2 << std::endl;

}
