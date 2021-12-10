#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

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

int get_fuel_acum_to_pos(std::vector<int> crab_positions, int position) {
	int cost = 0;

	for(int& i: crab_positions) {
		int acum = 0;
		int despl = abs(i-position);
		//Thats a sum equal to a triangular number, we take advantage of this.
		//for (int j=1; j <= despl; ++j)
		//	acum += j;
		acum = ((despl*despl)+despl)/2;
		cost += acum;
	}

	return cost;
}

int get_fuel_to_pos(std::vector<int> crab_positions, int position) {
	int cost = 0;

	for(int& i: crab_positions) {
		cost += abs(i-position);
	}

	return cost;
}

int part_one(std::vector<int> crab_positions){
	int cost = INFINITY;
	int current_cost = 0;
	int min = *(std::min_element(crab_positions.begin(), crab_positions.end()));
	int max = *(std::max_element(crab_positions.begin(), crab_positions.end()));
	std::vector<int> costs;

	for(int i=min; i<=max; ++i){
		current_cost = get_fuel_to_pos(crab_positions, i);
		if (current_cost < cost) {
			cost = current_cost;
		}
	}

	return cost;

}

int part_two(std::vector<int> crab_positions){
	int cost = INFINITY;
	int current_cost = 0;
	int min = *(std::min_element(crab_positions.begin(), crab_positions.end()));
	int max = *(std::max_element(crab_positions.begin(), crab_positions.end()));
	std::vector<int> costs;

	for(int i=min; i<=max; ++i){
		current_cost = get_fuel_acum_to_pos(crab_positions, i);
		if (current_cost < cost) {
			cost = current_cost;
		}
	}

	return cost;

}

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}
	
	std::string input_file = argv[1];
	std::vector<int> crab_positions = parse_input(input_file);
	int cost = part_one(crab_positions);
	std::cout << "Fuel spent to aling the crabs is: " << cost << std::endl;
	int cost_acum = part_two(crab_positions);
	std::cout << "Fuel spent to aling the crabs in part 2 is: " << cost_acum << std::endl;
}
