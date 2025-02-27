#ifndef VEKTORIAI_H
#define VEKTORIAI_H

#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

struct Student {
    string vardas;
    string pavarde;
    vector<int> namu_darbai;
    int egzaminas;
};

void ivestiStudenta(vector<Student> &studentai);
void nuskaitytiIsFailo(vector<Student> &studentai, const string &failoPavadinimas);
void issaugotiIFaila(const vector<Student> &studentai, const string &failoPavadinimas, bool naudotiMediana);
void rikiuotiStudentus(vector<Student> &studentai, int pasirinkimas);
void spausdintiStudentus(const vector<Student> &studentai, bool naudotiMediana);
double skaiciuotiMediana(vector<int> pazymiai);
bool tikrintiTeksta(const string &tekstas);
bool tikrintiSkaiciu(const string &input);
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();
string generuotiVarda();
string generuotiPavarde();

#endif