## Nauji pakeitimai `v1.5` versijoje

Šioje versijoje klasė `Studentas` buvo refaktorizuota pagal objektinio programavimo principus:

- Sukurta **abstrakti bazinė klasė `Zmogus`**, kuri apibrėžia bendrus metodus `vardas()` ir `pavarde()`.
- Klasė `Studentas` dabar **paveldi** `Zmogus` ir **realizuoja visus reikalingus metodus**.
- `Zmogus` negali būti instancijuojama (demonstracija pridėta testavimo kode).
- Išlaikytas **pilnas Rule of Five** įgyvendinimas:
  - Kopijavimo konstruktorius
  - Kopijavimo priskyrimo operatorius
  - Perkėlimo konstruktorius
  - Perkėlimo priskyrimo operatorius
  - Destruktorius
- Išlieka visos `v1.2` funkcijos ir testai veikia be pakeitimų.

---

## 🧱 Klasės struktūra

### Zmogus (abstrakti)
```cpp
class Zmogus {
public:
    virtual ~Zmogus() = default;
    virtual string vardas() const = 0;
    virtual string pavarde() const = 0;
};
```

### Studentas (paveldėta)
```cpp
class Studentas : public Zmogus {
    // paveldėjimas, papildomi metodai ir Rule of Five
};
```

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
![Vector](https://github.com/user-attachments/assets/5b3a3eb7-cddc-4401-95ab-6644ab71713a)

### List versija:
![List](https://github.com/user-attachments/assets/92afe394-b512-4bf0-b400-87c4bc84b6dd)

### Deque versija:
![Deque](https://github.com/user-attachments/assets/16641568-d16d-41fa-afe3-d4af4a5413dd)

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

### Testavime tikrinama:
- Visi `Rule of Five` metodai: konstruktoriai, priskyrimai, destruktorius.
- Veikiantys operatoriai `>>` ir `<<`.
- Skaičiavimas `galutinisVidurkis()`.
- - Demonstracija, kad `Zmogus` objektų sukurti neįmanoma (komentuota eilutė):

```cpp
// Zmogus z; // tai būtų klaida: negalima kurti abstrakčios klasės objekto
```

---

## Failai

- `zmogus.h` – abstrakti bazinė klasė
- `studentas.h`, `studentai.cpp` – `Studentas` klasė ir metodai
- `test.cpp` – testavimo failas
- `vector_versija.cpp`, `list_versija.cpp`, `deque_versija.cpp` – konteinerių strategijų palyginimai
