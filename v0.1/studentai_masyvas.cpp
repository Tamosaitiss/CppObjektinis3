#include "studentai_masyvas.h"

int main() {
    Student studentai[MAX_STUDENTU];
    int studentu_kiekis = 0;

    cout << "Iveskite studentu duomenis. Kad baigti iveskite '-1' vietoj vardo.\n";

    while (true) {
        int priesIvedima = studentu_kiekis;
        ivestiStudenta(studentai, studentu_kiekis);
        if (priesIvedima == studentu_kiekis) {
            break;
        }
    }

    spausdintiStudentus(studentai, studentu_kiekis);

    return 0;
}