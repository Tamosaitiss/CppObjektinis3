#ifndef STUDENTAI_H
#define STUDENTAI_H

#include "student.h"
#include <vector>
#include <string>

using namespace std;

void ivestiStudenta(vector<Student>& studentai, int pasirinkimas);
void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas);
void issaugotiIFaila(const vector<Student>& studentai, const string& failoPavadinimas, bool naudotiMediana);
void rikiuotiStudentus(vector<Student>& studentai, int pasirinkimas);
void spausdintiStudentus(const vector<Student>& studentai, bool naudotiMediana);
double skaiciuotiMediana(vector<int> pazymiai);
bool tikrintiTeksta(const string& tekstas);
bool tikrintiSkaiciu(const string& input);
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();
string generuotiVarda();
string generuotiPavarde();

#endif
