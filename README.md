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

**Konteineris	Failo dydis	Nuskaitymo laikas (s) Rūšiavimo laikas (s) Skirstymo laikas (s)**
std::vector	1000	      0.000988	            0.000017	             0.0001623
            10,000	   0.0088772	         0.0015587	          0.0009355
            100,000	   0.0788088	         0.0173394	          0.0074201
            1,000,000	0.673929	            0.225253	             0.0804325
std::list	1000	      0.0010048	         0.0001545	          0.0001307
            10,000	   0.0080566	         0.0007065	          0.0009017
            100,000	   0.081352	            0.007855	             0.0085647
            1,000,000	0.695045	            0.0975908	          0.0904832
std::deque	1000	      0.0010414	         0.0001276	          0.0006452
            10,000	   0.0080305	         0.0015489	          0.0007036
            100,000	   0.0776795	         0.0214414	          0.0064133
            1,000,000	0.667129	            0.282987	             0.0608517

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
