#ifndef VEKTORIAI_H
#define VEKTORIAI_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

// Student structure to hold student data
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
double skaiciuotiMediana(const vector<int>& pazymiai, int egzaminas);
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();
void ivestiStudenta(vector<Student>& studentai, int pasirinkimas, bool& buvoGeneruota);
void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas);
void rikiuotiStudentus(vector<Student>& studentai, int rikiavimoPasirinkimas);
void spausdintiStudentus(const vector<Student>& studentai, bool irasyti);
void generuotiFaila(int kiekis, const string& failoPavadinimas);
void generuotiFailus(const vector<int>& kiekiai);
void suskirstytiStudentus(const vector<Student>& studentai, vector<Student>& vargsiukai, vector<Student>& kietiakiai);
void issaugotiStudentusIFaila(const vector<Student>& studentai, const string& failoPavadinimas);
void matuotiFailuKurimoLaika();
void matuotiDuomenuApdorojimoLaika(const string& failoPavadinimas);
void vykdytiPrograma();

#endif