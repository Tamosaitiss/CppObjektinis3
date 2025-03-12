#include "studentai.h"
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

double skaiciuotiVidurki(const std::vector<int>& pazymiai, int egzaminas) {
    if (pazymiai.empty()) return 0.0;

    double vidurkis = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0);
    vidurkis += egzaminas; // Include the exam grade in the total sum
    vidurkis /= (pazymiai.size() + 1); // Divide by the total number of grades (homework + exam)
    return vidurkis;
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

    for (int i = 0; i < kiekis; i++) {
        pazymiai.push_back(dist(gen));
    }
    return pazymiai;
}

int generuotiAtsitiktiniEgzaminoBala() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10); // Generate exam scores between 1 and 10
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
    ofstream failas(failoPavadinimas);

    if (!failas) {
        cerr << "Klaida kuriant failą: " << failoPavadinimas << std::endl;
        return;
    }

    failas << left << setw(10) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= 10; ++i) {
        failas << setw(5) << ("ND" + to_string(i));
    }
    failas << setw(10) << "Egzaminas" << "\n";

    for (int i = 1; i <= kiekis; ++i) {
        string vardas = "Vardas" + to_string(i);
        string pavarde = "Pavarde" + to_string(i);
        vector<int> namu_darbai = generuotiAtsitiktiniusPazymius(10);
        int egzaminas = generuotiAtsitiktiniEgzaminoBala();

        failas << left << setw(10) << vardas << setw(15) << pavarde;
        for (int pazymys : namu_darbai) {
            failas << setw(5) << pazymys;
        }
        failas << setw(10) << egzaminas << "\n";
    }

    failas.close();
    cout << "Failas sukurtas: " << failoPavadinimas << endl;
}

void generuotiFailus(const vector<int>& kiekiai) {
    for (int kiekis : kiekiai) {
        string failoPavadinimas = "studentai_" + to_string(kiekis) + ".txt";
        generuotiFaila(kiekis, failoPavadinimas);
    }
}

void suskirstytiStudentus(vector<Student>& studentai, vector<Student>& vargsiukai, vector<Student>& kietiakiai) {
    for (const auto& studentas : studentai) {
        double galutinisBalas = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);
        if (galutinisBalas < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            kietiakiai.push_back(studentas);
        }
    }
}

void issaugotiStudentusIFaila(const vector<Student>& studentai, const string& failoPavadinimas) {
    ofstream failas(failoPavadinimas.c_str());

    if (!failas) {
        cerr << "Klaida kuriant faila: " << failoPavadinimas << endl;
        return;
    }

    failas << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (Vid.)" << endl;

    for (const auto& studentas : studentai) {
        double galutinisBalas = skaiciuotiVidurki(studentas.namu_darbai, studentas.egzaminas);
        failas << left << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << fixed << setprecision(2) << galutinisBalas << endl;
    }

    failas.close();
    cout << "Studentai issaugoti faile: " << failoPavadinimas << endl;
}

void matuotiFailuKurimoLaika(int kiekis, const string& failoPavadinimas) {
    auto start = chrono::high_resolution_clock::now();
    generuotiFaila(kiekis, failoPavadinimas);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> trukme = end - start;
    cout << "Failo " << failoPavadinimas << " kurimo laikas: " << trukme.count() << " s" << endl;
}

void matuotiDuomenuApdorojimoLaika(const string& failoPavadinimas) {
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
    start = chrono::high_resolution_clock::now();
    issaugotiStudentusIFaila(vargsiukai, "vargsiukai.txt");
    issaugotiStudentusIFaila(kietiakiai, "kietiakiai.txt");
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

        if (meniuPasirinkimas == 5) {
            vector<int> kiekiai;
            int kiekis;
            cout << "Iveskite failu kiekius (iveskite -1 baigti): ";
            while (cin >> kiekis && kiekis != -1) {
                kiekiai.push_back(kiekis);
            }
            generuotiFailus(kiekiai);

            char skirstyti;
            cout << "Ar norite suskirstyti studentus i dvi grupes ir issaugoti rezultatus faile? (t/n): ";
            cin >> skirstyti;

            if (skirstyti == 't') {
                vector<Student> vargsiukai;
                vector<Student> kietiakiai;
                for (const auto& failoPavadinimas : kiekiai) {
                    string failas = "studentai_" + to_string(failoPavadinimas) + ".txt";
                    nuskaitytiIsFailo(studentai, failas);
                    suskirstytiStudentus(studentai, vargsiukai, kietiakiai);
                    issaugotiStudentusIFaila(vargsiukai, "vargsiukai_" + to_string(failoPavadinimas) + ".txt");
                    issaugotiStudentusIFaila(kietiakiai, "kietiakiai_" + to_string(failoPavadinimas) + ".txt");
                    vargsiukai.clear();
                    kietiakiai.clear();
                }
            }

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
        } else if (meniuPasirinkimas == 6) {
            int kiekis;
            string failoPavadinimas;
            cout << "Iveskite studentu skaiciu failui kurti: ";
            cin >> kiekis;
            failoPavadinimas = "studentai_test.txt";
            matuotiFailuKurimoLaika(kiekis, failoPavadinimas);
            matuotiDuomenuApdorojimoLaika(failoPavadinimas);

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