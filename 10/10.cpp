#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <numeric>
#include <algorithm>

std::set<char> openings = {'(', '{', '<', '['};
std::set<char> closings = {')', '}', '>', ']'};
std::map<char, char> pairs = {{'(', ')'},{'{', '}'}, {'[', ']'}, {'<', '>'}};
std::map<char, int> points = {{')', 3},{'}', 1197}, {']', 57}, {'>', 25137}};


std::vector<std::string> parse_input(std::string input_file){
	std::string line;
	std::vector<std::string> parsed_input;
	std::ifstream input(input_file);

	while(std::getline(input, line)){
		parsed_input.push_back(line);
		line.clear();  // This may not be necessary
	}

	return parsed_input;
}

int get_line_punctuation(std::string line){
	
	bool corrupt = false;
	char corrupting_char;
	int line_punctuation = 0;
	std::stack<char> stack;

	for(const char& c: line){
		// check if the character is a opening one
		bool opens = openings.find(c) != openings.end();
		if (opens)
			stack.emplace(c);
		else {
			char matching = stack.top();
			stack.pop();

			if (pairs[matching] != c){
				corrupt = true;
				corrupting_char = c;
				break;
			}
		}
	}

	if (corrupt)
		line_punctuation = points[corrupting_char];

	return line_punctuation;
}

bool line_is_corrupt(std::string line){
	
	bool corrupt = false;
	std::stack<char> stack;

	for(const char& c: line){
		// check if the character is a opening one
		bool opens = openings.find(c) != openings.end();
		if (opens)
			stack.emplace(c);
		else {
			char matching = stack.top();
			stack.pop();

			if (pairs[matching] != c){
				corrupt = true;
				break;
			}
		}
	}

	return corrupt;
}

int part_one(std::vector<std::string>& input){
	std::vector<int> puntuaciones;
	for(const auto line: input){
		puntuaciones.push_back(get_line_punctuation(line));
	}

	int total_points = std::accumulate(puntuaciones.begin(), puntuaciones.end(), 0);

	return total_points;

}

int main(int argc, char* argv[]) {
	
	if (argc != 2) {
		std::cerr << "No input file provided" << std::endl;
		exit(-1);
	}
	
	std::string input_file = argv[1];
	std::vector<std::string> input = parse_input(input_file);
	int pt1 = part_one(input);
	std::cout << pt1 << std::endl;
	
	return 0;
}
