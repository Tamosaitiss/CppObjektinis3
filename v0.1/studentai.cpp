#include "studentai.h"

// Funkcija sugeneruoja studento vardą
string gautiVarda(int indeksas) {
    return "Vardas" + to_string(indeksas);
}

// Funkcija sugeneruoja studento pavardę
string gautiPavarde(int indeksas) {
    return "Pavarde" + to_string(indeksas);
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

double skaiciuotiVidurki(const vector<int>& pazymiai, int egzaminas) {
    if (pazymiai.empty()) return 0.0;

    double vidurkis = accumulate(pazymiai.begin(), pazymiai.end(), 0.0) / pazymiai.size();
    return 0.4 * vidurkis + 0.6 * egzaminas;
}

double skaiciuotiMediana(const vector<int>& pazymiai, int egzaminas) {
    if (pazymiai.empty()) return 0.0;

    // Sukuriame kopiją ir į ją įtraukiame egzaminą
    vector<int> visiPazymiai = pazymiai;
    visiPazymiai.push_back(egzaminas);

    // Rūšiuojame visus pažymius
    sort(visiPazymiai.begin(), visiPazymiai.end());

    int dydis = visiPazymiai.size();
    double mediana;
    if (dydis % 2 == 0) {
        // Jei pažymių skaičius lygus, mediana bus dviejų vidurinių reikšmių vidurkis
        mediana = (visiPazymiai[dydis / 2 - 1] + visiPazymiai[dydis / 2]) / 2.0;
    } else {
        // Jei pažymių skaičius nelygus, mediana bus vidurinė reikšmė
        mediana = visiPazymiai[dydis / 2];
    }
    return mediana;
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

    // Pasirinkimas 3: Generuoti studentus su vardais, pavardėmis ir pažymiais
    if (pasirinkimas == 3) {
        static bool buvoGeneruota = false;  // Patikrina, ar studentai jau buvo generuoti

        if (!buvoGeneruota) {  // Jei dar nebuvo generuota
            int kiekis;
            cout << "Kiek studentu generuoti?: ";
            cin >> kiekis;

            for (int i = 0; i < kiekis; ++i) {
                s.vardas = gautiVarda(i + 1);
                s.pavarde = gautiPavarde(i + 1);
                cout << "Generuojamas studentas: " << s.vardas << " " << s.pavarde << endl;
                int ndKiekis = rand() % 10 + 1;
                s.namu_darbai = generuotiAtsitiktiniusPazymius(ndKiekis);
                s.egzaminas = generuotiAtsitiktiniEgzaminoBala();
                studentai.push_back(s);
            }
            buvoGeneruota = true;  // Užtikriname, kad generavimas nepasikartotų
        } else {
            cout << "Studentai jau buvo sugeneruoti." << endl;
        }
    }
    // Kitų pasirinkimų atveju įvedame rankiniu būdu
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

        studentai.push_back(s);
        cout << "Studentas pridetas: " << s.vardas << " " << s.pavarde << endl;
    }
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
            double aVidurkis = skaiciuotiVidurki(a.namu_darbai, a.egzaminas);
            double bVidurkis = skaiciuotiVidurki(b.namu_darbai, b.egzaminas);
            return aVidurkis > bVidurkis;
        });
        break;
    case 4:
        sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
            double aMediana = skaiciuotiMediana(a.namu_darbai, a.egzaminas);
            double bMediana = skaiciuotiMediana(b.namu_darbai, b.egzaminas);
            return aMediana > bMediana;
        });
        break;
    default:
        cout << "Klaida! Netinkami kriterijai rusiavimui." << endl;
        break;
    }
}

void spausdintiStudentus(const vector<Student>& studentai, bool irasyti) {
    if (studentai.empty()) {
        cout << "Nera ivestu studentu duomenu.\n";
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

    if (irasyti) {
        string failoPavadinimas = "studentai.txt";
        ofstream fout(failoPavadinimas);
        if (!fout.is_open()) {
            cout << "Nepavyko atidaryti failo rašymui." << endl;
            return;
        }

        fout << left << setw(15) << "Vardas" << setw(15) << "Pavarde"
             << setw(15) << "Galutinis (Vid.)" << setw(15) << "Galutinis (Med.)" << endl;

        for (const auto& studentas : studentai) {
            double vidurkis = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);
            double mediana = skaiciuotiMediana(studentas.namu_darbai, studentas.egzaminas);

            fout << left << setw(15) << studentas.vardas << setw(15) << studentas.pavarde
                 << setw(15) << fixed << setprecision(2) << vidurkis
                 << setw(15) << fixed << setprecision(2) << mediana << endl;
        }
    }
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
        double galutinisMed = 0.4 * skaiciuotiMediana(s.namu_darbai, s.egzaminas) + 0.6 * s.egzaminas;

        outFile << left << setw(20) << s.vardas
                << setw(20) << s.pavarde
                << fixed << setprecision(2) << setw(15) << galutinisVid
                << setw(15) << galutinisMed << endl;
    }

    outFile.close();
    cout << "Duomenys issaugoti faile: " << failoPavadinimas << ".\n";
}

void suskirstytiStudentusIrIrasytiISFailus(const vector<Student>& studentai) {
    vector<Student> vargsiukai;
    vector<Student> kietiakiai;

    // Suskirstome studentus pagal galutinį balą
    for (const auto& studentas : studentai) {
        double galutinisBalas = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);

        if (galutinisBalas < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            kietiakiai.push_back(studentas);
        }
    }

    issaugotiIFaila(vargsiukai, "vargsiukai.txt", false);
    issaugotiIFaila(kietiakiai, "kietiakiai.txt", false);
}

// studentai.cpp
void generuotiVienaFaila(int kiekis) {
    string failoPavadinimas = "studentai_" + to_string(kiekis) + ".txt";
    ofstream failas(failoPavadinimas);

    if (!failas) {
        cerr << "Klaida kuriant failą: " << failoPavadinimas << endl;
        return;
    }

    failas << "Vardas Pavarde Namu_darbai Egzaminas\n";

    for (int i = 1; i <= kiekis; ++i) {
        string vardas = gautiVarda(i);
        string pavarde = gautiPavarde(i);
        vector<int> namu_darbai = generuotiAtsitiktiniusPazymius(10);
        int egzaminas = generuotiAtsitiktiniEgzaminoBala();

        failas << vardas << " " << pavarde << " ";
        for (int pazymys : namu_darbai) {
            failas << pazymys << " ";
        }
        failas << egzaminas << "\n";
    }

    failas.close();
    cout << "Failas sukurtas: " << failoPavadinimas << endl;
}

void generuotiFailus(int kiekis) {
    vector<int> kiekiai = {1000, 10000, 100000, 1000000, 10000000};

    cout << "Pasirinkite, kurį failą generuoti:\n";
    for (size_t i = 0; i < kiekiai.size(); ++i) {
        cout << i + 1 << " - " << kiekiai[i] << " studentų\n";
    }
    cout << "0 - Generuoti visus failus\n";

    int pasirinkimas;
    cin >> pasirinkimas;

    if (pasirinkimas == 0) {
        // Generuojami visi failai
        for (int kiekis : kiekiai) {
            generuotiVienaFaila(kiekis);
        }
    } else if (pasirinkimas >= 1 && pasirinkimas <= kiekiai.size()) {
        // Generuojamas tik pasirinktas failas
        generuotiVienaFaila(kiekiai[pasirinkimas - 1]);
    } else {
        cout << "Neteisingas pasirinkimas!\n";
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
        cout << "5 - Generuoti studentu failus\n";
        cout << "6 - Baigti darba\n";
        cout << "Pasirinkite: ";
        cin >> meniuPasirinkimas;

        if (meniuPasirinkimas == 6) break;

        if (meniuPasirinkimas == 5) {
            generuotiFailus(5); // Call the function with the argument 5
        } else if (meniuPasirinkimas == 4) {
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
                //cout << "Kiek studentu generuoti?: ";
                //cin >> kiekGeneruoti;
            }

            for (int i = 0; i < kiekGeneruoti; i++) {
                ivestiStudenta(studentai, meniuPasirinkimas);
            }

            if (studentai.empty()) {
                cout << endl;
                continue;
            }

            // Ask for sorting criteria after input
            cout << "Pasirinkite rikiavimo kriteriju:\n";
            cout << "1 - Pagal varda\n";
            cout << "2 - Pagal pavarde\n";
            cout << "3 - Pagal vidurki\n";
            cout << "4 - Pagal mediana\n";
            int rikiavimoPasirinkimas;
            cin >> rikiavimoPasirinkimas;

            // Sort students based on the selected criteria
            rikiuotiStudentus(studentai, rikiavimoPasirinkimas);

            // Ask if the user wants to save the results
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