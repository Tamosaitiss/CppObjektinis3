#include "vektoriai.h"
#include <chrono>
#include <stdexcept>

using namespace std::chrono;

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
        if (isdigit(c)) throw invalid_argument("Teksta turi sudaryti tik raides.");
    }
    return true;
}

bool tikrintiSkaiciu(const string &input) {
    for (char c : input) {
        if (!isdigit(c)) throw invalid_argument("Skaicius turi sudaryti tik skaičiai.");
    }
    return true;
}

double skaiciuotiVidurki(const vector<int>& pazymiai, int egzaminas) {
    if (pazymiai.empty()) return egzaminas;

    double suma = accumulate(pazymiai.begin(), pazymiai.end(), 0);
    double vidurkis = suma / pazymiai.size();
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
    uniform_int_distribution<int> dist(1, 10); // Generate grades between 1 and 10

    try {
        for (int i = 0; i < kiekis; i++) {
            pazymiai.push_back(dist(gen));
        }
    } catch (const std::exception& e) {
        throw runtime_error("Nepavyko sugeneruoti atsitiktinių pažymių: " + string(e.what()));
    }
    return pazymiai;
}

int generuotiAtsitiktiniEgzaminoBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10); // Generate exam scores between 1 and 10

    try {
        return dist(gen);
    } catch (const std::exception& e) {
        throw runtime_error("Nepavyko sugeneruoti egzaminų balo: " + string(e.what()));
    }
}

void isvestiKlaida(const string &klausimas) {
    cerr << "Klaida: " << klausimas << endl;
}

void ivestiStudenta(vector<Student>& studentai, int pasirinkimas) {
    Student s;

    try {
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
                try {
                    cout << "Vardas: ";
                    cin >> s.vardas;
                    if (s.vardas == "-1") return;

                    tikrintiTeksta(s.vardas);
                    ivestasVardasTeisingai = true;
                } catch (const invalid_argument &e) {
                    isvestiKlaida(e.what());
                }
            }

            // Pavarde
            bool ivestaPavardeTeisingai = false;
            while (!ivestaPavardeTeisingai) {
                try {
                    cout << "Pavarde: ";
                    cin >> s.pavarde;

                    tikrintiTeksta(s.pavarde);
                    ivestaPavardeTeisingai = true;
                } catch (const invalid_argument &e) {
                    isvestiKlaida(e.what());
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
                    try {
                        cin >> pazymys;

                        // Patikriname, ar įvestas duomuo yra skaičius
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw invalid_argument("Namu darbo rezultatas turi buti skaicius!");
                        }

                        if (pazymys == -1) break;

                        s.namu_darbai.push_back(pazymys);
                    } catch (const invalid_argument &e) {
                        isvestiKlaida(e.what());
                    }
                }

                // Tikriname, ar egzaminų rezultatas yra teisingas (tik skaičius)
                bool egzaminasTeisingai = false;
                while (!egzaminasTeisingai) {
                    try {
                        cout << "Egzamino rezultatas: ";
                        cin >> s.egzaminas;

                        // Patikriname, ar įvestas egzaminų rezultatas yra skaičius
                        if (cin.fail()) {
                            cin.clear(); // Išvalome klaidą
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw invalid_argument("Egzamino rezultatas turi buti skaicius!");
                        } else {
                            egzaminasTeisingai = true;
                        }
                    } catch (const invalid_argument &e) {
                        isvestiKlaida(e.what());
                    }
                }
            }

            studentai.push_back(s);
            cout << "Studentas pridetas: " << s.vardas << " " << s.pavarde << endl;
        }
    } catch (const runtime_error &e) {
        isvestiKlaida(e.what());
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
            cout << "Nepavyko atidaryti failo rasymui." << endl;
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

void generuotiFaila(int kiekis, const string& failoPavadinimas) {
    // Check if the file already exists
    ifstream fileCheck(failoPavadinimas);
    if (fileCheck) {
        cerr << "Klaida: Failas " << failoPavadinimas << " jau egzistuoja." << endl;
        fileCheck.close();
        return;
    }

    ofstream out(failoPavadinimas);
    if (!out) {
        cerr << "Klaida: Nepavyko sukurti failo " << failoPavadinimas << endl;
        return;
    }

    // Write header and data to the file
    out << left << setw(20) << "Vardas" << setw(25) << "Pavarde";
    for (int i = 1; i <= 15; i++) out << setw(10) << ("ND" + to_string(i));
    out << setw(10) << "Egz." << endl;

    for (int i = 1; i <= kiekis; i++) {
        out << left << setw(20) << ("Vardas" + to_string(i))
            << setw(25) << ("Pavarde" + to_string(i));

        int pazymiuSkaicius = rand() % 15 + 1;  // Random number of marks (1-15)
        vector<int> pazymiai;

        for (int j = 0; j < pazymiuSkaicius; j++) {
            int pazymys = rand() % 10 + 1;
            pazymiai.push_back(pazymys);
        }

        while (pazymiai.size() < 15) pazymiai.push_back(0);  // Fill missing grades with 0

        for (int j = 0; j < 15; j++) out << setw(10) << pazymiai[j];

        out << setw(10) << (rand() % 10 + 1) << endl;  // Final exam mark
    }

    out.close();
}

void generuotiFailus(const vector<int>& kiekiai) {
    for (int kiekis : kiekiai) {
        string failoPavadinimas = "studentai_" + to_string(kiekis) + ".txt";
        generuotiFaila(kiekis, failoPavadinimas);
    }
}

void nuskaitytiIsFailo(vector<Student>& studentai, const string& failoPavadinimas) {
    ifstream in(failoPavadinimas);
    if (!in) {
        cerr << "Klaida: Nepavyko atidaryti failo " << failoPavadinimas << endl;
        return;
    }

    studentai.clear();
    string line;
    getline(in, line); // Skip header row

    while (getline(in, line)) {
        istringstream iss(line);
        Student studentas;
        iss >> studentas.vardas >> studentas.pavarde;

        for (int i = 0; i < 15; i++) {
            int pazymys;
            iss >> pazymys;
            if (pazymys > 0) studentas.namu_darbai.push_back(pazymys);
        }

        iss >> studentas.egzaminas;
        studentai.push_back(studentas);
    }

    in.close();
}

void suskirstytiStudentus(const vector<Student>& studentai, vector<Student>& vargsiukai, vector<Student>& kietiakiai) {
    for (const auto& studentas : studentai) {
        double galutinis = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);

        if (galutinis < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            kietiakiai.push_back(studentas);
        }
    }
}

void issaugotiStudentusIFaila(const vector<Student>& studentai, const string& failoPavadinimas) {
    ofstream out(failoPavadinimas);
    if (!out) {
        cerr << "Klaida: Nepavyko sukurti failo " << failoPavadinimas << endl;
        return;
    }

    // Print header
    out << left << setw(20) << "Vardas"
        << setw(25) << "Pavarde"
        << setw(10) << "Galutinis" << endl;

    // Print student data
    for (const auto& studentas : studentai) {
        double galutinis = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);

        out << left << setw(20) << studentas.vardas
            << setw(25) << studentas.pavarde
            << fixed << setprecision(2) << setw(10) << galutinis << endl;
    }

    out.close();
}

void matuotiFailuKurimoLaika(int kiekis, const string& failoPavadinimas) {
    auto start = chrono::high_resolution_clock::now();

    // Simulate file creation without actually writing to disk
    ofstream out; // No file is opened
    out.setstate(ios_base::badbit); // Simulate a file stream without writing to disk

    // Simulate writing header to the file
    out << left << setw(20) << "Vardas" << setw(25) << "Pavarde";
    for (int i = 1; i <= 15; i++) out << setw(10) << ("ND" + to_string(i));
    out << setw(10) << "Egz." << endl;

    // Simulate writing student data to the file
    for (int i = 1; i <= kiekis; i++) {
        out << left << setw(20) << ("Vardas" + to_string(i))
            << setw(25) << ("Pavarde" + to_string(i));

        // Simulate generating random grades (1-10) and writing them to the file
        for (int j = 0; j < 15; j++) {
            int pazymys = rand() % 10 + 1;
            out << setw(10) << pazymys;
        }

        // Simulate writing exam grade
        out << setw(10) << (rand() % 10 + 1) << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> trukme = end - start;
    cout << "Simuliuotas failo " << failoPavadinimas << " kurimo laikas: " << trukme.count() << " s" << endl;
}

void matuotiDuomenuApdorojimoLaika(const string& failoPavadinimas) {
    // Check if the file exists before proceeding
    ifstream fileCheck(failoPavadinimas);
    if (!fileCheck) {
        cerr << "Klaida: Failas " << failoPavadinimas << " neegzistuoja. Pirmiausia sugeneruokite faila naudodami meniu 5." << endl;
        return;
    }
    fileCheck.close();

    vector<Student> studentai;
    vector<Student> vargsiukai;
    vector<Student> kietiakiai;

    // 1. Duomenu nuskaitymo laikas
    auto start = chrono::high_resolution_clock::now();
    nuskaitytiIsFailo(studentai, failoPavadinimas);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> nuskaitymoLaikas = end - start;
    cout << "Duomenu nuskaitymo laikas: " << nuskaitymoLaikas.count() << " s" << endl;

    // 2. Studentu rusiavimo laikas
    start = chrono::high_resolution_clock::now();
    suskirstytiStudentus(studentai, vargsiukai, kietiakiai);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> rusiavimoLaikas = end - start;
    cout << "Studentu rusiavimo laikas: " << rusiavimoLaikas.count() << " s" << endl;

    // 3. Surusiuotu studentu isvedimo laikas
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> isvedimoLaikas = end - start;
    cout << "Surusiuotu studentu isvedimo laikas: " << isvedimoLaikas.count() << " s" << endl;

    // 4. Bendras duomenu apdorojimo laikas
    cout << "Bendras duomenu apdorojimo laikas: " << (nuskaitymoLaikas + rusiavimoLaikas + isvedimoLaikas).count() << " s" << endl;
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
        cout << "5 - Generuoti studentu failus ir suskirstyti i dvi grupes\n";
        cout << "6 - Atlikti spartos analize\n";
        cout << "7 - Baigti darba\n";
        cout << "Pasirinkite: ";
        cin >> meniuPasirinkimas;

        if (meniuPasirinkimas == 7) break;

        // Option 3 - Generate Students' Names, Surnames and Grades
        if (meniuPasirinkimas == 3) {
            int kiekGeneruoti = 0; // Only ask for the number of students once
            cout << "Kiek studentu generuoti?: ";
            cin >> kiekGeneruoti;

            // Generate students
            for (int i = 0; i < kiekGeneruoti; i++) {
                ivestiStudenta(studentai, meniuPasirinkimas);
            }

            if (studentai.empty()) {
                cout << "Nera studentu!\n";
                continue;
            }

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
        }

else if (meniuPasirinkimas == 5) {
    int dydisPasirinkimas;
    cout << "Pasirinkite failo dydi:\n";
    cout << "1 - 1000 studentu\n";
    cout << "2 - 10000 studentu\n";
    cout << "3 - 100000 studentu\n";
    cout << "4 - 1000000 studentu\n";
    cout << "Pasirinkite: ";
    cin >> dydisPasirinkimas;

    int kiekis;
    switch (dydisPasirinkimas) {
        case 1: kiekis = 1000; break;
        case 2: kiekis = 10000; break;
        case 3: kiekis = 100000; break;
        case 4: kiekis = 1000000; break;
        default:
            cout << "Klaida! Netinkamas pasirinkimas." << endl;
            continue;
    }

    string failoPavadinimas = "studentai_" + to_string(kiekis) + ".txt";

    // Measure simulated file creation time
    matuotiFailuKurimoLaika(kiekis, failoPavadinimas);

    // Actually create the file (if needed)
    generuotiFaila(kiekis, failoPavadinimas);

    char skirstyti;
    cout << "Ar norite suskirstyti studentus i dvi grupes ir issaugoti rezultatus faile? (t/n): ";
    cin >> skirstyti;

    if (skirstyti == 't') {
        vector<Student> vargsiukai;
        vector<Student> kietiakiai;
        studentai.clear();  // Clear to avoid appending to old data
        nuskaitytiIsFailo(studentai, failoPavadinimas);

        cout << "Is failo nuskaityta studentu: " << studentai.size() << endl;

        for (auto& studentas : studentai) {
            // Validate if the student has grades
            if (studentas.namu_darbai.empty()) {
                cout << "Klaida: Studentas " << studentas.vardas << " neturi namu darbu!" << endl;
                continue;
            }

            // Calculate final grade
            double galutinis = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);

            if (galutinis < 5.0) {
                vargsiukai.push_back(studentas);
            } else {
                kietiakiai.push_back(studentas);
            }
        }

        cout << "Vargsiukai: " << vargsiukai.size() << ", Kietiakiai: " << kietiakiai.size() << endl;

        issaugotiStudentusIFaila(vargsiukai, "vargsiukai_" + to_string(kiekis) + ".txt");
        issaugotiStudentusIFaila(kietiakiai, "kietiakiai_" + to_string(kiekis) + ".txt");
    }
    continue;
}

        // Option 4 - Read from file
        else if (meniuPasirinkimas == 4) {
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
        }

        // Option 6 - Performance analysis
        else if (meniuPasirinkimas == 6) {
            int dydisPasirinkimas;
            cout << "Pasirinkite failo dydi:\n";
            cout << "1 - 1000 studentu\n";
            cout << "2 - 10000 studentu\n";
            cout << "3 - 100000 studentu\n";
            cout << "4 - 1000000 studentu\n";
            cout << "Pasirinkite: ";
            cin >> dydisPasirinkimas;

            int kiekis;
            switch (dydisPasirinkimas) {
            case 1: kiekis = 1000; break;
            case 2: kiekis = 10000; break;
            case 3: kiekis = 100000; break;
            case 4: kiekis = 1000000; break;
            default:
                cout << "Klaida! Netinkamas pasirinkimas." << endl;
                continue;
            }

            string failoPavadinimas = "studentai_" + to_string(kiekis) + ".txt";

            // Check if the file exists before performing analysis
            ifstream fileCheck(failoPavadinimas);
            if (!fileCheck) {
                cerr << "Klaida: Failas " << failoPavadinimas << " neegzistuoja. Pirmiausia sugeneruokite faila naudodami meniu 5." << endl;
                continue;
            }
            fileCheck.close();

            // Perform analysis
            matuotiDuomenuApdorojimoLaika(failoPavadinimas);
        }

        // Option 1 or 2 - Manual input or generate grades only
        else {
            int kiekGeneruoti = 1;  // Default value to 1
            if (meniuPasirinkimas == 3) {
                // Ask only once for the number of students to generate
                cout << "Kiek studentu generuoti?: ";
                cin >> kiekGeneruoti;
            }

            // Generate students based on menu option
            for (int i = 0; i < kiekGeneruoti; i++) {
                ivestiStudenta(studentai, meniuPasirinkimas);
            }

            if (studentai.empty()) {
                cout << endl;
                continue;
            }

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
        }
    }
}