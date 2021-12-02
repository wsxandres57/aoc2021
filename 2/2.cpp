#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct Indication {
	int steps;
	std::string direction;
};

std::vector<Indication> parse_input(std::string file_path){
	int steps;
	std::string direction;
	Indication parsed_indication;
	std::ifstream infile(file_path);
	std::vector<Indication> directions;

	while (infile >> direction >> steps) {
		parsed_indication.steps = steps;
		parsed_indication.direction = direction;

		directions.push_back(parsed_indication);
	}

	return directions;
}

std::pair<int, int> part_one(std::vector<Indication> input_directions){
	std::pair<int, int> coordinates;
	coordinates.first = 0;
	coordinates.second = 0;

	for (Indication indication: input_directions) {
		if (indication.direction == "down") {
			coordinates.second += indication.steps;
		} else if (indication.direction == "up") {
			coordinates.second -= indication.steps;
		} else {
			coordinates.first  += indication.steps;
		}
	}

	return coordinates;
}

std::pair<int, int> part_two(std::vector<Indication> input_directions){
	int aim = 0;
	std::pair<int, int> coordinates;
	coordinates.first = 0;
	coordinates.second = 0;

	for (Indication indication: input_directions) {
		if (indication.direction == "down") {
			aim += indication.steps;
		} else if (indication.direction == "up") {
			aim -= indication.steps;
		} else {
			coordinates.first  += indication.steps;
			coordinates.second += aim * indication.steps;
		}
	}

	return coordinates;
}

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}
	
	std::string input_file = argv[1];

	std::vector<Indication> input = parse_input(input_file);
	std::pair<int, int> sol1 = part_one(input);
	std::pair<int, int> sol2 = part_two(input);
	std::cout << "X: " << sol1.first << ", depth: " << sol1.second << ". Solution is: " << sol1.first*sol1.second << std::endl;
	std::cout << "X: " << sol2.first << ", depth: " << sol2.second << ". Solution to part 2 is: " << sol2.first*sol2.second << std::endl;
	return 0;
}
