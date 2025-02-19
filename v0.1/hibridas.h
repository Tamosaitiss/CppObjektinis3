#ifndef HIBRIDAS_H
#define HIBRIDAS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string vardas;
    string pavarde;
    int* namu_darbai;
    int nd_kiekis;
    int egzaminas;
};

// input
void ivestiStudenta(Student*& studentai, int& studentu_kiekis);

// output
void spausdintiStudentus(const Student* studentai, int studentu_kiekis);

// atminties valymas
void atlaisvintiAtmintį(Student*& studentai, int studentu_kiekis);

#endif
