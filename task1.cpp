#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

int main() {
    const char* path = "D:\\cpp_labs\\summer_practice\\cpp_tasks\\task1\\name.txt";
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << path << std::endl;
        return 1;
    }

    std::istream_iterator<double> begin(file);
    std::istream_iterator<double> end;

    int count = std::count_if(begin, end, [](double num) {
        return num > 0;
        });

    std::cout << "Number of positive integers: " << count << std::endl;

    return 0;
}