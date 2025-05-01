# Studentų rūšiavimo našumo analizė

## Projekto versija `v1.2`

Šiame projekte įgyvendintos trys studentų rūšiavimo strategijos naudojant skirtingus konteinerius:
- `std::vector`
- `std::list`
- `std::deque`

Visuose konteineriuose ištestuotos trys strategijos:
1. Kopijavimas į du atskirus konteinerius (`skirstymas_1`)
2. Perkėlimas "vargšiukų" į kitą konteinerį su `remove_if` (`skirstymas_2`)
3. Naudojamas `std::partition` (`skirstymas_3`)

---

## Veikimo laikų palyginimo lentelė (s)

| Konteineris | Strategija | 10k      | 100k     | 1M       |
|-------------|------------|----------|----------|----------|
| **vector**  | 1          | 0.000860 | 0.006967 | 0.078577 |
|             | 2          | 0.000511 | 0.004362 | 0.045950 |
|             | 3          | 0.000264 | 0.003232 | 0.037041 |
| **list**    | 1          | 0.001615 | 0.009874 | 0.090729 |
|             | 2          | 0.000547 | 0.006337 | 0.084468 |
|             | 3          | 0.000775 | 0.006130 | 0.083669 |
| **deque**   | 1          | 0.000662 | 0.006473 | 0.061961 |
|             | 2          | 0.000473 | 0.004174 | 0.049353 |
|             | 3          | 0.000377 | 0.003596 | 0.050791 |

---

## Ekrano nuotraukos

### Vector versija:
![Vector](./734686f4-5f2b-420c-8fdf-e1ec17c4ea28.png)

### List versija:
![List](./37e4f292-715e-4d32-afa8-aa674754fe0c.png)

### Deque versija:
![Deque](./9740431f-c023-4e84-b0bd-f7b3235ef266.png)

---

## Perdengti metodai

### Operatorius `>>`
- Skaito studento duomenis iš `std::istream`.
- Leidžia įvesti iš failo, `std::cin` arba `stringstream`.
- Paskutinis įrašytas pažymys laikomas egzaminu.

### Operatorius `<<`
- Išveda studento duomenis (vardas, pavardė, galutinis balas) lygiuotai į `std::ostream`.
- Naudojamas išvedimui į ekraną arba į failą.

### Naudojimo scenarijai:
- Įvedimas:
  - Rankiniu būdu: `std::cin >> studentas`
  - Iš failo: `nuskaitytiIsFailo(...)`
  - Automatiniu būdu: `stringstream >> studentas`
- Išvedimas:
  - Į ekraną: `std::cout << studentas`
  - Į failą: `issaugotiStudentusIFaila(...)`

---

## Testavimas

```bash
make test
./test
```

### Tikrinama:
- Visi `Rule of Five` metodai: konstruktoriai, priskyrimai, destruktorius.
- Veikiantys operatoriai `>>` ir `<<`.
- Skaičiavimas `galutinisVidurkis()`.

---

## Failai

- `studentas.h`, `studentai.cpp` – klasė ir metodai
- `vector_versija.cpp`, `list_versija.cpp`, `deque_versija.cpp` – strategijų palyginimas
- `main versiju .cpp` – Rule of Five ir operatorių testai
- `README.md` – dokumentacija
