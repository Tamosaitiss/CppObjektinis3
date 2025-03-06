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
#include <ctime>
#include <numeric>

using namespace std;

struct Student {
    string vardas;
    string pavarde;
    vector<int> namu_darbai;
    int egzaminas;
};

bool tikrintiTeksta(const string& tekstas);
bool tikrintiSkaiciu(const string& input);
double skaiciuotiMediana(vector<int> pazymiai);
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();
void isvestiKlaida(const string& klausimas);
void ivestiStudenta(vector<Student>& studentai, int pasirinkimas);
void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas);
void issaugotiIFaila(const vector<Student>& studentai, const string& failoPavadinimas, bool naudotiMediana);
void generuotiFailus(int kiekis);
void spausdintiStudentus(const vector<Student>& studentai, bool irasyti);
void rikiuotiStudentus(vector<Student>& studentai, int kriterijus);
string gautiVarda(int indeksas);
string gautiPavarde(int indeksas);
void vykdytiPrograma();

#endif // STUDENTAI_H
