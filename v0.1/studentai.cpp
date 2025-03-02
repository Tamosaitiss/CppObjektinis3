#include "studentai.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

string generuotiVarda() {
    vector<string> galimiVardai = {"Jonas", "Ignas", "Petras", "Justas", "Lukas", "Kristijonas", "Marius", "Matas"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, galimiVardai.size() - 1);
    return galimiVardai[dist(gen)];
}

string generuotiPavarde() {
    vector<string> galimosPavardes = {"Jonaitis", "Petraitis", "Kazlauskas", "Balciunas", "Jankauskas"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, galimosPavardes.size() - 1);
    return galimosPavardes[dist(gen)];
}

double skaiciuotiMediana(vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    sort(pazymiai.begin(), pazymiai.end());
    int dydis = pazymiai.size();
    return (dydis % 2 == 0) ? (pazymiai[dydis / 2 - 1] + pazymiai[dydis / 2]) / 2.0 : pazymiai[dydis / 2];
}

void nuskaitytiIsFailo(vector<Student> &studentai, const string &failoPavadinimas) {
    ifstream fin(failoPavadinimas);
    if (!fin) {
        cerr << "Klaida! Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return;
    }

    string eilute;
    getline(fin, eilute);

    while (!fin.eof()) {
        Student s;
        fin >> s.vardas >> s.pavarde;
        int pazymys;
        while (fin >> pazymys) {
            if (fin.peek() == '\n') {
                s.egzaminas = pazymys;
                break;
            }
            s.namu_darbai.push_back(pazymys);
        }
        studentai.push_back(s);
    }
    fin.close();
}

