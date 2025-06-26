#include <iostream>
#include <vector>
#include <map>

int main() {
    std::vector<int> V = { 4, 2, 4, 3, 2, 2, 1, 4 };

    std::map<int, int> M;

    for (auto it = V.begin(); it != V.end(); ++it) {
        M[*it]++;
    }

    std::cout << "Elements and repetitions: \n";
    for (auto it = M.begin(); it != M.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    return 0;
}