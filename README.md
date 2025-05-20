# CppObjektinis2 – v2.0

## ✅ Versijų istorija

### `v1.5` – Pagrindinis objektinis pertvarkymas
- Sukurta **abstrakti bazinė klasė `Zmogus`**, kurios negalima instancijuoti.
- Klasė `Studentas` paveldi `Zmogus` ir realizuoja visus metodus.
- Įgyvendinta **Rule of Five**: kopijavimo/perkėlimo konstruktoriai, priskyrimai ir destruktorius.
- Palaikomas operatorių `>>`, `<<` veikimas.
- Studentai failuose išrikiuoti pagal **galutinį vidurkį** (didėjimo tvarka).

### `v2.0` – Dokumentacija + Testavimas
- Sukurta dokumentacija naudojant **Doxygen**:
  - `docs/html/` – HTML dokumentacija
  - `docs/latex/` – LaTeX šaltiniai
  - `docs/latex/latex.pdf` – Sugeneruota PDF dokumentacija
- Realizuoti **Unit testai su Catch2**:
  - Tikrinami visi `Rule of Five` metodai
  - Testuojami `galutinisVidurkis`, `galutinisMediana`, operatoriai `>>` ir `<<`
- Paruoštas **`CMakeLists.txt`** – universalus (visoms OS)
- Repozitorija išvalyta nuo IDE šiukšlių, struktūra švari

---

## 🧪 Unit testai (Catch2)

Testuojami metodai:

- `Studentas(const Studentas&)` – kopijavimo konstruktorius
- `Studentas& operator=(const Studentas&)` – kopijavimo priskyrimas
- `Studentas(Studentas&&)` – perkėlimo konstruktorius
- `Studentas& operator=(Studentas&&)` – perkėlimo priskyrimas
- `~Studentas()` – destruktorius
- `galutinisVidurkis()` ir `galutinisMediana()`
- `operator>>` ir `operator<<`

```bash
# Paleidimas:
mkdir build && cd build
cmake ..
make tests
./tests
```

---

## 📸 Veikimo laikų palyginimas

| Konteineris | Strategija | 10k      | 100k     | 1M       |
|-------------|------------|----------|----------|----------|
| vector      | 1          | 0.000860 | 0.006967 | 0.078577 |
|             | 2          | 0.000511 | 0.004362 | 0.045950 |
|             | 3          | 0.000264 | 0.003232 | 0.037041 |

---

## 📝 Naudojimosi instrukcija

1. Paleisk `vector_versija` programą:

```bash
./vector_version
```

2. Ji perskaitys pasirinktus failus (pvz. `studentai10000.txt`) ir sukurs:

- `vector_vargsiukaiX.txt`
- `vector_kietiakiaiX.txt`

Failai bus išrikiuoti pagal galutinį balą nuo mažiausio iki didžiausio.

---

## ⚙️ Įdiegimo instrukcija

1. Klonuoti repozitoriją:

```bash
git clone https://github.com/Tamosaitiss/CppObjektinis2.git
cd CppObjektinis2
```

2. Sukurti `build/` katalogą ir sukompiliuoti:

```bash
mkdir build
cd build
cmake ..
make
```

3. Paleisti programą arba testus:

```bash
./vector_version
./tests
```

---

## 📁 Projekto struktūra

```
CppObjektinis2/
├── common/              ← studentai.cpp, studentas.h, zmogus.h
├── Vektoriu_versija/    ← vector_versija.cpp
├── tests/               ← test_studentas.cpp (Catch2)
├── external/catch2/     ← catch.hpp
├── docs/                ← Doxygen dokumentacija (html + latex)
├── CMakeLists.txt       ← Build sistema
```

---

## 📚 Doxygen dokumentacija

- Doxygen failas: `Doxyfile`
- Sugeneruoti formatai:
  - HTML: `docs/html/index.html`
  - PDF: `docs/latex/latex.pdf`
  - LaTeX: `docs/latex/`

---

## 🧹 Švari struktūra

- `.idea/`, `cmake-build-*/`, `*.o`, `*.exe` ir kiti IDE failai **neįtraukti į repozitoriją**
- `.gitignore` prižiūri tvarką

---

## 📌 Autorius

- Tamosaitiss @ GitHub
- Vilniaus universitetas, 2025 m.
