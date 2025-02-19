#include "hibridas.h"

void ivestiStudenta(Student*& studentai, int& studentu_kiekis) {
    Student temp;

    cout << "Vardas: ";
    cin >> temp.vardas;
    if (temp.vardas == "-1") return; // If "-1", return immediately and do NOT add to array

    cout << "Pavarde: ";
    cin >> temp.pavarde;

    cout << "Iveskite namu darbu rezultatus (-1 jei baigta):\n";
    temp.nd_kiekis = 0;
    temp.namu_darbai = new int[100]; // Assume max 100 grades for safety

    while (true) {
        int pazymys;
        cin >> pazymys;
        if (pazymys == -1) break;
        temp.namu_darbai[temp.nd_kiekis++] = pazymys;
    }

    cout << "Egzamino rezultatas: ";
    cin >> temp.egzaminas;

    // Allocate new memory for students and copy
    Student* tempArray = new Student[studentu_kiekis + 1];
    for (int i = 0; i < studentu_kiekis; i++) {
        tempArray[i] = studentai[i]; // Copy existing students
    }
    tempArray[studentu_kiekis] = temp; // Add new student

    delete[] studentai; // Free old memory
    studentai = tempArray; // Update pointer
    studentu_kiekis++; // Increase count
}

void atlaisvintiAtmintį(Student*& studentai, int studentu_kiekis) {
    for (int i = 0; i < studentu_kiekis; i++) {
        delete[] studentai[i].namu_darbai; // Free each student's dynamic array
    }
    delete[] studentai; // Free the student array itself
    studentai = nullptr; // Avoid dangling pointer
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

        if (beforeCount == studentu_kiekis) { // If count didn't increase, "-1" was entered
            break;
        }
    }

    spausdintiStudentus(studentai, studentu_kiekis);

    delete[] studentai; // isvalo atminti

    return 0;
}