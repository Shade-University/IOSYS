# Vypis

## 1) **Definice OS: typy OS; design OS: abstrakce a operace nad nimi – služby, systémová volání**

### **a) Dvě základní funkce OS (s vysvětlením) 2**

Rozšíření stroje (virtualizace) - pohled shora  

* Zjednodušující interface, abstrakce  
* Příklad: čtení/zápis na disk

Správa prostředků - pohled zdola  

* Procesy, paměti, V/V zařízení  
* Příklad: tisk na tiskárně
* Multiplexing - sdílenení prostředků v čase (CPU) a v prostoru (RAM)

### **b) Vlastnosti moderního OS 4**

* Preemptivní a efektivní plánování procesů  
* Izolace procesů  
* Efektivní správa paměti
 * Operační pamět - logické adresování, virtualizace
 * Úložiště - souborové systémy 
* Izolace uživatelů, víceuživatelský OS
 * Implementace oprávnění
* Podpora IPC - komunikace a synchronizace

### **c) Typy OS (alespoň šest) 3**

* Mainframe OS - sálové počítače 
* Serverové OS
* Vícepočítačové OS - Clustery  
* Osobní OS - PC
* Realtime OS
* Vestavěné (embedded) OS
* Smart Cart OS

### **d) Reprezentace abstrakcí (koncepcí) v OS a definice systémového volání 2**

Systémové volání - je mechanismus sloužící k volání funkcí operačního systému.  

### **e) Průběh systémového volání 3**

* Uložení parametrů na stack  
* Volání systémové funkce v knihovně  
* Knihovna nastaví registr na typ volání  
* TRAP - skok do jádra  
* Jádro zavolá příslušný ovladač  
* Návrat do knihovny a programu

### **f) Příklady systémových volání a co obstarvají (alespoň tři) 1**

Pro procesy  

* Vznik, nahrazení, čekání na ukončení, ukončení  

Soubory (na V/V)

* Otevření zavření, čtení, zápis

Adresáře a souborové systémy  

* Vytvoření, zrušení, odkazy, připojení FS

Ostatní (práva, signály)

* Změna práv, signál, zjištění času

## 2) **Architektura jádra OS: monolitický systém, vrstvený systém, virtualizace na úrovni jádra OS, mikrojádro**

### **a) Definice monolitického jádra OS 2**

Je to vnitřně nečleněné jádro - všechno běží v jednom paměťovém prostoru  

* Jádro má všechny potřebné funkce (procedury) - Každá funkce může volat libovolnou jinou

### **b) Definice vrstveného jádra OS a čím se liší od monolitického s vnitřní strukturou vrstev 2**

Jádro, které smí volat procedury stejné nebo nejbližší nižší vrstvy. Je rozděleno na oddělené vrstvy  
Vrstva smí volat jen procedury stejné nebo nejbližší nižší vrstvy (rozdíl od monolitického)

### **c) Definice mikrojádra OS a které funkce zajišťuje 3**

Velmi malé jádro, které obsahuje jen nejzákladnější funkce.  
Je trendem moderních systémů - snaží se být co nejjednodušší (zvyšuje přehlednost v kódu, snižuje riziko chyb programátora)  

* Mikroprogramování
* Zajištění ochrany paměti  
* Základní meziprocesová komunikace

### **d) Jak jsou v OS s mikrojádrem zajištěny ostatní funkcionality (které nejsouv mikrojádru) 2**

Jsou řešeny v uživatelském prostoru jako běžné procesy.

### **e) Definice virtualizace na úrovni jádra OS s příkladem 3**

Jedná se o virtuální stroje, které vytváří virtualizované prostřední mezi hw/sw a operačním systémem.  

* Virtualizované jádro operačního systému izoluje samostatná prostředí (skupiny procesů) s vlastním administrátorem, přičemž jádro běží pouze jedenkrát
Kontejnery

* Solaris, FreeBSD, Linux Containers

### **f) Příklady OS různých architektur jádra (monolitické, vrstvené, mikrojádro) 3**

Monolitické

* Windows, MacOS, Linux  

Vrstvené

* Multics

Mikrojádro

* Minix

## 3) **Návrh OS a jeho bezpečnost: důvody náročnosti implementace OS, principy jeho vývoje; zabezpečení systému, uživatelských dat a procesů (vyjma útoků na systém, to je jiný okruh)**

### **a) Hlavní obecné cíle návrhu OS 4**

* Definování abstrakcí (procesů, souborů..)
* Poskytnutí základních operací (operace jsou přístupné skrze systémové volání)
* Zajištění izolace
* Správa HW

### **b) Důvody náročnosti návrhu OS 5**

* Rozsáhlost, komplexnost, složitost
* Konkurence - Procesy soupeří o prostředky (kritické sekce)
* Ochrana - izolace procesů a oprávnění
* Sdílení dat a prostředků
* Životnost
* Obecnost použití - škálovatelnost použití
* Přenositelnost
* Kompatibilita

### **c) Principy vývoje OS 3**

* Jednoduchost - KISS (Keep it simple)
* Úplnost - Os by měla dělat to co má, ale nic navíc
* Efektivita - neefektivní vlastnost nemá cenu implementovat.

### **d) Způsoby zabezpečení procesů, dat na médiu a přenášených dat 3**

Zabezpečení procesů

* Domény ochrany - Stanovení domén a práv
* ACL - Access Control List - Stanovení práv nad objekty pro uživatele
* Capability - C-List - stanovení práv procesům
* Firewally

Zabezpečení dat na médiu

* Přístupová práva

Zabezpečení přenášených dat

* Šifrování

## 4) **CPU: provádění instrukce, pipeline, atomicita a přerušitelnost procesu a průběhu zpracování instrukce, přerušovací systém, průběh zpracování přerušení, časovač, sdílení času**

### **a) Popis fází provádění instrukce 4**

* FETCH - Načtení instrukce
* DECODE - Dekódování instrukce
* EXECUTE - Provedení instrukce
* WRITE - Zápis výsledků

### **b) Definice pipeline a další možnosti zvyšování výkonu CPU 4**

Pipeline je způsob zvýšení výkonu pomocí rozdělení instrukcí na nezávislé kroky

* Spekulativní provádění instrukcí
* Hyperthreading
* Více jader
* Paralelizace instrukcí

### **c) Přerušitelnost procesu, průběhu zpracování instrukce 2**

k přerušení procesu může dojít pouze na hranicích instrukcí

### **d) Přerušovací systém: účel, průběh přerušení 5**

ŮČel: Umožňuje efektivní využití CPU

Průběh:

* Dokončení rozpracované instrukce
* Skok na obslužnou rutinu přerušení
* Uložení kontextu
* Obsluha přerušení
* Návrat do procesu

## 5) **Vstupně-výstupní zařízení: ovladače a techniky programování vstupu a výstupu, DMA. Paměť cache, procesorová cache a střední přístupová doba do paměti**

### **a) Metoda 1 komunikace se vstupně-výstupním zařízením (neefektivní) 2**

Přístup pomocí instrukcí CPU.  

* Zápis
* Čtení (kontrola)
* Pokračování

### **b) Metoda 2 komunikace se vstupně-výstupním zařízením (efektivnější) 2**

Přístup pomocí instrukcí CPU s využitím přerušení.  

* Zápis
* Prováděění jiných operací
* Po dokončení přerušovací signál, který přeruší provádění jiných operací a může pokračovat v zápisu.

### **c) Metoda 3 komunikace se vstupně-výstupním zařízením (nejefektivnější) 3**

Direct Memory Access (DMA) s využitím prerušení.

* Zápis
* Provádění jiných operací
* Po dokončení přerušovací signál, který přeruší jiné operaci a přenos je dokončen

### **d) Definice paměti cache 2**

Jedná se o velmi rychlou pamět (mezipaměť) procesoru

### **e) Důvod existence konceptu paměti cache 1**

Pamět RAM je pomalá (a drahá) a brzdí CPU - proto má každý CPU svou paměť cache.

### **f) Důvod efektivity používání cache 2**

Princip lokality odkazů.

* Proces má tendenci přistupovat ke stejné části paměti jako v předcházejícím čase

### **g) Výpočet střední přístupové doby do paměti 3**

Ts = Tc + (1 − HR) ∙ Top(Tc ≪ Top)

* Tc - přístupová doba do paměti cache
* Top - přístupová doba do paměti

## 6) **Požadavky OS na HW nutný pro jeho implementaci: zejména na procesor, správu a adresování paměti. Registry CPU**

### **a) Nutné vlastnosti CPU a paměti pro implementaci OS a jejich účel 2 + 3**

Požadavky na procesor

* Řadič nebo řídící jednotka - načítání, dekódování, ukládání
* Sada registrů - uchování mezivýsledků
* Aritmeticko-logická jednotka - logické operace
* Cache - zrychlení

Požadavky na pamět

* Uvolňování - když už není potřeba
* Ochrana - proces nesmí odkazovat na místa přidělená jiným procesům
* Správa adresace -odkazy na pamět se musí dynamicky překládat na fyzické adresy
* Logická organizace - práce se sekcemi
* Sdílení paměti - více procesů může sdílet dané úseky bez narušení ochrany

### **b) Nutné subsystémy HW pro implementaci OS (kromě CPU a paměti) a jejich účel 2 + 2**

* Přerušovací systém - efektivní využití CPU (nutné pro DMA)
* Časovač - generuje přerušení
* Režim kernel a user - ochrana paměti
* Virtualizace paměti - logické adresování

### **c) Definice registrů CPU, jejich druhy 1 + 2**

Registr je malé úložště dat, které využívá procesor.

* Obecné
* Datové
* Adresní
* Privátní

### **d) Stavový registr CPU a zahrnuté příznaky (alespoň tři) 3**

Speciální registr procesoru.

* C - carry
* N - negative
* Z - zero
* V - overflow

## 7) **Implementace procesu v OS: proces a program, tabulka procesů, přepínání kontextu, stav procesu, třístavový model, příčiny změn stavů**

### **a) Proces a program: definice 2**

Program - postup operací, který popisuje realizaci dané úlohy  
Proces - Instance programu v paměti

### **b) Metadata procesu (alespoň šest) 3**

* Záznam o jeho identifikaci
* Záznam o jeho atributech
* Záznam o jeho stavu
* Záznám o jeho alokovaných zdrojích
* Otevřené soubory
* Sockety

### **c) Průběh přepnutí kontextu 3**

Uložení kontextu (Obvykle do PCB)  
Kód je vykonáván dokud nedojde k přerušovacímu signálu (HW - časovač)  
Přeskočení na obslužnou rutinu (do jádra OS - plánovač)  
Uložení kontextu  
Obsluha ovladače v jádře  
Plánovač rozhoduje, který proces poběží

### **d) Třístavový model: popis stavů 3**

* Běžící - aktuálně používá CPU
* Připravený - pozastaven jádrem CPU
* Blokovaný - čekající na vnější událost

### **e) Třístavový model: příčiny přechodů mezi stavy 4**

* Nedostatek paměti
* Preempce
* Aktivace plánovačem
* Nastala událost

## 8) **Procesy v OS UNIX/Linux: vznik a zánik procesu, systémová volání fork(2), exec(3), exit(3), wait(2), kill(2); hierarchie procesů, stavy procesů v Linuxu (podle příkazu ps); posixové signály a jejich zpracování**

### **a) Příčiny vzniku procesu a spuštění nového programu v posixových systémech, související systémová volání, hierarchie procesů 4**

Původcem je jádro - při inicializaci systému (první proces je init)  
růvodcem je proces - systémové volání  
Původcem je systémová volání - fork, exec

### **b) Příčiny zániku procesu a čekání na potomka v posixových systémech, související systémová volání 4**

Dobrovolné ukončení - chybný vstup či úloha dokončena  
Nedobrovolné ukončení - fatální chyba (neošetřená)  
Systémová volání - wait, exit, kill

### **c) Stavy procesů v Linuxu 4**

R - připravený  
S - blokovaný  
Z - ukončený  
T - pozastavený  
D - nepřerušitelný

### **d) Posixové signály, možnosti jejich zpracování a příklady 3**

Jednoduché zprávy procesům, které jsou zpracovány jádrem  
Implicitně jsou posílány jádrem OS při určitých událostech, explicitně se posílají příkazem  
Jsou zpracovány typicky jako ukončení procesu, pozastavení procesu. pokračování pozastaveného procesu

* SIGINT - exit - ukončení (ctrl+c)
* SIGSTP - stop - pozastavení (ctrl+z)
* SIGCONT - resume - pokračování
* SIGQUIT - core - ukončení

## 9) **Vlákna: motivace zavedení vláken, proces × vlákno, možné implementace vláken, obecné problémy při implementaci a používání vláken; knihovna posixových vláken: mutex, bariéra, podmínková proměnná a jejich použití**

### **a) Motivace zavedení vláken 1**

Zvýšení výkonu a zjednodušení programování

### **b) Společné a samostatné položky metadat procesů/vláken 3**

Samostatnené

* program counter a registry  
* stav vlákna  
* stack  

Společné

* Adresní prostor
* Prostředky
* Nástroje IPC
* ENvironment
* Pracovní adresář

### **c) Důvody vyhrazené části paměti pro každé vlákno 2**

Jednodušší správa  
přístup ke sdíleným prostředkům (globální proměnné)

### **d) Implementace vláken s podporou OS a bez ní, výhody a nevýhody 4**

S podporou OS

* Vzdálená volání - více režije
* Není třeba neblokujících volání

Výhody: není třeba neblokující volání, lze provádět i vlákno procesu, jehož vlákno způsobilo page-fault  
Nevýhody: Horší režije, pevná strategie vláken

Bez podpory OS

* Pomocí knihovních funkcí

Výhody: Lepší režie, strategie plánovače se dá prizpůsobit  
Nevýhody: Složitá implementace, page-fault zastaví všechna vlákna

### **e) Komplikace při zavádění vláken 2**

Globální proměnné  
Nereentrantní volání knihovních fukncí  
Přístup ke sdíleným prostředkům  
Znalost implementace signálů  
Stack

### **f) Posixová knihovna vláken: nástroje pro řešení problémů souběhu a jejich účel 3**

mutex - přístup do kritické sekce  
semafor - přístup do kritické sekce/synchronizace  
bariéra - synchronizace

## 10) **Plánovač. Cíle plánování, režimy plánování, plánovací kriteria (cíle) pro plánovací algoritmy, plánovací algoritmy**

### **a) Úloha plánovače, režimy plánování procesů 3**

Rozhoduje který proces (vlákno) má CPU  
Režimy:

* Nepreemptivní - proces se musí sám vzdát CPU
* Preemptivní - plánovač rozhodne kdy a který proces dostane CPU

### **b) Cíle plánování (obecně a dle určení OS) 3**

Obecně

* Spravedlnost - každý proces stejně času
* Dodržování strategie - na různých systémech může být jiná
* Efektivní využití zdrojů - snaha optimalizovat výkon

Dle OS

* Interaktivní systémy - minimalizace odezvy
* Dávkové systémy - maximalizace propustnosti, maximální využití CPU
* RT systémy - předvídatelnost, respektování lhůt

### **c) Popis plánovacích algoritmů: historické 3**

Fronta jednotlivých úloh

* Nepreemptivní  
* Úlohy se řadí do fronty
* CPU procesu přiděleno procesu, který čekal ve frontě nejdéle

Víceúlohová FIFO

* Nepreemptivní
* CPU Přiděleno tomu, který má nejkratší dobu provádění

Podle odhadu doby běhu úlohy

* Preemptivní
* CPU Přiděleno tomu, který má nejkratší dobu dokončení

### **d) Popis plánovacích algoritmů: moderní a specifické 6**

Round-Robin

* Preemptivní, založené na časovači
* Každý proces dostane stejný časový úsek

Prioritní

* Dává přednost procesu s vyšší prioritou

Uživatelsky férové

* Každému uživateli stejné podmínky

Loterie plánování

* Každý proces dostane tiket a periodicky se losuje

## 11) **Požadavky na plánování v systémech reálného času. Možnosti plánování vláken na víceprocesorových systémech (SMP). Časové a periodické plánování úloh uživatelem – příkazy at a crontab**

### **a) Kritéria pro plánování v systémech reálného času, plánovatelnost 4**

* Rýchlý FS
* Rychlá komunikace procesů
* Rychlé přepínání kontextu
* Preemptivní plánování procesů

### **b) Možné optimalizace plánování vláken na systémech SMP 4× 2**

* Sdílení zátěže - zátěž se rozděluje mezi procesory náhodně (žádný procesor nezůstane nevyužitý)
* Skupinové plánování - vlákna jsou naplánovaná tak, aby běžela na různých procesorech současně
* Pevné přiřazení procesoru -  všem vláknům jsou napevno přiřazené procesory
* Dynamické plánování - počet vláken se může během provádění měnit

### **c) Příkazy pro nastavení spouštění úloh v daném čase a démony, které to obstarávají. Orientačně možnosti konfigurace 3**

Příkaz at - provede daný příkaz jednou v určitý čas  
Příkaz crontab - provede příkaz opakovaně. /etc/crontab

## 12) **Požadavky na paměť, alokace, adresování, pevné (statické) a proměnné (dynamické) dělení paměti (fixed partitioning, variable partitioning), fragmentace paměti, typy fragmentace, umisťovací algoritmy**

### **a) Požadavky na operační paměť (na její vlastnosti) 3**

Relokace paměti procesoru  
Ochrana paměti  
Sdílení paměti mezi procesory  
Logická a fyzická organizace  

### **b) Pevné dělení paměti, nevýhody, umisťování procesů 4**

Paměť je rozdělena do oblastí s pevnými hranicemi.  

Všechny oblasti mají stejnou velikost.  

* Pokud malý proces zabere celou oblast, jedná se o neefektivní využití paměti

Oblasti mají různé velikosti

* Pro každý proces se vybírá nejvhodnější oblast

### **c) Dynamické dělení paměti, nevýhody 4**

Proměnný počet oblastí i jejich velikost  
Po ukončení procesu vznikají v paměti mezery

### **d) Umisťovací algoritmy pro dynamické dělení paměti (s popisem) 4**

Best fit

* Vybere stejnou nebo nejmenší volnou oblast
* Nejméně výkonná metoda
* Nejmenší možná fragmentace

First-fit

* Vybere první volnou oblast
* Rychlejší
* Prohledávání zpomaluje

Next-fit

* Pamět je prohledávána vždy od stejného místa, kde se naposledy umísťovalo
* Nejrychlejší

Worst-fit

* Vybírá oblast stejně velkou jako proces nebo největší volnou
* Nejhorší využití paměti

## 13) **Problém nedostatku operační paměti, odkládání obsahu paměti na disk, virtuální paměť, motivace k zavedení virtuální paměti, výhody virtualizace paměti, princip lokality odkazů, thrashing**

### **a) Možná řešení nedostatku RAM (s vysvětlením principu) 2 + 2**

Swapping (odkládání) - Odkládání procesu z RAM Na pamět SWAP  
Overlaying (překrývání) - Různé moduly nejsou využívány současně, takže využívají stejnou fyzickou pamět

### **b) Virtualizace paměti: definice a HW podpora 3**

Způsob správy paměti, který umožňuje předložit procesu větší množší paměti než je skutečně nainstalováno  
HW podpora - CPU musí umět pracovat s virtuální adresou. MMU poté převádí virtuální adresu na skutečnou

### **c) Virtualizace paměti: motivace a důsledky zavedení, princip fungování 2**

Všechny adresy, které proces používá, jsou spravovány pouze jako virtuální – transformaci na fyzické adresy provádí správa virtuální paměti.  
Pokud potřebuje více operační paměti, může operační systém požádat o přidělení další paměti.

### **d) Virtualizace paměti: pojmy (RS, S) 1**

Resident-set => část adresové prostoru, který je v RAM  
SWAP => sekundární pamět, kam lze dočasně uložit nepoužívané části adresového prostoru

### **e) Princip lokality odkazů 2**

Proces má tendenci přistupovat k okolí svého adrsového prostoru, kam přistupoval nedávno, proto lze odvodit, kterou část paměti bude proces v nejbližší budoucnosti potřebovat. Umožňuje efektivněji využít virtuální paměť.

### **f) Thrashing – definice a příčiny 3**

Část paměti je odložena těsně před tím, než bude potřeba.  

* Vzniká při špatné organizaci odkládání částí paměti na disk
* Může být následkem nedostatečného dodržení principu lokality odkazů

## 14) **Stránkování paměti, převod adresy, vlastnosti stránkování, sdílení stránek, volba velikosti stránky, řešení problému rozsáhlých stránkových tabulek, TLB**

### **a) Princip, vlastnosti (spojitost, fragmentace, sdílení) 5**

RAM je rozdělena na oblasti malé velikosti - rámce.  
Logický adresový prostor se rozdělí na stejně velké části jako RAM - stránky.  
OS pak udržuje pro každý proces tabulku přiřazení stránek k rámcům.  
Logická adresa se skládá z čísla stránky a offsetu  
Umístění stránek je nespojité

### **b) Stránkové tabulky, převod adresy 4**

Stránková tabulka obsahuje řídící bity

### **c) Volba velikosti stránky a důsledky 3**

Menší stránky

* Menší vnitřní fragmentace  
* Více stránek na proces - větší stránková tabulka
* Více rámců v RAM - lepší hospodaření s RAM

Větší stránky

* Větší vnitřní fragmentace
* Menší stránkovací tabulka
* Méně rámců - horší hospodaření s RAM

### **d) Řešení rozsáhlosti stránkových tabulek, TLB 3**

Velikost tabulky může být velká, proto se tabulka umisťuje také do virtuální paměti  

TLB = speciální cache pro položky stránkové tabulky. Obsahuje poslední použité položky stránkové tabulky

## 15) **Řídicí bity ve stránkových tabulkách, strategie zavádění, umisťování, nahrazování a uklízení (čištění) stránek paměti, vliv velikosti resident-set na běh procesů**

### **a) Důležité řídicí bity ve stránkové tabulce a jejich význam 3**

32bitový režim - dolních 12 bitů je řídících

### **b) Strategie zavádění stránek: účel, algoritmy 3**

fetch policy - určuje která stránka se má zavést do RAM  
demand pagging - zavedení stránek jen když jsou třeba  
lookahead pagging - zavedení stránek předem

### **c) Strategie umisťování dtránek: účel, algoritmy 1**

Placement policy - určuje do které části RAM se stránka zavede  
Typicky se tím OS nezabývá - vybíra libovolný volný rýmec

### **d) Strategie nahrazování stránek: účel, algoritmy 4**

Replacement policy - určuje které stránky se z RAM odloží na disk  
Ideální strategie - odstranění stránky, která bude nejdelší dobu nevyužitá  
Zamykání rámců - pro stránky, které nesmí být z RAM odloženy

### **e) Strategie uklízení (čištění) stránek: účel, algoritmy 3**

Cleaning policy - určuje kdy se modifikované stránky uloží na disk  
Demand cleaning - ukládání stránky, které nesmí být z RAM odloženy  
Precleaning - periodické ukládání stránek v dávce

### **f) Volba velikosti resident-set 1**

Pevná alokace - pevný počet rámců  
Proměnná alokace - počet rámců se může měnit

## 16) **Požadavky na OS pro práci v reálném čase, rozdělení RT OS, pojmy latence a odezva (na úrovni přerušení); vestavěné systémy, OS pro ně a typické požadavky na ně**

### **a) Definice systémů RT (pracujících v reálném čase) a jejich správná funkce 1**

Operační systém pracující v reálném čase.  

* Determistické (předvídatelné) chování
* Krátká doba odezvy
* Vysoká spolehlivost

### **b) Rozdělení systémů RT dle dodržování termínů (s popisem) 3**

* Hard real-time - při nedodržení časových limitů systém selhává
* Soft real-time - při nedodržení časových limitů se sníží účinnost
* Firm real-time - může občas zameškat časové limity bez selhání

### **c) Charakteristické vlastnosti RTOS 4**

* Rychlé přepínání kontextu
* Malé rozměry
* Rychlý FS
* Spolehlivost
* Multitasking

### **d) Příklady RTOS (alespoň dva) 1**

RTLinux, QNX, VxWorks

### **e) Definice pojmů latence a odezva (na úrovni přerušovacího systému) 2**

latence - doba mezi příchodem požadavku  
doba odezvy - doba za jak dlouho OS zareaguje na požadavek

### **f) Definice vestavěných systémů 1**

Počítačové systémy, které jsou součástí jiných systémů. Obvykle představují jejich řídící složku nebo tvoří jejich podsystémy

### **g) Typické vlastnosti vestavěných systémů (alespoň šest) 3**

* Malá spotřeba
* Odolnost
* Malé rozměry a váha
* Spolehlivost a bezpečnost
* cenová citlivost
* Funkce v reálném čase

## 17) **Víceprocesorové systémy, rozdělení dle vazby a dle symetrie, granulovatelnost úlohy, souvislost s vazbou (víceprocesorových systémů) a stupně paralelismu, distribuované (rozptýlené, clusterové) OS**

### **a) Kategorie počítačových systémů z hlediska paralelizace zpracování dat 4**

SISD (single instruction single data) - jeden procesor zpracovává jednou sadou jednu množinu dat  
SIMD (single instruction multiple data) - jeden procesor zpracovává jednou sadou více množin dat  
MISD - (multi instruction single data) - více procesů zpracovává více sadami jednu množinu dat  
MIMD (multi instruction multi data) - více procesorů zpracovává více sadami více množin dat

### **b) Rozdělení víceprocesorových systémů dle vazby 2**

S volnou vazbou - každý procesor má vlastní RAM  
S pevnou vazbou - procesory sdílejí RAM

### **c) Rozdělení víceprocesorových systémů dle symetrie 2**

Symetrické

* Shodné procesory
* Procesy smí být prováděny jakýmkoliv procesorem

Asymetrické

* Procesory jsou různé - specializované
* Systém je řízen centrálním procesorem

### **d) Granularita úlohy: účel, jak se pozná, že úloha je/není granulovatelná 4**

Každou úlohu můžeme rozčlenit na úseky, které lze provést samostatně. Ty pak lze na MP systému provádět paralelně na různých procesorech  
Pokud jeden úsek potřebuje pro svoji činnost výsledky jiného, musí na tyto výsledky čekat - nutnost komunikace a synchronizace

### **e) Granularita a vhodné stupně vazby 3**

Hrubě granulovatelná úloha - méně úseků, vhodné pro kooperující procesy  
Jemně granulovatelná úloha - více kratších úseků, synchronizace je častější.

## 18) **Soutěžení procesů (o prostředky), obecné problémy souběhu, vzájemné vylučování, kritická sekce, předpoklady pro řešení KS, požadované vlastnosti řešení KS, typy řešení**

### **a) Definice kritické sekce v programu 4**

Jedná se o část kódu procesu, který manipuluje se sdílenými prostředky a současná manipulace s nimi by vedla k problému.  
V KS smí být pouze jeden proces  
Skládá se ze vstupní sekce, kritické sekce, výstupní sekce a zbytkové sekce

### **b) Předpoklady pro řešení přístupu do kritické sekce. (Co se předpokládá, že platí, a co se nesmí předpokládat) 4**

Nenulová rychlost procesů  
Specifikace vstupní a výstupní sekce
Žádné předpoklady o relativní rychlosti procesů  
Žádné předpoklady o prokládaném provádění  

### **c) Požadované vlastnosti řešení přístupu do kritické sekce (s vysvětlením) 3**

Vzájemné vylučování - vždy jeden proces v KS  
Pokrok v přidělování - rozhodování o vstupu mohou řídit pouze procesy, které nejsou v ZS a toto rozhodnutí musí padnout v konečném čase  
Omezené čekání - Mezi požadavkem na vstup do KS a vyhověním  do KS smí vstoupit pouze omezený počet procesů

### **d) Typy řešení přístupu do kritické sekce (s příklady) 4**

Softwarové řešení- algoritmy pro vstupní a výstupní sekci  
Hardwarové řešení - instrukce procesoru  
Řešení operačního systému - semafory...  
Řešení programovacího jazyka - konkurenční programování

## 19) **Řízení přístupu do kritické sekce pomocí SW metod, příklady nevhodných (obecně nefunkčních) SW řešení, SW algoritmy, vlastnosti (nedostatky) SW metod**

### **a) SW algoritmus pro KS s proměnnou locked, důvod nefunkčnosti 1 + 1**

Sdílená proměnná locked (true/false) inicializována na 0  
Proces čeká dokud je KS obsazena (locked != 0) - jakmile je KS volná, nastaví se locked = 1  

* Pokud oba procesy současně zjistí volnou KS, oba nastaví obsazeno a vstoupí do ní -> požadavek vzájemného vyloučení není splněn

### **b) SW algoritmus pro KS s proměnnou turn, důvod nefunkčnosti 1 + 1**

Sdílená proměnná turn inicializována na 0 nebo 1 - udává který proces smí vstoupit do KS  
Proces Pi smí vstoupit do KS jestliže turn = i  
Proces Pi aktivně čeká jestliže turn = j

* vzájemné vylučování splněno, ale požadavek pokroku není splněn!

### **c) SW algoritmus pro KS s proměnnými flag[i], důvod nefunkčnosti 1 + 1**

Sdílená proměnná flag[i] pro každá proces Pi  
Při vstupu do KS se Pi ptá zda flag[i] = true  
Ve výstupní sekci proces nastaví flag[i + 1] = true -> umožňí vstup dalšímu procesu  

* Pokud však chtějí procesy vstoupit do KS znovu, mají nastaveno true a hrozí deadlock -> požadavek pokroku není splněn

### **d) Funkční SW algoritmy pro řízení přístupu do KS, krátká charakteristika 2 + 2**

Petersonův algoritmus

* Kombinace turn s flag. Pokud se oba procesy pokusí vstoupit do KS současně, pouze jeden bude mít potřebnou hodnotu turn

Leslie Lamports bakery algoritmus

* Každý proces dostane před vstupem číslo. Nejmenší číslo smí vstoupit do KS.

### **e) Specifické nevýhody SW algoritmů pro řízení přístupu do KS (včetně vysvětlení, bez všeobecných nevýhod všech typů algoritmů) 5**

Neodolnost vůči chybám v KS - pokud proces havaruje v KS, ostatní procesy se do KS nedostanou  
Aktivní čekání - spotřebovávají zbytečně čas procesoru

## 20) **Řízení přístupu do kritické sekce pomocí HW metod, výchozí předpoklady pro HW řešení, algoritmy využívající HW instrukce, vlastnosti (nedostatky) HW metod**

### **a) Hardwarové předpoklady pro řízení přístupu do KS 3**

Procesy jsou prováděny kontinuálně  
K přerušení může dojít pouze na hranicích intrukcí  
Přístup k paměti je výlučný

### **b) HW podpora pro řízení přístupu do KS, popis řešení 2 + 3**

Zákaz přerušení

* Zákaz přerušení způsobí, že proces nemůže být přerušen, tudíž žádný jiný proces nemůže vstoupit do KS
* Vzájemné vylučování zajištěno pouze na jednoprocesorových systémech

Speciální instrukce test-and-set

* Jedna instrukce přečte příznak a zároveň ho nastaví
* Byl-li příznak nastven - KS obsazena. Nebyl-li - vstup do KS

Speciální instrukce xchg

* pro intel x86
* Využívá proměnnou locked inicializovanou na 0
* Funguje jako test-and-set

### **c) Vlastností (nedostatky) HW řešení 4 + 3**

* Aktivní čekání
* Řeší pouze vzájemné vylučování, ostatní vlastnosti KS je třeba řešit algoritmicky
* Krátká vstupní a výstupní sekce

## 21) **Nástroj OS: semafor, jeho popis včetně systémových volání, použití semaforu pro řízení přístupu do KS a pro synchronizaci, problém obědvajících filozofů**

### **a) Popis nástroje OS: semafor 2**

Semafor je prostředek OS - synchronizační nástroj.  
Jedná se o datovou strukturu obsahující čítač, frontu a operace init, wait a signal (post)

### **b) Popis systémových volání semaforu 1 + 2 + 2**

init - inicializuje čitač na požadovanou hodnotu  
wait - snižuje hodnotu čitače o 1. Pokud je hodnota záporná, vloží proces do fronty  
signal (post) - zvyšuje hodnotu čitače o 1. Pokud je ve frontě proces, tak je uvolněn

### **c) Popis řešení přístupu do KS používajícího semafor 3**

Semafor se inicializuje na 1 pro KS - sem_init(&s, 1);  
Ve vstupní sekci se volá sem_wait(&s);  
Ve výstupní sekci se volá sem_post(&s);

### **d) Popis řešení synchronizace vláken pomocí semaforu 3**

Semafor se inicializuje na 0 pro synchronizaci - sem_init(&s, 0);  
Proces, který má čekat, volá sem_wait(&s);  
Proces, na který se čeká (koná svou práci), volá sem_post(&s);

### **e) Definice problému obědvajících filozofů a jeho řešení pomocí semaforů 2**

U stolu sedí 5 filosofů. Každý buď jí nebo přemýšlí. Při jídle potřebuje dvě vidličky a na stole jich je 5.  

* Musíme dovolit zvedat vidličky nejvýše 4 filosofům (n -1) - pak vždy aspoň jeden filosof může jíst, ostatní musejí čekat

## 22) **Nástroj OS: předávání zpráv, popis systémových volání a možností blokování, použití fronty zpráv pro řízení přístupu do KS a pro synchronizaci, problém svázaných producentů a konzumentů**

### **a) Popis nástroje OS: předávání zpráv 3**

Je to komunikační prostředek OS pro procesy  
Je nutné vzájemné vylučování  
Systémová volání send(cíl, zpráva), receive(zdroj, zpráva)

### **c) Popis řešení KS používajícího frontu zpráv 3**

Typická implementace blokování send a receive pro fronty zpráv s omezenou velikostí  

* neblokující send - blokuje pouze po zaplnění fronty zpráv
* blokující receive - je blokován pokud není dostupná žádná zpráva

Neblokující varianty lze nastavit parametrem - pak místo blokování vrací chybu

### **d) Popis řešení synchronizace vláken pomocí fronty zpráv 3**

Sdílená fronta se inicializuje zasláním jedné zprávy  
Vstupní sekce volá blokující receive  
Výstupní sekce volá neblokující send

### **e) Definice problému svázaných producentů a konzumentů a jeho řešení pomocí fronty zpráv 3**

Do fronty zpráv (storage, buffer) zasílají producenti zprávy  
Kapacita je omezená maximální velikostí fronty  
Konzumenti vybírají zprávy voláním receive

## 23) **Nástroj programovacích jazyků: koncept monitoru, problém producentů a konzumentů a jeho řešení pomocí monitoru**

### **a) Popis konceptu monitoru: jeho účel, struktura a základní vlastnosti 2 + 2**

Je to softwarový modul (něco jako třída) ve vyšším programovacím jazyce.  
Obsahuje lokální proměnné (sdílená data) a funkce pro zpřístupnění  
V monitoru (jeho funkci, KS) smí být pouze jediné vlákno (zajišťuje vzájemné vylučování)  
Synchronizaci lze zajistit podmínkovými proměnnými

### **b) Popis řešení KS pomocí monitoru 2**

Kód KS je umístěn ve funkci monitoru  
Pro vykonání KS se pak volá tato funkce

### **c) Popis řešení synchronizace vláken pomocí monitoru 3**

Lze vyřešit pomocí podmínkových proměnných s proměnnou se stavem akce.

### **d) Definice problému svázaných producentů a konzumentů a jeho řešení pomocí monitoru, podmínky použité u synchronizace a zdůvodnění jejich použití 6**

Producenti ukládají data na volná místa ve skladu a konzumenti vybírají data z obsazených míst.  
Konzumenti musejí čekat, pokud je sklad prázdný, producenti musejí čekat, pokud je sklad plný  

* Sdílená data (sklad) jsou definovány uvnitř monitoru.
* Monitor obsahuje funkce take a append. Synchronizace se řeší pomocí podmínkových proměnných

## 24) **Nástroje knihovny posixových vláken: mutex, bariéra, podmínková proměnná**

### **a) Popis mutexu, účel a vlastnosti, popis funkcí 3**

Binární semafor  
Místo čitače obsahuje true/false hodnotu inicializovanou na false  
Zaručuje vzájemné vylučování, využívá neaktivní čekání  
wait = lock, signal = unlock  

* lock - nastaví logickou proměnnou na false - blokující volání  - umístí proces do fronty
* unlock - nastaví logickou proměnnou na true - neblokující volání - odemkne mutex je-li fronta prázdná

### **b) Způsob použití mutexu 2**

Využití hlavně pro řešení přístupu do KS  
Vstupní sekce: lock  
Výstupní sekce: unlock

### **c) Bariéra: účel, použití a popis funkcí (včetně návratové hodnoty funkce čekání) 1 + 4**

Object sloužící pro synchronizaci startu vláken  
Umožňuje vláknům neaktivně čekat na ostatní vlákna  
Bariéře se inicializuje počet vláken které je třeba sesynchronizovat  
Jakmile se k bariéře dostane daný počet vláken, bariéra propustí všechny naráz - paralelní běh

operace wait

* wait je voláno tolikrát, na kolik je inicializovaný čitač
* Vrací 0 při úspěšném volání, nenulovou hodnotu pro chybu
* Vrací PTHREAD_BARRIER_SERIAL_THREAD kterou vrátí jen pro jedno nespecikované vlákno

### **d) Podmínková proměnná: účel, způsob použití a vlastnosti 1 + 4**

Slouží pro synchronizaci vláken  
Umožňuje neaktivně čekat na událost  
Na událost může čekat několik vláken  
Událost je oznámena signálem - probouzí jedno vlákno, ale lze i poslat vísměrový signál a probudit všechna vlákna

## 25) **Stav uváznutí (deadlock) a vyhladovění (definice a rozdíl), nutné podmínky pro vznik stavu uváznutí, předcházení a řešení problému stavu uváznutí, algoritmus bankéře**

### **a) Definice stavu uváznutí (deadlock) 2**

Každý proces ve skupině čeká na událost, kterou může vyvolat jen proces v dané skupině => Procesy budou nekonečně dlouho čekat, protože událost může vyvolat jen proces, který taky čeká na událost

### **b) Definice stavu vyhladovění (starvation), příklad 1**

Nekonečné čekání procesu na přidělení prostředku - proces nemá žádný pokrok  
Proces v soupeření o prostředek neustále prohrává - například kvůli nízké prioritě

### **c) Vysvětlení podmínek pro vznik stavu uváznutí 4**

* Vzájemné vylučování - prostředky lze vlastnit pouze jedním procesem  
* Alokace a čekání - proces vlastnící prostředky může vyžadovat další
* Neodnímatelné prostředky - OS je nemůže odebrat, musí být uvolněny explicitně
* Cyklické čekání - řetěz vzájemně čekajících procesů uzavírá cyklus  

### **d) Přístupy k řešení odstranění vzniklého stavu uváznutí 3**

* Ignorování problémy
* Detekce a obnovení - obnova do stavu bez uváznutí
* Prevence - negace alespoń jedné podmínky

### **e) Způsoby prevence vzniku stavu uváznutí 3**

* Negace vzájemného vylučování
* Negace alokace a čekání - zajištění alokace všech prostředků naráz
* Negace neodnímatelných prostředků - možnost nenásilného odebrání prostředku
* Negace cyklického čekání - nedovolit alokaci pokud by vznikl cyklus
* Dovolení pouze bezpečných stavů

### **f) Popis bankéřova algoritmu aplikovaného na procesy (s popisem stavů) 2**

Bankéř (OS) poskytuje klientům (procesy) pujčku (prostředky) - pokud požadavek vede k nebezpečnému stavu, požadavek je odmítnut  

## 26) **IPC: komunikace procesů a vláken, možné prostředky komunikace**

### **a) Možné prostředky pro komunikaci procesů / vláken 5**

* Soubor, databáze
* Roura
* Socket
* Fronta zpráv
* Sdílená pamět

### **b) Krátká charakteristika prostředků pro komunikaci procesů / vláken 5**

* Soubor, databáze - pomalé, současný přístup je třeba řídit
* Roura - proudouvý přístup (FIFO), jednosměrná komunikace
* Socket - proudouvý přístup (FIFO), obousměrná komunikace
* Fronta zpráv - jednosměrná komunikace
* Sdílená pamět - nejrychlejší, nutno řídit

### **c) Popis funkcí pro sokety (alespoň pěti typů) 5**

* bind - svázání socketu s lokálním portem
* connect - navázání spojení
* send - poslání zprávy
* recv - přijmutí zprávy
* close - uzavření socketu
* listen - zahájení naslouchání
* accept - přijetí spojení

## 27) **Dělení disku na oddíly, zavaděč OS, důvody dělení, MBR, GPT, swap**

### **a) Popis důvodů pro rozdělení disku na oddíly 4**

* Více operačních systémů
* Možnost oddělit data od OS
* Možnost vytvoření oddílu SWAP
* Porucha pouze jednoho oddílu neporuší ostatní
* Vícero jiných FS
* Snadnější správa
* Snadnější obnova

### **b) Popis MBR a způsob dělení disku na oddíly 3**

Master Boot Record

* První sektor na disku
* Tabulka rozdělení disku na oddíly
  * Primární - lze na něj nahrát OS
  * Rozšířený - dělí se na logické oddíly
* Velikost disku maximálně 2 TB
* Maximálně 4 oddíly

### **c) Popis typů oddílů (pro dělení MBR) 3**

* Primární - lze na něm zavést OS
* Rozšířený - obsahuje logické oddíly
* Logický - nelze zavést OS, slouží k ukládání dat

### **d) Charakterizace GPT 3**

GUID Partition Table

* Standard UEFI
* Náhrada za MBR (odstraňuje jeho limity)
* Až 128 primárních oddílů
* Možnost využít disk větší jak 2 TB

### **e) Vysvětlení rozdílů mezi odkládacím prostorem (swap) na samostatném diskovém oddíle a v souboru 2**

Swap na diskovém oddíle - rychlejší, horší správa  
Swap v sobour - pomalejší, velikost se může měnit podle potřeby

## 28) **Souborový systém, metadata, speciální soubory**

### **a) Popis obecné struktury souborových systémů a jejich metadat 3**

Umožňují uživatelům a procesům přístup k souborům na pamětovém médiu  
Vytváří logickou strukturu souborů  
Eviduje metadata souborů  
Organizuje uspořádání souborů na médiu  
Sjednocuje přístup k datům různého typu

### **b) Metadata souborů vyjma oprávnění (alespoň šest) 3**

* Typ
* Velikost
* Čas změny
* umíštění
* jméno
* vlastník
* oprávnění

### **c) Možná oprávnění na soubor (alespoň šest) 3**

* Provádění
* Čtení
* Zápis
* Mazání
* Vytváření
* Změna práv
* Přidávání (append)

### **d) Popis zvláštních typů souborů (alespoň čtyř) 2**

* Odkazy - soubory, které odkazují na jiný soubor
* Adresáře - obsahují soubory  
* Pojmenovaná roura - jednosměrný komunikační nástroj
* Pojmenovaný socket - obousměrný komunikační nástroj
* Zařízení - Speciální soubor pro přístup k HW

### **e) Charakteristika typů odkazů a jejich reprezentace na souborovém systému 2 + 2**

Pevné

* Jedná se o soubor s novým jménem, který bude odkazovat na stejná data a metadata jako nějaký již existují soubor
* Nelze vytvářet mezi různými FS
* Ke smazání dojde při smazání posledního odkazu

Symbolické

* Soubor s novým jménem, který při odkazu na něj provede textovou záměnu jména za nějaký již existující soubor
* Může být absolutní nebo relativní cesta

## 29) **Konzistence metadat souborových systémů: příčiny vzniku nekonzistencí, metody zachování konzistence, vlastnosti metod, příklady souborových systémů**

### **a) Popis příčiny vzniku nekonzistence metadat souborového systému 3**

Zápis dat do souboru znamená provedení několik operací na různých místech na médiu. Tyto změny probíhají postupně - může dojít ke vzniknu nekonzistence.  
Po pádu systému je třeba provést kontrolu

### **b) Popis principu žurnálování a činnost obnovy konzistence po pádu 5**

Zabraňuje ztrátě konzistence dat při pádu systému, ale nezabraňuje ztrátě dat  
Změny metadat se zapisují do transakčního logu. Teprve po potvrzení zápisu do žurnálu se provede patřičná změna souborového systému - dvojí zápis = zpomalení  
Při startu po pádu systému se nemusí kontrolovat konzistence celého souborového systému, ale prochází se pouze žurnál

### **c) Popis principu metody copy-on-write a činnost obnovy konzistence po pádu 4**

Kopírování bloku při změně  
NEkonzistence vzniká při změně informací - zápisu  
Souborový systém vytvoří kopii bloku a upravuje ten. Po dokončení se provede zneplatnění původních dat/metadat a potvrdí se platnost nových => FS je vždy konzistentní

### **d) Příklady souborových systémů ve vztahu k metodě zachování konzistence, alespoň dva různé pro každou metodu (nikoliv různé verze téhož), pro žurnálování zvlášť po dvou příkladech pro dvojí způsob 3**

Souborové systémy bez konzistence po pádu

* FAT
* ext2

Žurnálovací FS

* Úplné žurnálování: ext3/ext4, ReiserFS
* Žurnálování metadat: NTFS, XFS

Copy-on-write FS

* ZFS
* BtrFS
* Nilfs
* ReFS

## 30) **Typy úložišť, RAID, způsob alokace dat souborů**

### **a) Popis typů úložišť (DAS, NAS, SAN) 3**

DAS (Directly attached storage)

* Lokální pamětové úložiště

NAS (Network attached storage)

* Úložiště zpřístupněné síťovým protokolem

SAN (Storage Area Network)

* Blokové zařízení zpřístupněné síťovým protokolem

### **b) Charakteristika RAID 0 (způsob zapojení a ukládání dat, odolnost, rychlost R/W) 3**

* Minimálně dva disky
* Stripping - prokládané ukládání
* Rychlejší
* Výpadek disku znamená ztrátu všech dat

### **c) Charakteristika RAID 1 (způsob zapojení a ukládání dat, odolnost, rychlost R/W) 3**

* Minimálně dva disky
* Mirroring - zrcadlené ukládání
* Rychlejší
* Celková kapacita pouze jednoho disku
* Výpadek disku NEZNAMENÁ ztrátu dat

### **d) Charakteristika RAID 5 (způsob zapojení a ukládání dat, odolnost, rychlost R/W) 3**

* Minimálně tři disky
* Stripping + parity - prokládání s paritou
* Rychlejší
* Kapacita snížena o jeden disk
* Při výpadku disku lze dopočítat data z parity

### **e) Charakteristika možných způsobů alokace dat pro soubory 3**

Souvislá alokace

* Po sobě jdoucí bloky
* Dochází k vnější fragmentaci

Řetězená alokace

* Alokují se jednotlivé bloky
* Alokační tabulka obsahuje seznam těchto bloků
* Bloky nemusí být u sebe

Indexová alokace

* Index obsahuje seznam bloků
* Bloky mohou mít různou velikost

## 31) **Vzdálený přístup k OS, telnet, SSH, autentizace, autorizace, zásady tvorby hesla, typy útoků na systém a prevence**

### **a) Definice pojmů autentizace a autorizace 2**

Autentizace - ověření identity  
Autorizace - ověření práv

### **b) Možné metody autentizace (alespoň čtyři) 2**

* Login + heslo
* Biometrie
* RFID karty
* Certifikáty
* Secret klíče
* Tokeny

### **c) Popis principu zabezpečení přihlašování pomocí protokolu SSH 3**

Při prvním připojení z daného pc dochází k:

* Server nám vrátí otisk klíče, který by měl uživatel ověřit s administrátorem
* Po potvrzení se klíč uloží a při dalším přihlášení je kontrolováno, zda je klíč stejný
* Klient ssh se pokusí autentizovat uživatele - několik metod, nejčastější je ověření hesla

SSH komunikuje zabezpečeně

### **d) Riziko přihlašování pomocí protokolu SSH a jak mu předcházet 2 + 2**

Riziko nastává při prvním přihlášení na server. Server předá uživateli klíč, který není šifrovaný. Útočník je může vyměnit za své. Komunkace poté běží přes útočníka a ten poslouchá komunikaci.  

* Tomuto lze předejít kontrolou klíče s administrátorem (nebo pokud má server tento klíč vystaven na webové stránce)

### **e) Zásady tvorby hesla (čtyři nejdůležitější) 2**

* Minimálně 8 znaků
* Jiné heslo pro každou službu
* Kombinace různých znaků (velká/malá písmena, čísla, speciální symboly)
* Neslovníková slova

### **f) Popis alespoň čtyř typů útoků na systém 2**

* Login spoofing / phishing - podvržení přihlašovací obrazovky
* Trojský kůn - nevinně vypadající program, který má škodlivou funkci navíc
* Zadní vrátka - vložená metoda, který umožňuje vzdálený přístup
* Časované bomby - škodlivý kód je spuštěn za určitých okolností či po určitě době
