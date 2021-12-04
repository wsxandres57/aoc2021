#include <fstream>
#include <iostream>
#include <string>
#include <vector>


struct Number {
	int value;
	bool marked;
};

class BingoTable {
	private:
		int table_size = 5;

		bool completed_row(){
			bool completed = false;
			for (int i=0; i < this->numbers.size() && !completed; i += this->table_size) {
				if (this->numbers[i].marked 
						&& this->numbers[i+1].marked 
						&& this->numbers[i+2].marked
						&& this->numbers[i+3].marked 
						&& this->numbers[i+4].marked) {
					completed = true;
				}
			}
			return completed;
		};
		bool completed_column(){
			bool completed = false;
			for (int i=0; i < this->table_size && !completed; ++i) {
				if (this->numbers[i].marked 
						&& this->numbers[i+this->table_size].marked 
						&& this->numbers[i+(2*this->table_size)].marked 
						&& this->numbers[i+(3*this->table_size)].marked 
						&& this->numbers[i+(4*this->table_size)].marked) {
					completed = true;
				}
			}

			return completed;
		};

	public:
		bool done;
		std::vector<Number> numbers;
		BingoTable() {};
		BingoTable& operator=(const BingoTable& other) {
			this->numbers = other.numbers;
			return *this;
		};
		BingoTable(std::vector<std::string> lines) {
			Number n;
			for (std::string line: lines) {
				std::string parsed;
				for (char s: line) {
					if ((s == ' ' || s == '\0') && parsed.size() > 0) {
						n.value = std::stoi(parsed);
						n.marked = false;
						this->numbers.push_back(n);
						parsed.clear();
					} else {
						parsed.push_back(s);
					}
				}
				n.value = std::stoi(parsed);
				n.marked = false;
				this->numbers.push_back(n);
				parsed.clear();
			}
		};

		bool completed(){
			return this->completed_row() || this->completed_column();
		};

		void mark_value(int value) {
			for(Number& n: this->numbers)
				if (n.value == value) {
					n.marked = true;
				}
		}

		int get_unmarked_sum() {
			int sum = 0;
			for(Number n: this->numbers)
				if (!n.marked)
					sum += n.value;

			return sum;
		};

		void print_bingo() {
			int i;
			for (i = 0; i < this->numbers.size(); ++i) {
				if (i % this->table_size == 0) 
					std::cout << std::endl;
				std::cout << this->numbers[i].value;
				if (this->numbers[i].marked)
					std::cout << "*";

				std::cout << " ";
			}
			std::cout << std::endl;
		};
};

void read_input(std::string input_file, std::vector<BingoTable>& tables, std::vector<int>& bingo_values) {
	std::string line;
	std::string discard_line;
	std::string values;
	std::vector<std::string> table_lines;
	std::ifstream input(input_file);

	std::getline(input, values);
	// TODO: ugly, probably there are better ways to skip the first blank line
	std::getline(input, discard_line);

	while(!input.eof()) {
		std::getline(input, line);
		if (line.length() == 0) {
			BingoTable table(table_lines);
			tables.push_back(table);
			table_lines.clear();
		} else {
			table_lines.push_back(line);
		}
	}

	// process the input values, converting they to int
	std::string parsed;
	for (char s: values) {
		if ((s == ',' || s == '\0') && parsed.size() > 0) {
			bingo_values.push_back(std::stoi(parsed));
			parsed.clear();
		} else {
			parsed.push_back(s);
		}
	}
}

int main(int argc, char* argv[]) {

	std::vector<int> values;
	std::vector<BingoTable> tables;

	if (argc != 2) {
			std::cerr << "No input file provided" << std::endl;
			exit(-1);
	}

	std::string input_file = argv[1];
	read_input(input_file, tables, values);
	
	for(int& i: values) {
		for(BingoTable& table: tables){
			if (!table.done) {
				table.mark_value(i);
				if (table.completed()) {
					table.done = true;
					std::cout << i << std::endl;
					std::cout << table.get_unmarked_sum() << std::endl;
					std::cout << i*table.get_unmarked_sum() << std::endl;
				}
			}
		}
	}
}
