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

int get_distance_increments(std::vector<int> distances) {
	int previous_distance = INFINITY;
	int increments = 0;
	previous_distance = *distances.begin();

	for (int i: distances) {

		if (i > previous_distance) {
			increments++;
		}
		previous_distance = i;
	}

	return increments;
}

std::vector<int> group_distances(std::vector<int> distances) {
	int grouped_distance;
	std::vector<int> grouped_distances;

	for (int i=0; i < distances.size()-2; i++) {
		grouped_distance = distances[i] + distances[i+1] + distances[i+2];
		grouped_distances.push_back(grouped_distance);
	}

	return grouped_distances;
}


int main() {
	std::vector<int> distances = parse_input_file();
	int increments = get_distance_increments(distances);

	std::vector<int> grouped_distances = group_distances(distances);
	int increments2 = get_distance_increments(grouped_distances);

	std::cout << increments << std::endl;
	std::cout << increments2 << std::endl;
	return 0;
}
