#include "vektoriai.h"
#include <deque>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    deque<Student> studentai;
    deque<Student> vargsiukai, kietiakiai;
    string failoPavadinimas = "studentai1000000.txt"; // Keisk pagal testavimą

    // 1. Duomenų nuskaitymo laikas
    auto start = high_resolution_clock::now();
    nuskaitytiIsFailo(studentai, failoPavadinimas);
    auto end = high_resolution_clock::now();
    duration<double> nuskaitymoLaikas = end - start;
    cout << "Duomenu nuskaitymo laikas: " << nuskaitymoLaikas.count() << " s" << endl;

    // 2. Rūšiavimo laikas
    start = high_resolution_clock::now();
    sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
        return a.vardas < b.vardas;
    });
    end = high_resolution_clock::now();
    duration<double> rusiuLaikas = end - start;
    cout << "Rusiavimo laikas: " << rusiuLaikas.count() << " s" << endl;

    // 3. Skirstymo laikas
    start = high_resolution_clock::now();
    suskirstytiStudentus(studentai, vargsiukai, kietiakiai);
    end = high_resolution_clock::now();
    duration<double> skirstymoLaikas = end - start;
    cout << "Studentu skirstymo laikas: " << skirstymoLaikas.count() << " s" << endl;

    // Išsaugome rezultatus į failus
    issaugotiStudentusIFaila(vargsiukai, "vargsiukai_deque.txt");
    issaugotiStudentusIFaila(kietiakiai, "kietiakiai_deque.txt");

    return 0;
}