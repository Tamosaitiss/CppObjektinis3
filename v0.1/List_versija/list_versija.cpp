#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <chrono>
#include <string>
#include "studentas.h"

using namespace std;

template <typename Container>
void strategija1(Container& studentai, Container& vargsiukai, Container& kietiakiai) {
    for (auto& s : studentai) {
        if (s.galutinis() < 5.0) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }
}

template <typename Container>
void strategija2(Container& studentai, Container& vargsiukai, Container& kietiakiai) {
    auto it = remove_if(studentai.begin(), studentai.end(), [&](const auto& s) {
        if (s.galutinis() < 5.0) {
            vargsiukai.push_back(move(s));
            return true;
        }
        return false;
    });
    studentai.erase(it, studentai.end());
    kietiakiai = studentai;
}

template <typename Container>
void strategija3(Container& studentai, Container& vargsiukai, Container& kietiakiai) {
    auto it = partition(studentai.begin(), studentai.end(), [](const auto& s) {
        return s.galutinis() < 5.0;
    });
    vargsiukai.assign(make_move_iterator(studentai.begin()), make_move_iterator(it));
    kietiakiai.assign(make_move_iterator(it), make_move_iterator(studentai.end()));
}

template <typename Container>
void testuotiStrategijas(const string& failo_pavadinimas) {
    vector<Studentas> visi_studentai;
    ifstream in(failo_pavadinimas);
    string vardas, pavarde;
    int nd;
    int egz;
    string temp;
    getline(in, temp); // skip header

    while (in >> vardas >> pavarde) {
        vector<int> nd_;
        for (int i = 0; i < 5; ++i) {
            in >> nd;
            nd_.push_back(nd);
        }
        in >> egz;
        visi_studentai.emplace_back(vardas, pavarde, nd_, egz);
    }

    cout << "Failas: " << failo_pavadinimas << fixed << setprecision(6) << endl;

    for (int s = 1; s <= 3; ++s) {
        Container studentai(visi_studentai.begin(), visi_studentai.end());
        Container vargsiukai, kietiakiai;

        auto start = chrono::high_resolution_clock::now();

        if (s == 1) strategija1(studentai, vargsiukai, kietiakiai);
        else if (s == 2) strategija2(studentai, vargsiukai, kietiakiai);
        else strategija3(studentai, vargsiukai, kietiakiai);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> trukme = end - start;

        cout << "Strategija " << s << ": " << trukme.count() << " s (vargsiukai: "
             << vargsiukai.size() << ", kietiakiai: " << kietiakiai.size() << ")" << endl;
    }

    cout << "---------------------------------------------" << endl;
}

int main() {
    vector<string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt"
    };

    for (const auto& failas : failai) {
        testuotiStrategijas<list<Studentas>>(failas);
    }

    return 0;
}