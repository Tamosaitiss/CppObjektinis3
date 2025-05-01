#include "studentas.h"
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void paleistiStrategija1(const string& failas) {
    vector<Studentas> studentai, vargsiukai, kietiakiai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_1(studentai, vargsiukai, kietiakiai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 1: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakiai: " << kietiakiai.size() << ")" << endl;

    issaugotiStudentusIFaila(vargsiukai, "vector_vargsiukai1.txt");
    issaugotiStudentusIFaila(kietiakiai, "vector_kietiakiai1.txt");
}

void paleistiStrategija2(const string& failas) {
    vector<Studentas> studentai, vargsiukai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_2(studentai, vargsiukai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 2: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakiai: " << studentai.size() << ")" << endl;

    issaugotiStudentusIFaila(vargsiukai, "vector_vargsiukai2.txt");
    issaugotiStudentusIFaila(studentai, "vector_kietiakiai2.txt");
}

void paleistiStrategija3(const string& failas) {
    vector<Studentas> studentai, vargsiukai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_3(studentai, vargsiukai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 3: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakiai: " << studentai.size() << ")" << endl;

    issaugotiStudentusIFaila(vargsiukai, "vector_vargsiukai3.txt");
    issaugotiStudentusIFaila(studentai, "vector_kietiakiai3.txt");
}

void testuokStudentas() {
    std::cout << "TESTAVIMAS PRASIDEDA..." << std::endl;

    vector<int> nd = {10, 9, 8, 7};
    Studentas s1("Jonas", "Jonaitis", nd, 6);
    Studentas s2 = s1;              // Copy constructor
    Studentas s3; s3 = s1;          // Copy assignment
    Studentas s4 = std::move(s1);   // Move constructor
    Studentas s5; s5 = std::move(s2); // Move assignment

    std::cout << std::left
              << std::setw(20) << "Vardas"
              << std::setw(25) << "Pavarde"
              << std::setw(10) << "Galutinis" << std::endl;

    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;
    std::cout << s5 << std::endl;

    std::stringstream input("Tomas Tomaitis 7 8 9 10 6");
    Studentas s6;
    input >> s6;

    std::cout << s6 << std::endl;

    std::cout << "TESTAVIMAS BAIGTAS" << std::endl;
}

int main() {
    vector<string> failai = {
        //"studentai1000.txt",
        "studentai10000.txt",
        "studentai100000.txt",
        "studentai1000000.txt"
    };

    for (const auto& failas : failai) {
        cout << "Failas: " << failas << endl;
        paleistiStrategija1(failas);
        paleistiStrategija2(failas);
        paleistiStrategija3(failas);
        cout << "---------------------------------------------" << endl;
    }

    testuokStudentas();

    return 0;
}