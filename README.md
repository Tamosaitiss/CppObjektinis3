**Studentų Duomenų Apdorojimo Testavimas (v1.0.0 pradinė)
Čia aprašyta studentų duomenų nuskaitymo, rūšiavimo ir skirstymo į dvi grupes (vargsiukai, kietiakiai) našumo testavimas naudojant skirtingus konteinerius (std::vector, std::list, std::deque)**


**Kompiuterio specifikacija atliekant testavimus:**
**Procesorius**: (CPU)	Intel Core i9-14900K
**Operatyvioji atmintis (RAM)**:	64 GB DDR5 (Kingston FURY Beast)
**Diskas (SSD)**:	Samsung 990 PRO 1TB (NVMe)
**OS**: Windows 11 Pro 64-bit
**Kompiliatorius**:	GCC


**Testavimo rezultatai (v1.0)**
**Testavimas atliekamas su std::vector, std::list ir std::deque
Kiekvienas konteineris testuojamas su visais failų dydžiais**

![image](https://github.com/user-attachments/assets/aca19f37-1b2e-4b0e-acbc-756175435921)

**Analizė ir išvados**

**1️. Rūšiavimas (sort())**
std::vector yra greičiausias didelėms duomenų aibėms
std::list yra lėtesnis rūšiuojant, bet efektyvus įterpiant ir šalinant elementus
std::deque prasčiau veikia su didelėmis duomenų aibėmis, rūšiuojant jis lėčiausias

**2️. Skirstymas (std::partition)**
std::deque pasirodė geriausiai dėl dvipusio įterpimo
std::list veikia stabiliai, bet yra kiek lėtesnis nei std::deque
std::vector yra lėčiausias skirstant, nes reikalingi perstumdymai atmintyje

**3️. Bendras našumas**
Jei reikia greito rūšiavimo → naudoti std::vector
Jei reikia dažnų įterpimų ir trynimų → naudoti std::list
Jei reikia greito skirstymo → naudoti std::deque

##**v1.0.1 final release**

Ši `v1.0` versija įgyvendina **trijų skirtingų studentų skirstymo strategijų** palyginimą naudojant **trijų tipų konteinerius**:  
- `std::vector`
- `std::list`
- `std::deque`

Kiekvienai strategijai buvo išmatuotas veikimo laikas su skirtingo dydžio studentų failais.

---

##**Testavimo rezultatai**

**Failo dydis: 1000 studentų**

| Strategija | `vector` (s) | `list` (s) | `deque` (s) |
|------------|------------|------------|------------|
| **1 strategija** | 0.0001467 | 0.0000908 | 0.0000762 |
| **2 strategija** | 0.0001064 | 0.0000548 | 0.0000513 |
| **3 strategija** | 0.0000421 | 0.0000374 | 0.0000481 |

---

**Failo dydis: 10 000 studentų**

| Strategija | `vector` (s) | `list` (s) | `deque` (s) |
|------------|------------|------------|------------|
| **1 strategija** | 0.0009502 | 0.0009596 | 0.0006457 |
| **2 strategija** | 0.0008376 | 0.0008483 | 0.0006426 |
| **3 strategija** | 0.0008296 | 0.0008406 | 0.0006353 |

---

**Failo dydis: 100 000 studentų**

| Strategija | `vector` (s) | `list` (s) | `deque` (s) |
|------------|------------|------------|------------|
| **1 strategija** | 0.0069682 | 0.008217 | 0.0062123 |
| **2 strategija** | 0.0048604 | 0.006032 | 0.0042192 |
| **3 strategija** | 0.0040873 | 0.005632 | 0.0047136 |

---

**Failo dydis: 1 000 000 studentų**

| Strategija | `vector` (s) | `list` (s) | `deque` (s) |
|------------|------------|------------|------------|
| **1 strategija** | 0.0805227 | 0.0912095 | 0.059769 |
| **2 strategija** | 0.0473973 | 0.0715186 | 0.0455487 |
| **3 strategija** | 0.0398828 | 0.0780245 | 0.0356733 |

---

##**Išvados**
- **3 strategija (`std::partition`) buvo greičiausia** visuose testuose.
- **`std::deque` veikė greičiausiai su dideliais failais** (ypač 1 000 000 įrašų).
- **`std::list` buvo lėčiausias pasirinkimas** beveik visais atvejais, nes dažni trynimai nėra efektyvūs.
- **Didėjant studentų kiekiui, veikimo laikas didėja eksponentiškai**, bet strategijos pasirinkimas turi didelę įtaką.

---

##**Kaip paleisti**
1. **Kompiliavimas naudojant `CMake`**
   ```sh
   mkdir build
   cd build
   cmake ..
   make

**Tai sugeneruos tris vykdomuosius failus:** 
-- vector_version
-- list_version
-- deque_version

**Po sėkmingo kompiliavimo, galite paleisti bet kurią versiją:**
./vector_version   # Vektorių versija
./list_version     # Sąrašų (list) versija
./deque_version    # Deque versija

**Naudojimosi instrukcija:**
**Programa automatiškai testuoja 4 skirtingus failų dydžius:**
- studentai1000.txt
- studentai10000.txt
- studentai100000.txt
- studentai1000000.txt

**Kiekvienam failui išbandomos 3 strategijos:**
**1 strategija:** Kopijuojami studentai į du naujus konteinerius.
**2 strategija:** Sukuriamas tik vargšiukų sąrašas, o kietiakiai lieka pirminiame konteineryje.
**3 strategija:** Optimizuotas skirstymas naudojant std::partition.

**Rezultatai išsaugomi į failus:**
- vargsiukai_<dydis>_strategijaX_<konteineris>.txt
- kietiakiai_<dydis>_strategijaX_<konteineris>.txt

---

**## Struct ir Class studentų palyginimas (3 strategija)**

Naudotas konteineris: `std::vector`  
Naudota strategija: 3 strategija (`std::partition`)  
Failai: `studentai100000.txt` ir `studentai1000000.txt`

| Failas              | Struktūra (struct) | Klasė (class) |
|---------------------|--------------------|---------------|
| studentai100000.txt | 0.0040873 s        | 0.003692 s    |
| studentai1000000.txt| 0.0398828 s        | 0.037380 s    |

**Išvada:**  
Klasės versija yra šiek tiek greitesnė už struktūrinę. Skirtumas nedidelis, tačiau klasė leidžia lengviau plėsti funkcionalumą, todėl ji tinkamesnė didesnėms sistemoms.

---

## Kompiliatoriaus optimizavimo flag'ų įtaka

Testuota naudojant:  
- `class` versiją  
- `std::vector` konteinerį  
- 3 strategiją (`std::partition`)  

| Flag'as | studentai100000.txt | studentai1000000.txt |
|--------|----------------------|----------------------|
| -O0    | 0.005663 s           | 0.054703 s           |
| -O1    | 0.004873 s           | 0.039828 s           |
| -O2    | 0.0040873 s          | 0.0398828 s          |
| -O3    | 0.003692 s           | 0.037380 s           |

**Išvada:**  
Programos veikimo sparta labai priklauso nuo kompiliatoriaus optimizavimo lygio. Aukštesnis optimizavimo lygis (ypač `-O3`) ženkliai pagerina veikimo laiką, ypač su dideliais duomenų kiekiais.

---


