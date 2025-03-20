#include "vektoriai.h"

// ✅ Pilnai atkurtos funkcijos iš `v0.4`

vector<int> generuotiAtsitiktiniusPazymius(int kiekis) {
    vector<int> pazymiai;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < kiekis; i++) {
        pazymiai.push_back(dist(gen));
    }
    return pazymiai;
}

int generuotiAtsitiktiniEgzaminoBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
}

double skaiciuotiVidurki(const vector<int>& pazymiai, int egzaminas) {
    if (pazymiai.empty()) return egzaminas;
    double suma = accumulate(pazymiai.begin(), pazymiai.end(), 0);
    double vidurkis = suma / pazymiai.size();
    return 0.4 * vidurkis + 0.6 * egzaminas;
}

double skaiciuotiMediana(const vector<int>& pazymiai, int egzaminas) {
    if (pazymiai.empty()) return egzaminas;

    vector<int> visiPazymiai = pazymiai;
    visiPazymiai.push_back(egzaminas);
    sort(visiPazymiai.begin(), visiPazymiai.end());

    int dydis = visiPazymiai.size();
    if (dydis % 2 == 0) {
        return (visiPazymiai[dydis / 2 - 1] + visiPazymiai[dydis / 2]) / 2.0;
    } else {
        return visiPazymiai[dydis / 2];
    }
}

// ✅ Pridėtos funkcijos studentų duomenų spausdinimui ir rikiavimui
void spausdintiStudentus(const vector<Student>& studentai, bool irasyti) {
    if (studentai.empty()) {
        cout << "Nėra įvestų studentų duomenų.\n";
        return;
    }

    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde"
         << setw(15) << "Galutinis (Vid.)" << setw(15) << "Galutinis (Med.)" << endl;

    for (const auto& studentas : studentai) {
        double vidurkis = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);
        double mediana = skaiciuotiMediana(studentas.namu_darbai, studentas.egzaminas);

        cout << left << setw(15) << studentas.vardas << setw(15) << studentas.pavarde
             << setw(15) << fixed << setprecision(2) << vidurkis
             << setw(15) << fixed << setprecision(2) << mediana << endl;
    }
}

void rikiuotiStudentus(vector<Student>& studentai, int rikiavimoPasirinkimas) {
    switch (rikiavimoPasirinkimas) {
    case 1:
        sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
            return a.vardas < b.vardas;
        });
        break;
    case 2:
        sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
            return a.pavarde < b.pavarde;
        });
        break;
    case 3:
        sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
            return skaiciuotiVidurki(a.namu_darbai, a.egzaminas) > skaiciuotiVidurki(b.namu_darbai, b.egzaminas);
        });
        break;
    default:
        cout << "Klaida! Netinkami kriterijai rūšiavimui." << endl;
        break;
    }
}