#ifndef STUDENTAI_H
#define STUDENTAI_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <numeric>
#include <limits>

using namespace std;

// Student structure
struct Student {
    string vardas;
    string pavarde;
    vector<int> namu_darbai;
    int egzaminas;
};

string gautiVarda(int indeksas);
string gautiPavarde(int indeksas);
bool tikrintiTeksta(const string &tekstas);
bool tikrintiSkaiciu(const string &input);
double skaiciuotiVidurki(const vector<int>& pazymiai, int egzaminas);
double skaiciuotiMediana(vector<int>& pazymiai, int egzaminas);
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();
void isvestiKlaida(const string &klausimas);
void ivestiStudenta(vector<Student>& studentai, int pasirinkimas);
void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas);
void rikiuotiStudentus(vector<Student>& studentai, int rikiavimoPasirinkimas);
void spausdintiStudentus(const vector<Student>& studentai, bool irasyti);
void issaugotiIFaila(const vector<Student>& studentai, const string& failoPavadinimas, bool naudotiMediana);
void generuotiFailus(int kiekis);
void vykdytiPrograma();

#endif // STUDENTAI_H