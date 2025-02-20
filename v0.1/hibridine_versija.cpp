#include "hibridas.h"

void ivestiStudenta(Student*& studentai, int& studentu_kiekis) {
    Student temp;

    cout << "Vardas: ";
    cin >> temp.vardas;
    if (temp.vardas == "-1") return; // jei -1 tai neprideta prie amsyvo ir grazina reiksme

    cout << "Pavarde: ";
    cin >> temp.pavarde;

    cout << "Iveskite namu darbu rezultatus (-1 jei baigta):\n";
    temp.nd_kiekis = 0;
    temp.namu_darbai = new int[100];

    while (true) {
        int pazymys;
        cin >> pazymys;
        if (pazymys == -1) break;
        temp.namu_darbai[temp.nd_kiekis++] = pazymys;
    }

    cout << "Egzamino rezultatas: ";
    cin >> temp.egzaminas;

    // dinaminis masyvas studentams
    Student* tempArray = new Student[studentu_kiekis + 1];
    for (int i = 0; i < studentu_kiekis; i++) {
        tempArray[i] = studentai[i]; // kad nesidvigubintu
    }
    tempArray[studentu_kiekis] = temp; // naujas studentas

    delete[] studentai; // isvalo atminti
    studentai = tempArray; // atnaujina rodykle
    studentu_kiekis++;
}

void atlaisvintiAtmintį(Student*& studentai, int studentu_kiekis) {
    for (int i = 0; i < studentu_kiekis; i++) {
        delete[] studentai[i].namu_darbai; // isvalo dinamini masyva
    }
    delete[] studentai; // isvalo masyva
    studentai = nullptr; // nunulina rodykle
}

void spausdintiStudentus(const Student* studentai, int studentu_kiekis) {
    cout << "--------------------------------------------\n";
    cout << "Vardas\t\tPavarde\t\tGalutinis (Vid.)\n";
    cout << "--------------------------------------------\n";

    for (int i = 0; i < studentu_kiekis; i++) {
        double suma = 0;
        for (int j = 0; j < studentai[i].nd_kiekis; j++) {
            suma += studentai[i].namu_darbai[j];
        }
        double vidurkis = (studentai[i].nd_kiekis > 0) ? (suma / studentai[i].nd_kiekis) : 0;
        double galutinis = 0.4 * vidurkis + 0.6 * studentai[i].egzaminas;

        cout << studentai[i].vardas << "\t\t" << studentai[i].pavarde
             << "\t\t" << galutinis << endl;
    }
}

int main(){
    Student* studentai = nullptr;
    int studentu_kiekis = 0;

    cout << "Iveskite studentu duomenis. Kad baigti, iveskite '-1' vietoj vardo.\n";

    while (true) {
        int beforeCount = studentu_kiekis;
        ivestiStudenta(studentai, studentu_kiekis);

        if (beforeCount == studentu_kiekis) { // jei nepadidejo, tai -1 buvo ivestas
            break;
        }
    }

    spausdintiStudentus(studentai, studentu_kiekis);

    delete[] studentai; // isvalo atminti

    return 0;
}