#include "vektoriai.h"

vector<string> galimiVardai = {"Jonas", "Ignas", "Petras", "Justas", "Lukas", "Kristijonas", "Marius", "Matas"};
vector<string> galimosPavardes = {"Jonaitis", "Petraitis", "Kazlauskas", "Balciunas", "Jankauskas", "Rutkauskas", "Sabaliauskas"};

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
    for (char c : tekstas) {
        if (isdigit(c)) return false; // leidziamos tik raides
    }
    return true;
}

bool tikrintiSkaiciu(const string &input) {
    for (char c : input) {
        if (!isdigit(c)) return false; // leidziami tik skaiciai
    }
    return true;
}

double skaiciuotiMediana(vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;

    sort(pazymiai.begin(), pazymiai.end());
    size_t dydis = pazymiai.size();

    if (dydis % 2 == 0) {
        return (pazymiai[dydis / 2 - 1] + pazymiai[dydis / 2]) / 2.0;
    } else {
        return pazymiai[dydis / 2];
    }
}

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
    uniform_int_distribution<int> dist(1, 100);
    return dist(gen);
}

void ivestiStudenta(vector<Student>& studentai, int pasirinkimas) {
    Student s;

    if (pasirinkimas == 3) { // Generuoja vardus/pavardes ir rez
        s.vardas = generuotiVarda();
        s.pavarde = generuotiPavarde();
        cout << "Generuojamas studentas: " << s.vardas << " " << s.pavarde << endl;
    } else {
        while (true) {
            cout << "Vardas: ";
            cin >> s.vardas;

            if (s.vardas == "-1") return;
            if (tikrintiTeksta(s.vardas)) break;

            cout << "Klaida! Vardas negali turėti skaiciu. Bandykite dar karta.\n";
        }

        while (true) {
            cout << "Pavarde: ";
            cin >> s.pavarde;

            if (tikrintiTeksta(s.pavarde)) break;
            cout << "Klaida! Pavarde negali turėti skaiciu. Bandykite dar karta.\n";
        }
    }

    if (pasirinkimas == 2 || pasirinkimas == 3) {
        int ndKiekis = rand() % 10 + 1;
        s.namu_darbai = generuotiAtsitiktiniusPazymius(ndKiekis);
        s.egzaminas = generuotiAtsitiktiniEgzaminoBala();
    } else {
        cout << "Iveskite namu darbu rezultatus (-1 jei baigta):\n";
        int pazymys;
        string input;

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
                s.namu_darbai.push_back(pazymys);
            }
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

void nuskaitytiIsFailo(vector<Student> &studentai, const string &failoPavadinimas) {
    ifstream fin("studentai10000.txt");
    if (!fin) {
        cerr << "Klaida! Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return;
    }

    string eilute;
    getline(fin, eilute); // ignoruoja headeri

    while (!fin.eof()) {
        Student s;
        fin >> s.vardas >> s.pavarde; // paima varda ir pavarde

        int pazymys;
        while (fin >> pazymys) {
            if (fin.peek() == '\n') { // paskutinis skaicius eiluteje yra egzamino balas
                s.egzaminas = pazymys;
                break;
            }
            s.namu_darbai.push_back(pazymys);
        }
        studentai.push_back(s);
    }
    fin.close();
}

void issaugotiIFaila(const vector<Student> &studentai, const string &failoPavadinimas, bool naudotiMediana) {
    ofstream fout("rezultatai.txt");
    if (!fout) {
        cerr << "Klaida! Nepavyko sukurti failo: " << failoPavadinimas << endl;
        return;
    }

    fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << (naudotiMediana?"Galutinis (Med.)" : "Galutinis (Vid.)") << endl;
    fout << string(80, '-') << endl;

    for (const auto& s : studentai) {
        double galutinis;
        if (naudotiMediana) {
            galutinis = 0.4 * skaiciuotiMediana(s.namu_darbai) + 0.6 * s.egzaminas;
        } else {
            double vidurkis = accumulate(s.namu_darbai.begin(), s.namu_darbai.end(), 0.0) / s.namu_darbai.size();
            galutinis = 0.4 * vidurkis + 0.6 * s.egzaminas;
        }
        fout << left << setw(15) << s.vardas << setw(15) << s.pavarde << fixed << setprecision(2) << setw(15) << galutinis << endl;
    }
    fout.close();
}

void rikiuotiStudentus(vector<Student> &studentai, int pasirinkimas) {
    switch (pasirinkimas) {
    case 1:
        sort(studentai.begin(), studentai.end(), [](const Student &a, const Student &b) {
            return a.vardas < b.vardas;
        });
        break;
    case 2:
        sort(studentai.begin(), studentai.end(), [](const Student &a, const Student &b) {
            return a.pavarde < b.pavarde;
        });
        break;
    case 3:
        sort(studentai.begin(), studentai.end(), [](const Student &a, const Student &b) {
            double galutinisA = 0.4 * skaiciuotiMediana(a.namu_darbai) + 0.6 * a.egzaminas;
            double galutinisB = 0.4 * skaiciuotiMediana(b.namu_darbai) + 0.6 * b.egzaminas;
            return galutinisA > galutinisB;
        });
        break;
    }
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
            galutinis = 0.4 * skaiciuotiMediana(s.namu_darbai) + 0.6 * s.egzaminas;
        } else {
            double vidurkis = accumulate(s.namu_darbai.begin(), s.namu_darbai.end(), 0.0) / s.namu_darbai.size();
            galutinis = 0.4 * vidurkis + 0.6 * s.egzaminas;
        }

        cout << left << setw(15) << s.vardas
             << setw(15) << s.pavarde
             << fixed << setprecision(2) << setw(15) << galutinis
             << endl;
    }
}

int main() {
    vector<Student> studentai;
    char pasirinkimas;
    int meniuPasirinkimas;

    while (true) {
        cout << "\nMeniu:\n";
        cout << "1 - Rankinis ivedimas\n";
        cout << "2 - Generuoti tik pazymius\n";
        cout << "3 - Generuoti vardus, pavardes ir pazymius\n";
        cout << "4 - Nuskaityti is failo\n";
        cout << "5 - Baigti darba\n";
        cout << "Pasirinkite: ";
        cin >> meniuPasirinkimas;

        if (meniuPasirinkimas == 5) break;

        if (meniuPasirinkimas == 4) {
            nuskaitytiIsFailo(studentai, "studentai10000.txt");
        } else {
            while (true) {
                int before_size = studentai.size();
                ivestiStudenta(studentai, pasirinkimas);
                if (studentai.size() == before_size) break;
            }
        }

        cout << "Pasirinkite rikiavimo kriteriju:\n";
        cout << "1 - Pagal varda\n";
        cout << "2 - Pagal pavarde\n";
        cout << "3 - Pagal galutini pazymi\n";
        int rikiavimoPasirinkimas;
        cin >> rikiavimoPasirinkimas;
        rikiuotiStudentus(studentai, rikiavimoPasirinkimas);

        cout << "Rezultatus saugoti faile? (t/n): ";
        char saugoti;
        cin >> saugoti;
        if (saugoti == 't') {
            issaugotiIFaila(studentai, "rezultatai.txt", true);
        } else {
            spausdintiStudentus(studentai, true);
        }
    }

    return 0;
}