#include "hibridas.h"

vector<string> galimiVardai = {"Giedre", "Ona", "Vanesa", "Ieva", "Liepa", "Ema", "Martyna", "Goda"};
vector<string> galimosPavardes = {"Giedraitiene", "Petraitiene", "Kazlauskiene", "Balciuniene", "Jankauskiene", "Rutkauskiene", "Sabaliauskiene"};

string generuotiVarda() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, galimiVardai.size() - 1);
    return galimiVardai[dist(gen)];
}

string generuotiPavarde() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, galimosPavardes.size() - 1);
    return galimosPavardes[dist(gen)];
}

bool tikrintiTeksta(const string &tekstas) {
    if (tekstas == "-1") return true; // leidziama irasyti -1
    for (char c : tekstas) {
        if (isdigit(c)) return false; // nepriima vardu su sk.
    }
    return true;
}

bool tikrintiSkaiciu(const string &input) {
    for (char c : input) {
        if (!isdigit(c)) return false; // leidzia ivesti tik skaicius
    }
    return true;
}

double skaiciuotiMediana(int* pazymiai, int nd_kiekis) {
    if (nd_kiekis == 0) return 0.0;

    vector<int> paz(pazymiai, pazymiai + nd_kiekis); // kopijuoja dinamini masyva vektoriu rusiavimui
    sort(paz.begin(), paz.end());

    if (nd_kiekis % 2 == 0) {
        return (paz[nd_kiekis / 2 - 1] + paz[nd_kiekis / 2]) / 2.0;
    } else {
        return paz[nd_kiekis / 2];
    }
}

int* generuotiAtsitiktiniusPazymius(int kiekis) {
    int* pazymiai = new int[kiekis];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < kiekis; i++) {
        pazymiai[i] = dist(gen);
    }

    return pazymiai;
}

int generuotiAtsitiktiniEgzaminoBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100);
    return dist(gen);
}

void ivestiStudenta(vector<Student>& studentai, int pasirinkimas) {
    Student s;

    if (pasirinkimas == 3) {
        s.vardas = generuotiVarda();
        s.pavarde = generuotiPavarde();
        cout << "Generuojamas studentas: " << s.vardas << " " << s.pavarde << endl;
    } else {
        while (true) {
            cout << "Vardas: ";
            cin >> s.vardas;

            if (s.vardas == "-1") return;
            if (tikrintiTeksta(s.vardas)) break;

            cout << "Klaida! Vardas negali tureti skaiciu. Bandykite dar karta.\n";
        }

        while (true) {
            cout << "Pavarde: ";
            cin >> s.pavarde;

            if (tikrintiTeksta(s.pavarde)) break;
            cout << "Klaida! Pavarde negali tureti skaiciu. Bandykite dar karta.\n";
        }
    }

    if (pasirinkimas == 2 || pasirinkimas == 3) {
        s.nd_kiekis = rand() % 10 + 1;
        s.namu_darbai = generuotiAtsitiktiniusPazymius(s.nd_kiekis);
        s.egzaminas = generuotiAtsitiktiniEgzaminoBala();
    } else {
        cout << "Iveskite namu darbu rezultatus (-1 jei baigta):\n";
        int pazymys;
        string input;
        vector<int> laikini;

        while (true) {
            cin >> input;
            if (input == "-1") break;

            while (!tikrintiSkaiciu(input)) {
                cout << "Klaida! Iveskite tik skaicius (1-10): ";
                cin >> input;
            }

            pazymys = stoi(input);
            if (pazymys < 1 || pazymys > 10) {
                cout << "Klaida! Pazymys turi buti tarp 1 ir 10. Bandykite dar karta: ";
            } else {
                laikini.push_back(pazymys);
            }
        }

        s.nd_kiekis = laikini.size();
        s.namu_darbai = new int[s.nd_kiekis];
        for (int i = 0; i < s.nd_kiekis; i++) {
            s.namu_darbai[i] = laikini[i];
        }

        while (true) {
            cout << "Egzamino rezultatas: ";
            cin >> input;

            if (tikrintiSkaiciu(input) && stoi(input) >= 1 && stoi(input) <= 100) {
                s.egzaminas = stoi(input);
                break;
            }

            cout << "Klaida! Egzamino rezultatas turi buti tarp 1 ir 100. Bandykite dar karta.\n";
        }
    }
    studentai.push_back(s);
}

void spausdintiStudentus(const vector<Student>& studentai, bool naudotiMediana) {
    if (studentai.empty()) {
        cout << "Nera ivestu studentu duomenu.\n";
        return;
    }

    cout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(15) << (naudotiMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)")
         << endl;
    cout << string(50, '-') << endl;

    for (const auto& s : studentai) {
        double galutinis;

        if (naudotiMediana) {
            galutinis = 0.4 * skaiciuotiMediana(s.namu_darbai, s.nd_kiekis) + 0.6 * s.egzaminas;
        } else {
            double suma = 0;
            for (int i = 0; i < s.nd_kiekis; i++) {
                suma += s.namu_darbai[i];
            }
            double vidurkis = (s.nd_kiekis > 0) ? suma / s.nd_kiekis : 0;
            galutinis = 0.4 * vidurkis + 0.6 * s.egzaminas;
        }

        cout << left << setw(15) << s.vardas<< setw(15) << s.pavarde<< fixed << setprecision(2) << setw(15) << galutinis<< endl;
    }
}


int main(){
    vector<Student> studentai;
    char pasirinkimas;
    int meniuPasirinkimas;

    while (true) {
        cout << "\nMeniu:\n";
        cout << "1 - Rankinis ivedimas\n";
        cout << "2 - Generuoti tik pazymius\n";
        cout << "3 - Generuoti vardus, pavardes ir pazymius\n";
        cout << "4 - Baigti darba\n";
        cout << "Pasirinkite: ";
        cin >> meniuPasirinkimas;

        while (meniuPasirinkimas < 1 || meniuPasirinkimas > 4) {
            cout << "Klaida! Pasirinkite 1, 2, 3 arba 4: ";
            cin >> meniuPasirinkimas;
        }

        if (meniuPasirinkimas == 4) {
            cout << "Programa baigta.\n";
            break;
        }

        cout << "Iveskite studentu duomenis. Jei norite baigti, iveskite '-1' vietoj vardo.\n";

        if (meniuPasirinkimas == 3) {
            int studentuKiekis;
            cout << "Kiek studentu norite sugeneruoti?: ";
            cin >> studentuKiekis;

            while (studentuKiekis <= 0) {
                cout << "Klaida! Iveskite bent viena studenta: ";
                cin >> studentuKiekis;
            }

            for (int i = 0; i < studentuKiekis; i++) {
                ivestiStudenta(studentai, meniuPasirinkimas);
            }
            } else {
                while (true) {
                    int before_size = studentai.size();
                    ivestiStudenta(studentai, meniuPasirinkimas);
                    if (studentai.size() == before_size) break;
                }
            }

            cout << "Pasirinkite skaiciavimo buda (1 - vidurkis, 2 - mediana): ";
            cin >> pasirinkimas;

            bool naudotiMediana = (pasirinkimas == '2');
            spausdintiStudentus(studentai, naudotiMediana);
        }

    return 0;
}