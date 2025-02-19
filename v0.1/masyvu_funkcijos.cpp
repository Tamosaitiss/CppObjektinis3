/*#include "studentai_masyvas.h"
#include <iomanip>

// Input funkcija
void ivestiStudenta(Student studentai[], int &studentu_kiekis) {
    Student s;
    cout << "Vardas: ";
    cin >> s.vardas;
    if (s.vardas == "-1") return; // Jei ivedamas '-1' - break;
    cout << "Pavarde: ";
    cin >> s.pavarde;

    cout << "Iveskite namu darbu rezultatus (-1 jei baigta):\n";
    s.nd_kiekis = 0;
    while (true) {
        int pazymys;
        cin >> pazymys;
        if (pazymys == -1) break;
        s.namu_darbai[s.nd_kiekis++] = pazymys;
    }

    cout << "Egzamino rezultatas: ";
    cin >> s.egzaminas;

    studentai[studentu_kiekis++] = s;
}

// Vidurkio funkcija
double skaiciuotiVidurki(const Student &studentas) {
    int suma = 0;
    for (int i = 0; i < studentas.nd_kiekis; i++) {
        suma += studentas.namu_darbai[i];
    }
    return (studentas.nd_kiekis > 0) ? (double)suma / studentas.nd_kiekis : 0;
}

// Medianos funkcija
double skaiciuotiMediana(const Student &studentas) {
    int temp[MAX_ND];
    for (int i = 0; i < studentas.nd_kiekis; i++) {
        temp[i] = studentas.namu_darbai[i];
    }
    sort(temp, temp + studentas.nd_kiekis);
    int mid = studentas.nd_kiekis / 2;
    return (studentas.nd_kiekis % 2 == 0) ?
           (temp[mid - 1] + temp[mid]) / 2.0 : temp[mid];
}

// Output funkcija
void spausdintiStudentus(const Student studentai[], int studentu_kiekis) {
    cout << "Pavarde    Vardas    Galutinis (Vid.)\n";
    cout << "--------------------------------------\n";
    for (int i = 0; i < studentu_kiekis; i++) {
        double galutinis = 0.4 * skaiciuotiVidurki(studentai[i]) +
                           0.6 * studentai[i].egzaminas;
        cout << setw(10) << studentai[i].pavarde << " "
                  << setw(10) << studentai[i].vardas << " "
                  << fixed << setprecision(2) << galutinis << "\n";
    }
}