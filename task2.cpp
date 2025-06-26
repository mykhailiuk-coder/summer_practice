#include <iostream>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    deque<int> D = { 6, -2, -7, 5, -3, 9 };
    size_t half = D.size() / 2;

    deque<int> D0;
    auto it = D.begin();
    advance(it, half);
    D0.insert(D0.begin(), D.begin(), it);

    deque<int>::reverse_iterator rbegin = D0.rbegin();
    deque<int>::reverse_iterator rend = D0.rend();

    replace_copy_if(rbegin, rend, back_inserter(D), [](int x) { return x < 0; }, 0);

    for (int val : D) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}