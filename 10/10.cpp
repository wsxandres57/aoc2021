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
	std::map<char, int> points = {{')', 3},{'}', 1197}, {']', 57}, {'>', 25137}};

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

unsigned long long int complete_line(const std::string& line){
	unsigned long long int punctuation = 0;
	std::string closing_chars;
	std::stack<char> stack;
	std::map<char, int> points = {{')', 1},{'}', 3}, {']', 2}, {'>', 4}};

	for(const char& c: line){
		// check if the character is a opening one
		bool opens = openings.find(c) != openings.end();
		if (opens)
			stack.emplace(c);
		else {
			char matching = stack.top();
			stack.pop();
		}
	}

	while (!stack.empty()) {
		char c = stack.top();
		stack.pop();
		closing_chars.push_back(pairs[c]);

		punctuation = punctuation*5 + points[pairs[c]];
	}

	return punctuation;
}

int part_two(std::vector<std::string>& input){
	std::vector<unsigned long long int> puntuaciones;
	for(const auto& line: input){
		if(!line_is_corrupt(line)){
			puntuaciones.push_back(complete_line(line));
		}
	}

	auto m = puntuaciones.begin() + puntuaciones.size()/2;
    std::nth_element(puntuaciones.begin(), m, puntuaciones.end());

	return puntuaciones[puntuaciones.size()/2];
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
	int pt2 = part_two(input);
	std::cout << pt2 << std::endl;
	
	return 0;
}
