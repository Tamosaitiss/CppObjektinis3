**Studentų Duomenų Apdorojimo Testavimas (v1.0)
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
