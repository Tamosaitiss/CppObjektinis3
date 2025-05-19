
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
- **Rūšiavimas pagal galutinį vidurkį:** studentai failuose `vargsiukai` ir `kietiakiai` yra išrikiuojami **nuo mažiausio iki didžiausio** galutinio balo.

---

## Klasės struktūra

### Zmogus (abstrakti)
```cpp
class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    virtual ~Zmogus() = default;
    std::string vardas() const;
    std::string pavarde() const;
    virtual std::ostream& spausdinti(std::ostream& os) const = 0;
};
```

### Studentas (paveldėta)
```cpp
class Studentas : public Zmogus {
private:
    std::vector<int> nd_;
    int egzaminas_;
    // ...

public:
    // Rule of Five, paveldėti metodai, galutiniai skaičiavimai
};
```

---

## Veikimo laikų palyginimo lentelė (s)

| Konteineris | Strategija | 10k      | 100k     | 1M       |
|-------------|------------|----------|----------|----------|
| **vector**  | 1          | 0.000860 | 0.006967 | 0.078577 |
|             | 2          | 0.000511 | 0.004362 | 0.045950 |
|             | 3          | 0.000264 | 0.003232 | 0.037041 |

---

## Output nuotraukos

### Vector versija:
![Vector](https://github.com/user-attachments/assets/30f40a68-cbd1-430e-ad77-72aadc0519d1)

---

## Perdengti metodai

### Operatorius `>>`
- Skaito studento duomenis iš `std::istream`.
- Leidžia įvesti iš failo, `std::cin` arba `stringstream`.
- Paskutinis įrašytas pažymys laikomas egzaminu.

### Operatorius `<<`
- Išveda studento duomenis (vardas, pavardė, galutinis balas) lygiuotai į `std::ostream`.
- Naudojamas išvedimui į ekraną arba į failą.

---

### Testavime tikrinama:
- Visi `Rule of Five` metodai: konstruktoriai, priskyrimai, destruktorius.
- Veikiantys operatoriai `>>` ir `<<`.
- Skaičiavimas `galutinisVidurkis()`.
- Demonstracija, kad `Zmogus` objektų sukurti neįmanoma (komentuota eilutė):

```cpp
// Zmogus z; // tai būtų klaida: negalima kurti abstrakčios klasės objekto
```

---

## Failai

- `zmogus.h` – abstrakti bazinė klasė
- `studentas.h`, `studentai.cpp` – `Studentas` klasės ir metodai
- `vector_versija.cpp` – konteinerių strategijų palyginimai ir testavimai
