# Studentų Valdymo Sistema – Versija 3.0

## 🧠 Aprašymas

Galutinė (v3.0) C++ projektinė versija su nuosava `Vector` klase vietoje `std::vector`. Ši versija apima:

- Visišką `Vector` integraciją į programą.
- Instaliacinį `setup.exe` failą be `admin` teisių.
- Strategijų testavimo sistemą.
- Rule of Five testus.
- Vartotojo sąsajos meniu.
- Vienetinius testus ir Doxygen dokumentaciją.

---

## ✅ Funkcijos

- Nuosava `Vector` klasė.
- 3 studentų skirstymo strategijos.
- Rule of Five + I/O operatorių testavimas.
- Greičio analizė (vektorius vs std::vector).
- `Catch2` unit testai.
- Sugeneruota dokumentacija su Doxygen.
- Sukurtas `setup.exe` diegimo failas.

---

## 📦 Diegimo instrukcija

1. Paleiskite `setup.exe` failą.
2. Pasirinkite diegimo vietą (rekomenduojama: `C:\StudentuSistema`).
3. Baigus diegimą, paleiskite „Studentu Sistema“ per Start meniu arba `vector_version.exe`.

---

## 🧑‍💻 Naudojimosi instrukcija

Paleidus programą, rodoma meniu:

====== STUDENTU SISTEMA ======
1 - Testuoti strategijas (1, 2, 3)
2 - Vykdyti tik Rule of Five testą
3 - Vykdyti strategijas + Rule of Five testą
4 - Išeiti
Pasirinkimas: _


Failai turi būti tame pačiame kataloge kaip ir `.exe`.

---

## 📊 Spartos analizė

Palyginta `std::vector` ir `Vector` užpildymo sparta su `push_back()`:

| Elementų kiekis | std::vector (s) | Vector (s) |
|------------------|------------------|------------|
| 10,000           | 0.00193          | 0.00084    |
| 100,000          | 0.01694          | 0.00741    |
| 1,000,000        | 0.17904          | 0.09541    |

---

## 🧪 Unit testai

Sukurti `Catch2` testai `Vector` klasei:

- Konstrukcijos, destrukcija, `push_back`, `at`, `insert`, `erase`, `move`, `copy`, `front`, `back`, `resize`, `clear`.
- `std::out_of_range` tikrinimas su `at()`.
- Iteratorių palaikymas.

---

## 📚 Dokumentacija

- Sugeneruota su `Doxygen`.
- Galima rasti kataloge `docs/`:
  - `docs/html/index.html`
  - `docs/latex/refman.pdf`

---

## 📁 Projekto struktūra

CppObjektinis3/
│
├── Vektoriu_versija/
│ └── vector_versija.cpp
├── common/
│ ├── studentai.cpp
│ ├── studentas.h
│ ├── Vector.h
│ └── Vector.tpp
├── tests/
│ ├── test_vector.cpp
│ ├── test_studentas.cpp
│ ├── bench_pushback.cpp
│ └── bench_rollback.cpp
├── docs/
│ ├── html/
│ └── latex/latex_7.pdf
├── studentai10000.txt
├── studentai100000.txt
├── CMakeLists.txt
└── setup.exe


---

## 📌 Versijos istorija

- `v1.0` – Strategijų palyginimas su STL konteineriais.
- `v2.0` – Rule of Five, unit testai, Doxygen dokumentacija.
- `v3.0` – Savarankiškas `Vector`, veikimo analizė, `setup.exe`.

---

## ℹ️ Pastabos

Programa neišsaugos failų į `Program Files`, jei neturite rašymo teisių. Rekomenduojama diegti į kitą katalogą (pvz. `C:\StudentuSistema`).

---

[Setup]
AppName=Studentu Sistema
AppVersion=3.0
DefaultDirName={pf}\StudentuSistema
DefaultGroupName=Studentu Sistema
OutputBaseFilename=setup
PrivilegesRequired=lowest
DisableWelcomePage=no

[Files]
Source: "cmake-build-release\vector_version.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "studentai10000.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "studentai100000.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "README.md"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Paleisti programą"; Filename: "{app}\vector_version.exe"
