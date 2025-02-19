#ifndef STUDENTAI_MASYVAS_H
#define STUDENTAI_MASYVAS_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_STUDENTU = 100;
const int MAX_ND = 100;

struct Student {
    string vardas, pavarde;
    int namu_darbai[MAX_ND];
    int nd_kiekis;
    int egzaminas;
};

void ivestiStudenta(Student studentai[], int &studentu_kiekis);
void spausdintiStudentus(const Student studentai[], int studentu_kiekis);
double skaiciuotiVidurki(const Student &studentas);
double skaiciuotiMediana(const Student &studentas);

#endif //STUDENTAI_MASYVAS_H