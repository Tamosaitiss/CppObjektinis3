#include <iostream>
#include <vector>
#include "../common/Vector.h"

using namespace std;

int main() {
    const size_t n = 100000000;

    // std::vector
    vector<int> v_std;
    size_t std_reallocs = 0;
    for (size_t i = 0; i < n; ++i) {
        if (v_std.size() == v_std.capacity())
            ++std_reallocs;
        v_std.push_back(i);
    }

    // Vector
    Vector<int>::resize_counter = 0;
    Vector<int> v_custom;
    for (size_t i = 0; i < n; ++i) {
        v_custom.push_back(i);
    }

    cout << "std::vector perskirstymai: " << std_reallocs << endl;
    cout << "Vector perskirstymai:      " << Vector<int>::resize_counter << endl;

    return 0;
}
