#ifndef VEKTORIAI_H
#define VEKTORIAI_H

#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string vardas;
    string pavarde;
    vector<int> namu_darbai;
    int egzaminas;
};

void ivestiStudenta(vector<Student> &studentai);
void spausdintiStudentus(const vector<Student> &studentai);

#endif