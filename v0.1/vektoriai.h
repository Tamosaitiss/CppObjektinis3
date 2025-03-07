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

// Function to generate a student's name
string gautiVarda(int indeksas);

// Function to generate a student's surname
string gautiPavarde(int indeksas);

// Function to generate random homework grades
vector<int> generuotiAtsitiktiniusPazymius(int kiekis);

// Function to generate a random exam grade
int generuotiAtsitiktiniEgzaminoBala();

// Function to manually input a student
void ivestiStudenta(vector<Student>& studentai, int pasirinkimas);

// Function to calculate the average grade
double skaiciuotiVidurki(const vector<int>& pazymiai, int egzaminas);

// Function to calculate the median grade
double skaiciuotiMediana(const vector<int>& pazymiai, int egzaminas);

// Function to read students from a file
void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas);

// Function to sort students based on criteria
void rikiuotiStudentus(vector<Student>& studentai, int pasirinkimas);

// Function to print students to the console or save to a file
void spausdintiStudentus(const vector<Student>& studentai, bool irasyti);

// Function to save students to a file
void issaugotiIFaila(const vector<Student>& studentai, const string& failoPavadinimas, bool naudotiMediana);

// Function to sort students into two categories and save to files
void suskirstytiStudentusIrIrasytiISFailus(const vector<Student>& studentai);

// Function to generate a single file with student data
void generuotiVienaFaila(int kiekis);

// Function to generate multiple files with student data
void generuotiFailus(int kiekis);

// Function to measure file generation time
void matuotiFailuGeneravimoLaika();

// Function to measure data processing time
void matuotiDuomenuApdorojimoLaika(const string& failoPavadinimas);

// Main program execution function
void vykdytiPrograma();

// Function to split students into two categories (vargsiukai and kietiakiai)
void suskirstytiStudentus(const vector<Student>& studentai, vector<Student>& vargsiukai, vector<Student>& kietiakiai);

// Function to save sorted students to files
void issaugotiStudentusIFaila(const vector<Student>& studentai, const string& failoPavadinimas);

// Function to measure file creation time
void matuotiFailuKurimoLaika();

#endif