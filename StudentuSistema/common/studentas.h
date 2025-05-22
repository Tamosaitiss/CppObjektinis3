#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Vector.h"
#include <string>
#include <algorithm>

using namespace std;

class Studentas : public Zmogus {
private:
    Vector<int> nd_;
    int egzaminas_;

public:
    Studentas();
    Studentas(string vardas, string pavarde, Vector<int> nd, int egzaminas);
    Studentas(istream& is);

    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(Studentas&& other) noexcept;

    ~Studentas();

    // paveldeti metodai vardas() ir pavarde() jau yra Zmogus klasėje
    Vector<int> nd() const;
    int egzaminas() const;

    double galutinisVidurkis() const;
    double galutinisMediana() const;
    double galutinis() const { return galutinisVidurkis(); }

    istream& read(istream& is);

    std::ostream& spausdinti(std::ostream& os) const override;

    friend ostream& operator<<(ostream& os, const Studentas& s);
    friend istream& operator>>(istream& is, Studentas& s);

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
        istringstream iss(line);
        string vardas, pavarde;
        Vector<int> nd(5);
        int egzaminas;

        iss >> vardas >> pavarde;
        for (int& pazymys : nd) iss >> pazymys;
        iss >> egzaminas;

        studentai.push_back(Studentas(vardas, pavarde, nd, egzaminas));
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
    studentai.erase(it, studentai.end());
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
void issaugotiStudentusIFaila(Container studentai, const string& failoPavadinimas) {
    ofstream out(failoPavadinimas);
    if (!out) {
        cerr << "Klaida: Nepavyko sukurti failo '" << failoPavadinimas << "'!" << endl;
        return;
    }

    // Rūšiuojame pagal galutinį vidurkį (mažėjimo tvarka)
    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.galutinis() < b.galutinis();
    });

    out << left << setw(20) << "Vardas"
        << setw(25) << "Pavarde"
        << setw(10) << "Galutinis" << endl;

    for (const auto& s : studentai) {
        out << left << setw(20) << s.vardas()
            << setw(25) << s.pavarde()
            << fixed << setprecision(2) << setw(10) << s.galutinis() << endl;
    }
}

#endif