#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::setw;
using std::setprecision;
using std::left;
using std::right;
using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::cerr;

class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<int> nd_;
    int egzaminas_;

public:
    Studentas();
    Studentas(string vardas, string pavarde, vector<int> nd, int egzaminas);
    Studentas(std::istream& is);
    ~Studentas();

    string vardas() const;
    string pavarde() const;
    vector<int> nd() const;
    int egzaminas() const;

    double galutinisVidurkis() const;
    double galutinisMediana() const;

    // Papildomas metodas strategijoms
    double galutinis() const { return galutinisVidurkis(); }

    std::istream& read(std::istream& is);

    friend bool compare(const Studentas& a, const Studentas& b);
    friend bool comparePagalPavarde(const Studentas& a, const Studentas& b);
    friend bool comparePagalEgza(const Studentas& a, const Studentas& b);
};

// Šabloninės funkcijos darbui su bet kokiu konteineriu
template <typename Container>
void nuskaitytiIsFailo(Container& studentai, const string& failoPavadinimas) {
    ifstream in(failoPavadinimas);
    if (!in) {
        cerr << "Klaida: Nepavyko atidaryti failo '" << failoPavadinimas << "'!\n";
        return;
    }

    studentai.clear();
    string line;
    getline(in, line); // Skip header

    while (getline(in, line)) {
        std::istringstream iss(line);
        string vardas, pavarde;
        vector<int> nd(5);
        int egzaminas;

        iss >> vardas >> pavarde;
        for (int& pazymys : nd) iss >> pazymys;
        iss >> egzaminas;

        studentai.emplace_back(vardas, pavarde, nd, egzaminas);
    }
}

template <typename Container>
void skirstymas_1(const Container& visi, Container& vargsiukai, Container& kietiakiai) {
    for (const auto& s : visi) {
        if (s.galutinis() < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }
}

template <typename Container>
void skirstymas_2(Container& studentai, Container& vargsiukai) {
    auto it = std::remove_if(studentai.begin(), studentai.end(), [&](const Studentas& s) {
        if (s.galutinis() < 5.0) {
            vargsiukai.push_back(s);
            return true;
        }
        return false;
    });
    studentai.erase(it, studentai.end()); // lieka tik kietiakiai
}

template <typename Container>
void skirstymas_3(Container& studentai, Container& vargsiukai) {
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) {
        return s.galutinis() >= 5.0;
    });
    vargsiukai.insert(vargsiukai.end(), it, studentai.end());
    studentai.erase(it, studentai.end());
}

template <typename Container>
void issaugotiStudentusIFaila(const Container& studentai, const string& failoPavadinimas) {
    ofstream out(failoPavadinimas);
    if (!out) {
        cerr << "Klaida: Nepavyko sukurti failo '" << failoPavadinimas << "'!" << endl;
        return;
    }

    out << left << setw(20) << "Vardas"
        << setw(25) << "Pavarde"
        << setw(10) << "Galutinis" << endl;

    for (const auto& s : studentai) {
        out << left << setw(20) << s.vardas()
            << setw(25) << s.pavarde()
            << std::fixed << setprecision(2) << setw(10) << s.galutinis() << endl;
    }
}

#endif