#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

std::vector<int> parse_input_file() {
	int distance;
	std::vector<int> distances = std::vector<int>();
	std::ifstream input_file("./input/input.txt");

	while (input_file >> distance) {
		distances.push_back(distance);
	}

	return distances;
}


int main() {
	int previous_distance = INFINITY;
	int increments = 0;
	std::vector<int> distances = parse_input_file();

	previous_distance = *distances.begin();
	
	for (std::vector<int>::iterator it = distances.begin();  it != distances.end(); ++it) {

		if (*it > previous_distance) {
			increments++;
		}
		previous_distance = *it;
	}

	std::cout << increments << std::endl;
	return 0;
}
