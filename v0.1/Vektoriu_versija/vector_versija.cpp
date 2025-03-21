#include "vektoriai.h"
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

void testuotiFaila(const string& failoPavadinimas) {
    vector<Student> visi, vargsiukai, kietiakiai;

    //Duomenų nuskaitymas
    auto start = high_resolution_clock::now();
    nuskaitytiIsFailo(visi, failoPavadinimas);
    auto end = high_resolution_clock::now();
    double nuskaitymoLaikas = duration<double>(end - start).count();

    //Rūšiavimas
    start = high_resolution_clock::now();
    sort(visi.begin(), visi.end(), [](const Student& a, const Student& b) {
        return a.vardas < b.vardas;
    });
    end = high_resolution_clock::now();
    double rusiavimoLaikas = duration<double>(end - start).count();

    //Skirstymas
    start = high_resolution_clock::now();
    suskirstytiStudentus(visi, vargsiukai, kietiakiai);
    end = high_resolution_clock::now();
    double skirstymoLaikas = duration<double>(end - start).count();

    //Failo dydžio ištraukimas
    string dydis = failoPavadinimas.substr(9, failoPavadinimas.find(".") - 9);

    //Išsaugojimas
    issaugotiStudentusIFaila(vargsiukai, "vargsiukai_" + dydis + "_vector.txt");
    issaugotiStudentusIFaila(kietiakiai, "kietiakiai_" + dydis + "_vector.txt");

    //Patikra (pasirinktinai)
    for (const auto& s : vargsiukai) {
        double galutinis = skaiciuotiVidurki(s.namu_darbai, s.egzaminas);
        if (galutinis >= 5.0) {
            cerr << "Klaida: vargsiukuose yra studentas su galutiniu >= 5.0: " << galutinis << endl;
        }
    }

    for (const auto& s : kietiakiai) {
        double galutinis = skaiciuotiVidurki(s.namu_darbai, s.egzaminas);
        if (galutinis < 5.0) {
            cerr << "Klaida: kietiakuosee yra studentas su galutiniu < 5.0: " << galutinis << endl;
        }
    }

    // 📊 Išvedimas
    cout << "Failas: " << failoPavadinimas << endl;
    cout << "   Nuskaitymo laikas: " << nuskaitymoLaikas << " s" << endl;
    cout << "   Rusiavimo laikas: " << rusiavimoLaikas << " s" << endl;
    cout << "   Skirstymo laikas: " << skirstymoLaikas << " s" << endl;
    cout << "   Kietiakiai: " << kietiakiai.size() << ", Vargsiukai: " << vargsiukai.size() << "\n" << endl;
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

