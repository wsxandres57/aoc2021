#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_vector(std::vector<int>& v){
	for(int& i: v)
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
		print_vector(intial_states);
	}

	return intial_states.size();
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}

	std::string input_file = argv[1];
	std::vector<int> initial_states = parse_input(input_file);
	print_vector(initial_states);
	int fishes = part_one(initial_states);
	
	std::cout << fishes << std::endl;

}
