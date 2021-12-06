#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Vent {
    std::pair<int, int> start;
    std::pair<int, int> end;
};

std::vector<Vent> parse_input(std::string input_file) {
    std::vector<Vent> vents;
    std::ifstream input(input_file);
    std::string line;
    int separator_position;

    int x, y, x1, y1;
    while (std::getline(input, line)) {
        separator_position = line.find("->");

        std::string number;
        for (int i=0; i < separator_position; ++i) {
            if (line[i] != ',') {
                number.push_back(line[i]);
            } else {
                x = std::stoi(number);
                number.clear();
            }
        }

        y = std::stoi(number);
        number.clear();

        for (int i=separator_position+2; i < line.size(); ++i) {
            if (line[i] != ',') {
                number.push_back(line[i]);
            } else {
                x1 = std::stoi(number);
                number.clear();
            }
        }

        y1 = std::stoi(number);
        number.clear();

        Vent v;
        v.start.first = x;
        v.start.second = y;
        v.end.first = x1;
        v.end.second = y1;

        vents.push_back(v);

    }

    return vents;

}

std::pair<int, int> get_table_size(std::vector<Vent> input_vents) {
    int x=0, y=0;
    std::pair<int, int> dimensions;

    for(Vent v: input_vents) {
        if (v.start.first > x) {
            x =v.start.first;
        } 

        if (v.end.first > x) {
            x =v.end.first;
        }

        if (v.start.second > y) {
            y =v.start.second;
        }

        if (v.end.second > y) {
            y =v.end.second;
        }

    }

    dimensions.first = x;
    dimensions.second = y;

    return dimensions;
}


std::vector<std::vector<int>> create_table(int x, int y) {
    std::vector<std::vector<int>> table;
    // TODO: with the real input I am geting a core dumped error without the +1
    for (int i=0; i <= x+1; ++i) {
        std::vector<int> row;
        for (int j = 0; j <= y; j++) {
            row.push_back(0);
        }
        table.push_back(row);
    }

    return table;
}

void print_table(std::vector<std::vector<int>>& table) {
    for(std::vector<int>& v: table) {
        for(int x: v) {
            if (x != 0)
                std::cout << x << " ";
            else
                std::cout << '.' << " ";

        }
        std::cout << std::endl;
    }
}

void mark_horizontal_points(Vent& v, std::vector<std::vector<int>>& table) {
    int i;
    int start = (v.start.first < v.end.first) ? v.start.first:v.end.first;
    int end = (v.start.first > v.end.first) ? v.start.first:v.end.first;
    for (i = start; i <= end; ++i) {
        table[v.start.second][i] += 1;
    }
}

void mark_vertical_points(Vent& v, std::vector<std::vector<int>>& table) {
    int i;
    int start = (v.start.second < v.end.second) ? v.start.second:v.end.second;
    int end = (v.start.second > v.end.second) ? v.start.second:v.end.second;
    for (i = start; i <= end; ++i) {
        table[i][v.start.first] += 1;
    }
}

void mark_diagonal_points_south_east(Vent& v, std::vector<std::vector<int>>& table) {
    int i, j;
    int startx = (v.start.first < v.end.first) ? v.start.first:v.end.first;
    int endx = (v.start.first > v.end.first) ? v.start.first:v.end.first;
    int starty = (v.start.second < v.end.second) ? v.start.second:v.end.second;


    int y=starty;
    for (i = startx; i <= endx; ++i) {
            table[i][y] += 1;
            y++;
    }
}

void mark_diagonal_points_north(Vent& v, std::vector<std::vector<int>>& table) {
    int i, j;
    int startx = (v.start.first < v.end.first) ? v.start.first:v.end.first;
    int endx = (v.start.first > v.end.first) ? v.start.first:v.end.first;
    int starty = (v.start.second > v.end.second) ? v.start.second:v.end.second;
    int y= starty;

    for(int i=startx; i < endx; ++i) {
        table[i][y] += 1;
        y--;
    }


}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "No input file provided" << std::endl;
        exit(-1);
    }

    std::string input_file = argv[1];
    std::vector<Vent> vents = parse_input(input_file);
    std::pair<int, int> dim = get_table_size(vents);
    std::vector<std::vector<int>> table = create_table(dim.first, dim.second);
    //std::vector<std::vector<int>> table = create_table(10,10);

    //part 1
    for(Vent& v: vents) {
        if (v.start.second == v.end.second) {
            mark_horizontal_points(v, table);
        } else if (v.start.first == v.end.first) {
            mark_vertical_points(v, table);
        } else if(abs(v.start.first - v.end.first) == abs(v.start.second - v.end.second)) {
            if (v.start.first < v.end.first) {
                if (v.start.second < v.end.second) {
                    mark_diagonal_points_south_east(v, table);
                } else {
                    mark_diagonal_points_north(v, table);
                }
            } else {
                if (v.start.second > v.end.second) {
                    mark_diagonal_points_south_east(v, table);
                } else {
                    mark_diagonal_points_north(v, table);
                }
            }
        }
    }

    int count = 0;
    for(int i= 0; i < table.size(); ++i) {
        for(int j=0; j < table[0].size(); ++j) {
            if (table[i][j] > 1)
                count++;
        }
    }

    std::cout << "**********" << std::endl;
    std::cout << count << std::endl;
    //print_table(table);

    return 0;
}
