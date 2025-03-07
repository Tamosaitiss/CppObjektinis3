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

// Funkcijos, susijusios su studentų generavimu ir įvedimu
string gautiVarda(int indeksas);
string gautiPavarde(int indeksas);
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);
int generuotiAtsitiktiniEgzaminoBala();
void ivestiStudenta(vector<Student>& studentai, int pasirinkimas);

// Duomenų apdorojimo funkcijos
double skaiciuotiVidurki(const vector<int>& pazymiai, int egzaminas);
double skaiciuotiMediana(const vector<int>& pazymiai, int egzaminas);
void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas);
void rikiuotiStudentus(vector<Student>& studentai, int pasirinkimas);
void spausdintiStudentus(const vector<Student>& studentai, bool irasyti);

// Failų apdorojimo funkcijos
void issaugotiIFaila(const vector<Student>& studentai, const string& failoPavadinimas, bool naudotiMediana);
void suskirstytiStudentusIrIrasytiISFailus(const vector<Student>& studentai);
void generuotiFailus(int kiekis);
void generuotiVienaFaila(int kiekis);

// Laiko matavimo funkcijos
void matuotiFailuGeneravimoLaika();
void matuotiDuomenuApdorojimoLaika(const string& failoPavadinimas);

// Pagrindinė programos vykdymo funkcija
void vykdytiPrograma();

#endif