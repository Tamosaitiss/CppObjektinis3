#include "studentai.h"

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
        if (isdigit(c)) return false;
    }
    return true;
}

bool tikrintiSkaiciu(const string &input) {
    for (char c : input) {
        if (!isdigit(c)) return false;
    }
    return true;
}

double skaiciuotiMediana(vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;

    sort(pazymiai.begin(), pazymiai.end());

    int dydis = pazymiai.size();
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

void isvestiKlaida(const string &klausimas) {
    cerr << "Klaida: " << klausimas << endl;
}

void ivestiStudenta(vector<Student>& studentai, int pasirinkimas) {
    Student s;

    if (pasirinkimas == 3) {
        s.vardas = generuotiVarda();
        s.pavarde = generuotiPavarde();
        cout << "Generuojamas studentas: " << s.vardas << " " << s.pavarde << endl;
        int ndKiekis = rand() % 10 + 1;
        s.namu_darbai = generuotiAtsitiktiniusPazymius(ndKiekis);
        s.egzaminas = generuotiAtsitiktiniEgzaminoBala();
    }
    else {
        // Vardas
        bool ivestasVardasTeisingai = false;
        while (!ivestasVardasTeisingai) {
            cout << "Vardas: ";
            cin >> s.vardas;
            if (s.vardas == "-1") return;

            if (!tikrintiTeksta(s.vardas)) {
                isvestiKlaida("Varda gali sudaryti tik raides!");
            } else {
                ivestasVardasTeisingai = true;
            }
        }

        // Pavarde
        bool ivestaPavardeTeisingai = false;
        while (!ivestaPavardeTeisingai) {
            cout << "Pavarde: ";
            cin >> s.pavarde;

            if (!tikrintiTeksta(s.pavarde)) {
                isvestiKlaida("Pavarde gali sudaryti tik raides!");
            } else {
                ivestaPavardeTeisingai = true;
            }
        }

        if (pasirinkimas == 2) {
            int ndKiekis = rand() % 10 + 1;
            s.namu_darbai = generuotiAtsitiktiniusPazymius(ndKiekis);
            s.egzaminas = generuotiAtsitiktiniEgzaminoBala();
        } else {
            cout << "Iveskite namu darbu rezultatus (-1 jei baigta):\n";
            int pazymys;
            while (true) {
                cin >> pazymys;

                // Patikriname, ar įvestas duomuo yra skaičius
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    isvestiKlaida("Namu darbo rezultatas turi buti skaicius!");
                    continue;
                }

                if (pazymys == -1) break;

                s.namu_darbai.push_back(pazymys);
            }

            // Tikriname, ar egzaminų rezultatas yra teisingas (tik skaičius)
            bool egzaminasTeisingai = false;
            while (!egzaminasTeisingai) {
                cout << "Egzamino rezultatas: ";
                cin >> s.egzaminas;

                // Patikriname, ar įvestas egzaminų rezultatas yra skaičius
                if (cin.fail()) {
                    cin.clear(); // Išvalome klaidą
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    isvestiKlaida("Egzamino rezultatas turi buti skaicius!");
                } else {
                    egzaminasTeisingai = true;
                }
            }
        }
    }

    studentai.push_back(s);
    cout << "Studentas pridetas: " << s.vardas << " " << s.pavarde << endl;
}

void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas) {
    ifstream fin(failoPavadinimas);
    if (!fin.is_open()) {
        cerr << "Klaida! Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return;
    }

    string eilute;
    getline(fin, eilute);

    while (getline(fin, eilute)) {
        Student s;
        stringstream ss(eilute);
        ss >> s.vardas >> s.pavarde;
        int pazymys;
        while (ss >> pazymys) {
            if (ss.peek() == '\n') {
                s.egzaminas = pazymys;
                break;
            }
            s.namu_darbai.push_back(pazymys);
        }
        studentai.push_back(s);
    }

    fin.close();
}

void issaugotiIFaila(const vector<Student>& studentai, const string& failoPavadinimas, bool naudotiMediana) {
    ofstream outFile(failoPavadinimas);
    if (!outFile) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << "!\n";
        return;
    }

    outFile << left << setw(20) << "Vardas"
            << setw(20) << "Pavarde"
            << setw(15) << "Galutinis (Vid.)"
            << setw(15) << "Galutinis (Med.)" << endl;
    outFile << "-----------------------------------------------\n";

    for (const auto& s : studentai) {
        double vidurkis = accumulate(s.namu_darbai.begin(), s.namu_darbai.end(), 0.0) / s.namu_darbai.size();
        double galutinisVid = 0.4 * vidurkis + 0.6 * s.egzaminas;
        double galutinisMed = 0.4 * skaiciuotiMediana(s.namu_darbai) + 0.6 * s.egzaminas;

        outFile << left << setw(20) << s.vardas
                << setw(20) << s.pavarde
                << fixed << setprecision(2) << setw(15) << galutinisVid
                << setw(15) << galutinisMed << endl;
    }

    outFile.close();
    cout << "Duomenys issaugoti faile: " << failoPavadinimas << ".\n";
}

void rikiuotiStudentus(vector<Student>& studentai, int pasirinkimas) {
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
            double galutinisA = 0.4 * accumulate(a.namu_darbai.begin(), a.namu_darbai.end(), 0.0) / a.namu_darbai.size() + 0.6 * a.egzaminas;
            double galutinisB = 0.4 * accumulate(b.namu_darbai.begin(), b.namu_darbai.end(), 0.0) / b.namu_darbai.size() + 0.6 * b.egzaminas;
            return galutinisA > galutinisB;
        });
        break;
    case 4:
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

    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde"
         << setw(15) << "Galutinis (Vid.)" << setw(15) << "Galutinis (Med.)" << endl;
    cout << string(70, '-') << endl;

    for (const auto& s : studentai) {
        double vidurkis = accumulate(s.namu_darbai.begin(), s.namu_darbai.end(), 0.0) / s.namu_darbai.size();
        double galutinisVid = 0.4 * vidurkis + 0.6 * s.egzaminas;
        double galutinisMed = 0.4 * skaiciuotiMediana(s.namu_darbai) + 0.6 * s.egzaminas;

        cout << left << setw(15) << s.vardas << setw(15) << s.pavarde
             << fixed << setprecision(2) << setw(15) << galutinisVid
             << setw(15) << galutinisMed << endl;
    }

    if (naudotiMediana) {
        issaugotiIFaila(studentai, "rezultatai.txt", naudotiMediana);
    }
}

void vykdytiPrograma() {
    vector<Student> studentai;
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

            cout << "Pasirinkite rikiavimo kriteriju:\n";
            cout << "1 - Pagal varda\n";
            cout << "2 - Pagal pavarde\n";
            cout << "3 - Pagal vidurki\n";
            cout << "4 - Pagal mediana\n";
            int rikiavimoPasirinkimas;
            cin >> rikiavimoPasirinkimas;
            rikiuotiStudentus(studentai, rikiavimoPasirinkimas);

            char saugoti;
            bool irasymas = false;

            cout << "Ar norite issaugoti rezultatus faile? (t/n): ";
            cin >> saugoti;

            if (saugoti == 't') {
                irasymas = true;
            }

            spausdintiStudentus(studentai, irasymas);

        } else {
            int kiekGeneruoti = 1;
            if (meniuPasirinkimas == 3) {
                cout << "Kiek studentu generuoti?: ";
                cin >> kiekGeneruoti;
            }

            for (int i = 0; i < kiekGeneruoti; i++) {
                ivestiStudenta(studentai, meniuPasirinkimas);
            }

            if (studentai.empty()) {
                cout << endl;
                continue;
            }

            char saugoti;
            bool irasymas = false;

            cout << "Ar norite issaugoti rezultatus faile? (t/n): ";
            cin >> saugoti;

            if (saugoti == 't') {
                irasymas = true;
            }

            spausdintiStudentus(studentai, irasymas);
        }
    }
}