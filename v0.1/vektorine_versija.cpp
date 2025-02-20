#include "vektoriai.h"

void ivestiStudenta(vector<Student>& studentai) {
    Student s;
    cout << "Vardas: ";
    cin >> s.vardas;

    if (s.vardas == "-1") return;

    cout << "Pavarde: ";
    cin >> s.pavarde;

    cout << "Iveskite namu darbu rezultatus (-1 jei baigta):\n";
    int pazymys;
    while (true) {
        cin >> pazymys;
        if (pazymys == -1) break;
        s.namu_darbai.push_back(pazymys);
    }

    cout << "Egzamino rezultatas: ";
    cin >> s.egzaminas;

    studentai.push_back(s);  // ✅ Now only valid students get added
}

void spausdintiStudentus(const vector<Student>& studentai) {
    if (studentai.empty()) {
        cout << "Nera ivestu studentu duomenu.\n";
        return;
    }

    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(10) << "Galutinis" << endl;
    cout << string(40, '-') << endl;  // bruksnine linija

    for (const auto& s : studentai) {
        double vidurkis = accumulate(s.namu_darbai.begin(), s.namu_darbai.end(), 0.0) / s.namu_darbai.size();
        double galutinis = 0.4 * vidurkis + 0.6 * s.egzaminas;

        cout << left << setw(15) << s.vardas
             << setw(15) << s.pavarde
             << fixed << setprecision(2) << setw(10) << galutinis
             << endl;
    }
}

int main(){
    vector<Student> studentai;

    cout << "Iveskite studentu duomenis. Kad baigti iveskite '-1' vietoj vardo.\n";

    while (true) {
        int before_size = studentai.size();
        ivestiStudenta(studentai);
        if (studentai.size() == before_size) break;
    }

    spausdintiStudentus(studentai);

    return 0;
}