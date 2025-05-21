#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "../common/Vector.h"

using namespace std;
using namespace std::chrono;

template <typename Container>
double benchmark_push_back(Container& v, unsigned int sz) {
    auto start = high_resolution_clock::now();
    for (unsigned int i = 0; i < sz; ++i)
        v.push_back(i);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

int main() {
    vector<unsigned int> sizes = {10000, 100000, 1000000, 10000000, 100000000};

    cout << left << setw(20) << "| Elementu skaicius"
         << setw(28) << "| std::vector laikas (s)"
         << setw(25) << "| Vector laikas (s)"
         << setw(25) << "| Vector perskirstymai |" << endl;

    cout << string(98, '-') << endl;

    for (auto sz : sizes) {
        // std::vector testas
        vector<int> v_std;
        double std_time = benchmark_push_back(v_std, sz);

        // Vector testas
        Vector<int>::resize_counter = 0;
        Vector<int> v_custom;
        double custom_time = benchmark_push_back(v_custom, sz);
        size_t reallocs = Vector<int>::resize_counter;

        cout << left << setw(20) << ("| " + to_string(sz))
             << setw(28) << ("| " + to_string(std_time))
             << setw(25) << ("| " + to_string(custom_time))
             << setw(25) << ("| " + to_string(reallocs)) << "|\n";
    }

    return 0;
}
