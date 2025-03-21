#include "vektoriai.h"
#include <list>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

void testuotiStrategijas(const string& failoPavadinimas) {
    list<Student> pradiniai;
    nuskaitytiIsFailo(pradiniai, failoPavadinimas);
    string dydis = failoPavadinimas.substr(9, failoPavadinimas.find(".") - 9);

    // Strategija 1
    {
        list<Student> vargsiukai, kietiakiai;
        auto start = high_resolution_clock::now();
        skirstymas_1(pradiniai, vargsiukai, kietiakiai);
        auto end = high_resolution_clock::now();
        double laikas = duration<double>(end - start).count();

        issaugotiStudentusIFaila(vargsiukai, "vargsiukai_" + dydis + "_strategija1_list.txt");
        issaugotiStudentusIFaila(kietiakiai, "kietiakiai_" + dydis + "_strategija1_list.txt");

        cout << "Strategija 1: " << laikas << " s (vargsiukai: " << vargsiukai.size() << ", kietiakiai: " << kietiakiai.size() << ")" << endl;
    }

    // Strategija 2
    {
        list<Student> studentai = pradiniai;
        list<Student> vargsiukai;
        auto start = high_resolution_clock::now();
        skirstymas_2(studentai, vargsiukai);
        auto end = high_resolution_clock::now();
        double laikas = duration<double>(end - start).count();

        issaugotiStudentusIFaila(vargsiukai, "vargsiukai_" + dydis + "_strategija2_list.txt");
        issaugotiStudentusIFaila(studentai, "kietiakiai_" + dydis + "_strategija2_list.txt");

        cout << "Strategija 2: " << laikas << " s (vargsiukai: " << vargsiukai.size() << ", kietiakiai: " << studentai.size() << ")" << endl;
    }

    // Strategija 3
    {
        list<Student> studentai = pradiniai;
        list<Student> vargsiukai;
        auto start = high_resolution_clock::now();
        skirstymas_3(studentai, vargsiukai);
        auto end = high_resolution_clock::now();
        double laikas = duration<double>(end - start).count();

        issaugotiStudentusIFaila(vargsiukai, "vargsiukai_" + dydis + "_strategija3_list.txt");
        issaugotiStudentusIFaila(studentai, "kietiakiai_" + dydis + "_strategija3_list.txt");

        cout << "Strategija 3: " << laikas << " s (vargsiukai: " << vargsiukai.size() << ", kietiakiai: " << studentai.size() << ")" << endl;
    }

    cout << "---------------------------------------------\n";
}

int main() {
    vector<string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt"
    };

    for (const auto& failas : failai) {
        cout << "Failas: " << failas << endl;
        testuotiStrategijas(failas);
    }

    return 0;
}
