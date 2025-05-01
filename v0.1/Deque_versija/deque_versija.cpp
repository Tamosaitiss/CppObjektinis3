#include "studentas.h"
#include <deque>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void paleistiStrategija1(const string& failas) {
    deque<Studentas> studentai, vargsiukai, kietiakiai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_1(studentai, vargsiukai, kietiakiai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 1: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakiai: " << kietiakiai.size() << ")" << endl;

    issaugotiStudentusIFaila(vargsiukai, "deque_vargsiukai1.txt");
    issaugotiStudentusIFaila(kietiakiai, "deque_kietiakiai1.txt");
}

void paleistiStrategija2(const string& failas) {
    deque<Studentas> studentai, vargsiukai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_2(studentai, vargsiukai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 2: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakiai: " << studentai.size() << ")" << endl;

    issaugotiStudentusIFaila(vargsiukai, "deque_vargsiukai2.txt");
    issaugotiStudentusIFaila(studentai, "deque_kietiakiai2.txt");
}

void paleistiStrategija3(const string& failas) {
    deque<Studentas> studentai, vargsiukai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_3(studentai, vargsiukai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 3: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakiai: " << studentai.size() << ")" << endl;

    issaugotiStudentusIFaila(vargsiukai, "deque_vargsiukai3.txt");
    issaugotiStudentusIFaila(studentai, "deque_kietiakiai3.txt");
}

void testuokStudentas() {
    std::cout << "TESTAVIMAS PRASIDEDA..." << std::endl;

    // Sukuriamas studentas naudojant parametrizuotą konstruktorių
    vector<int> nd = {10, 9, 8};
    Studentas s1("Jonas", "Jonaitis", nd, 10);

    // Testuojamas kopijavimo konstruktorius
    Studentas s2 = s1;
    std::cout << "Kopijavimo konstruktorius: " << s2 << std::endl;

    // Testuojamas kopijavimo priskyrimo operatorius
    Studentas s3;
    s3 = s1;
    std::cout << "Kopijavimo priskyrimo operatorius: " << s3 << std::endl;

    // Testuojamas perkėlimo konstruktorius
    Studentas s4 = std::move(s1);
    std::cout << "Perkėlimo konstruktorius: " << s4 << std::endl;

    // Testuojamas perkėlimo priskyrimo operatorius
    Studentas s5;
    s5 = std::move(s2);
    std::cout << "Perkėlimo priskyrimo operatorius: " << s5 << std::endl;

    // Testuojamas operatorius >>
    std::stringstream input("Tomas Tomaitis 7 8 9 10 6");
    Studentas s6;
    input >> s6;
    std::cout << "Nuskaitytas studentas (>>): " << s6 << std::endl;

    std::cout << "TESTAVIMAS BAIGTAS" << std::endl;
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
        paleistiStrategija1(failas);
        paleistiStrategija2(failas);
        paleistiStrategija3(failas);
        cout << "---------------------------------------------" << endl;
    }

    testuokStudentas();

    return 0;
}