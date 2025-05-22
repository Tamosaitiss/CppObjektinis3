#include "studentas.h"
#include <chrono>
#include <iomanip>
#include "../common/Vector.h"

using namespace std;
using namespace std::chrono;

void paleistiStrategija1(const string& failas) {
    Vector<Studentas> studentai, vargsiukai, kietiakiai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_1(studentai, vargsiukai, kietiakiai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 1: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakai: " << kietiakiai.size() << ")" << endl;


    issaugotiStudentusIFaila(vargsiukai, "vector_vargsiukai1.txt");
    issaugotiStudentusIFaila(kietiakiai, "vector_kietiakai1.txt");
}

void paleistiStrategija2(const string& failas) {
    Vector<Studentas> studentai, vargsiukai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_2(studentai, vargsiukai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 2: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakai: " << studentai.size() << ")" << endl;


    issaugotiStudentusIFaila(vargsiukai, "vector_vargsiukai2.txt");
    issaugotiStudentusIFaila(studentai, "vector_kietiakai2.txt");
}

void paleistiStrategija3(const string& failas) {
    Vector<Studentas> studentai, vargsiukai;
    nuskaitytiIsFailo(studentai, failas);

    auto start = high_resolution_clock::now();
    skirstymas_3(studentai, vargsiukai);
    auto end = high_resolution_clock::now();

    double trukme = duration<double>(end - start).count();
    cout << "Strategija 3: " << fixed << setprecision(6) << trukme << " s"
         << " (vargsiukai: " << vargsiukai.size()
         << ", kietiakai: " << studentai.size() << ")" << endl;


    issaugotiStudentusIFaila(vargsiukai, "vector_vargsiukai3.txt");
    issaugotiStudentusIFaila(studentai, "vector_kietiakai3.txt");
}

/*void testuokStudentas() {
    cout << "Rule of Five testas\n";

    Studentas s1("Testas", "Testavicius", {10, 9, 9}, 9.6);
    cout << left << setw(25) << "s1 sukurtas:" << s1 << endl;

    Studentas s2(s1); // kopijavimo konstruktorius
    cout << left << setw(25) << "s2 (kopija s1):" << s2 << endl;

    cout << left << setw(25) << "s1 po kopijavimo:" << s1 << endl;

    Studentas s3(std::move(s1)); // perkėlimo konstruktorius
    cout << left << setw(25) << "s3 (perkeltas s1):" << s3 << endl;
    cout << left << setw(25) << "s1 po perkelimo:" << s1 << endl;

    Studentas s4 = s2; // kopijavimo priskyrimo operatorius
    cout << left << setw(25) << "s4 (priskirtas s2):" << s4 << endl;
    cout << left << setw(25) << "s2 po priskyrimo:" << s2 << endl;

    Studentas s5 = std::move(s3); // perkėlimo priskyrimo operatorius
    cout << left << setw(25) << "s5 (perkeltas s3):" << s5 << endl;
    cout << left << setw(25) << "s3 po perkelimo:" << s3 << endl;

    cout << "\nGalutines objektu busenos:\n";
    cout << left << setw(25) << "s1:" << s1 << endl;
    cout << left << setw(25) << "s2:" << s2 << endl;
    cout << left << setw(25) << "s3:" << s3 << endl;
    cout << left << setw(25) << "s4:" << s4 << endl;
    cout << left << setw(25) << "s5:" << s5 << endl;

    cout << "Rule of Five testas\n";

    cout << "\nDestruktoriaus testas\n";
    {
        Studentas laikinas("Testas", "Testavicius", {7, 8, 9}, 7.2);
        cout << "Laikinas studentas sukurtas: " << laikinas << endl;
    }
    cout << "Isejome is bloko, destruktorius turejo buti iskvieciamas.\n";

    cout << "\nIvesties ir isvesties operatoriu testas\n";
    istringstream fakeInput("Testas Testavicius 10 8 7 9 8");
    Studentas ivestas;
    fakeInput >> ivestas;

    cout << "Nuskaitytas studentas:\n" << ivestas << endl;

    // Demonstracija: negalima kurti Zmogus objekto
    // Zmogus z; // <- Tai būtų kompiliavimo klaida, nes Zmogus yra abstrakti klasė
    // Zmogus z("Jonas", "Jonaitis");
}*/

int main() {
    Vector<string> failai = {
        "studentai10000.txt",
        "studentai100000.txt",
    };

    for (const auto& failas : failai) {
        cout << "Failas: " << failas << endl;
        paleistiStrategija1(failas);
        paleistiStrategija2(failas);
        paleistiStrategija3(failas);
        cout << "---------------------------------------------" << endl;
    }

    //testuokStudentas();

    string stop;
    cout << "Spausk ENTER, kad uzdaryti programa...";
    getline(cin, stop);

    return 0;
}