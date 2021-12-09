#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

void print_grid(std::vector<std::vector<int>>& grid){
	for(const auto row: grid) {
		for(const auto digit: row)
			std::cout << digit;
		std::cout << std::endl;
	}
}


std::vector<std::vector<int>> parse_input(std::string input_file){
	std::vector<std::vector<int>> grid;
	std::vector<int> row;
	std::ifstream input(input_file);
	std::string line;

	while(std::getline(input, line)){
		for(const auto& c: line)
			row.push_back(c - '0');

		grid.push_back(row);
		row.clear();
	}

	return grid;
}

bool lower_than_bowdary(std::vector<std::vector<int>>& table, int& x, int& y){
	bool low = true;

	if (x == 0) {
		if (y == 0) {
			low = table[x][y+1] > table[x][y] && table[x+1][y] > table[x][y];
		} else if (y == table[0].size()-1) {
			low = table[x][y-1] > table[x][y] && table[x+1][y] > table[x][y];
		} else {
			low = table[x][y-1] > table[x][y] && table[x+1][y] > table[x][y] && table[x][y+1] > table[x][y];
		}
	} else if (x == table.size()-1) {
		if (y == 0) {
			low = table[x-1][y] > table[x][y] && table[x][y+1] > table[x][y];
		} else if (y == table[0].size()-1) {
			low = table[x-1][y] > table[x][y] && table[x][y-1] > table[x][y];
		} else {
			low = table[x][y-1] > table[x][y] && table[x-1][y] > table[x][y] && table[x][y+1] > table[x][y];
		}
	} else {
		if (y == 0) {
			low = table[x-1][y] > table[x][y] && table[x+1][y] > table[x][y] && table[x][y+1] > table[x][y];
		} else if (y == table[0].size()-1) {
			low = table[x-1][y] > table[x][y] && table[x][y-1] > table[x][y] && table[x+1][y] > table[x][y];
		} else {
			low = table[x][y-1] > table[x][y]
				&& table[x-1][y] > table[x][y]
				&& table[x][y+1] > table[x][y]
				&& table[x+1][y] > table[x][y];
		}
	}

	return low;
}

int part_one(std::vector<std::vector<int>>& table){
	int value = 0;
	for (int x=0; x<table.size(); ++x) {
		for (int y=0; y<table[0].size(); ++y) {
			if (lower_than_bowdary(table, x, y))
				value += table[x][y] + 1;
		}
	}

	return value;
}


int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}
	
	std::string input_file = argv[1];
	std::vector<std::vector<int>> input = parse_input(input_file);
	int sol1 = part_one(input);
	std::cout << "Sol to part 1 is: " << sol1 << std::endl;
	return 0;
}
