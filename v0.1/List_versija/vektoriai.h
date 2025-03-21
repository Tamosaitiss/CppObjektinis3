#ifndef VEKTORIAI_H
#define VEKTORIAI_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <random>
#include <numeric>
#include <filesystem>

using namespace std;

// Studentų struktūra
struct Student {
    string vardas;
    string pavarde;
    vector<int> namu_darbai;
    int egzaminas;
};

//funkcijos iš `v0.4`
string gautiVarda(int indeksas);
string gautiPavarde(int indeksas);
double skaiciuotiVidurki(const vector<int>& pazymiai, int egzaminas);
double skaiciuotiMediana(const vector<int>& pazymiai, int egzaminas);
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();

//Šabloninės funkcijos, veikiančios su visais konteineriais (vector, list, deque)
template <typename Container>
void nuskaitytiIsFailo(Container& studentai, const string& failoPavadinimas) {
    ifstream in(failoPavadinimas);
    if (!in) {
        cerr << "Klaida: Nepavyko atidaryti failo '" << failoPavadinimas << "'!\n";
        return;
    }

    studentai.clear();
    string line;
    getline(in, line); // Skip header row

    while (getline(in, line)) {
        istringstream iss(line);
        Student studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        for (int i = 0; i < 5; i++) {  // Read 5 ND scores
            int pazymys;
            iss >> pazymys;
            studentas.namu_darbai.push_back(pazymys);
        }

        // Read egzaminas
        if (!(iss >> studentas.egzaminas)) {
            cerr << "Klaida: Nepavyko nuskaityti egzamino studentui " << studentas.vardas << " " << studentas.pavarde << endl;
            studentas.egzaminas = -1; // Assign an invalid value to detect errors
        }

        studentai.push_back(studentas);
    }
}


template <typename Container>
void suskirstytiStudentus(const Container& visi, Container& vargsiukai, Container& kietiakiai) {
    for (const auto& s : visi) {
        if (skaiciuotiVidurki(s.namu_darbai, s.egzaminas) < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }
}

template <typename Container>
void issaugotiStudentusIFaila(const Container& studentai, const string& failoPavadinimas) {
    ofstream out(failoPavadinimas);

    if (!out) {
        cerr << "Klaida: Nepavyko sukurti failo '" << failoPavadinimas << "'!" << endl;
        return;
    }

    // Write only if there are students
    if (studentai.empty()) {
        cerr << "Ispejimas: failas '" << failoPavadinimas << "' yra tuscias, nes nera studentu." << endl;
        return;
    }

    out << left << setw(20) << "Vardas"
        << setw(25) << "Pavarde"
        << setw(10) << "Galutinis" << endl;

    for (const auto& studentas : studentai) {
        double galutinis = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);

        out << left << setw(20) << studentas.vardas
            << setw(25) << studentas.pavarde
            << fixed << setprecision(2) << setw(10) << galutinis << endl;
    }

    cout << "Failas '" << failoPavadinimas << "' sekmingai sukurtas su " << studentai.size() << " studentu(-ais)." << endl;
}


//papildomos funkcijos iš `v0.4`
void generuotiFailus(const vector<int>& kiekiai);
void rikiuotiStudentus(vector<Student>& studentai, int rikiavimoPasirinkimas);
void spausdintiStudentus(const vector<Student>& studentai, bool irasyti);
void vykdytiPrograma();

#endif