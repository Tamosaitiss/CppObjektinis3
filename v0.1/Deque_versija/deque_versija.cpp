#include "vektoriai.h"
#include <list>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

void testuotiFaila(const string& failoPavadinimas) {
    list<Student> visi, vargsiukai, kietiakiai;

    auto start = high_resolution_clock::now();
    nuskaitytiIsFailo(visi, failoPavadinimas);
    auto end = high_resolution_clock::now();
    double nuskaitymoLaikas = duration<double>(end - start).count();

    start = high_resolution_clock::now();
    visi.sort([](const Student& a, const Student& b) {
        return a.vardas < b.vardas;
    });
    end = high_resolution_clock::now();
    double rusiavimoLaikas = duration<double>(end - start).count();

    start = high_resolution_clock::now();
    suskirstytiStudentus(visi, vargsiukai, kietiakiai);
    end = high_resolution_clock::now();
    double skirstymoLaikas = duration<double>(end - start).count();

    string dydis = failoPavadinimas.substr(9, failoPavadinimas.find(".") - 9);

    issaugotiStudentusIFaila(vargsiukai, "vargsiukai_" + dydis + "_list.txt");
    issaugotiStudentusIFaila(kietiakiai, "kietiakiai_" + dydis + "_list.txt");

    for (const auto& s : vargsiukai) {
        double galutinis = skaiciuotiVidurki(s.namu_darbai, s.egzaminas);
        if (galutinis >= 5.0) {
            cerr << "Klaida: i vargsiukai patenka studentas su galutiniu >= 5.0: " << galutinis << endl;
        }
    }

    for (const auto& s : kietiakiai) {
        double galutinis = skaiciuotiVidurki(s.namu_darbai, s.egzaminas);
        if (galutinis < 5.0) {
            cerr << "Klaida: i kietiakiai patenka studentas su galutiniu < 5.0: " << galutinis << endl;
        }
    }

    cout << "Failas: " << failoPavadinimas << endl;
    cout << "  Nuskaitymo laikas: " << nuskaitymoLaikas << " s" << endl;
    cout << "  Rusiavimo laikas: " << rusiavimoLaikas << " s" << endl;
    cout << "  Skirstymo laikas: " << skirstymoLaikas << " s" << endl;
    cout << "  Kietiakiai: " << kietiakiai.size() << ", Vargsiukai: " << vargsiukai.size() << endl << endl;
}

int main() {
    vector<string> failai = {
        "studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt"
    };

    for (const auto& failas : failai) {
        testuotiFaila(failas);
    }

    return 0;
}