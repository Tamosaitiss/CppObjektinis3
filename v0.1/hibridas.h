#ifndef HIBRIDAS_H
#define HIBRIDAS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <random>
#include <ctime>

using namespace std;

struct Student {
    string vardas;
    string pavarde;
    int* namu_darbai;
    int nd_kiekis;
    int egzaminas;
};

void ivestiStudenta(vector<Student>& studentai, int pasirinkimas);
void spausdintiStudentus(const vector<Student>& studentai, bool naudotiMediana);
double skaiciuotiMediana(int* pazymiai, int nd_kiekis);
bool tikrintiTeksta(const string& tekstas);
bool tikrintiSkaiciu(const string& input);
int* generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();
string generuotiVarda();
string generuotiPavarde();

#endif
