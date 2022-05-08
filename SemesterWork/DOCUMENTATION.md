Maticová kalkulačka
=============

## Ovládání

Program zajíšťuje možnost ovládání maticemi.
Realizováné algebraické operaci: násobení matic na vektor i navzájem, sčítání, odčítání ,transpozice a takže umocňování.
Takže program může najít řád, determinant, hodnost matice, je-li matice čtvercová, regulární anebo obdelníková. Pro čtvercové matice můžeme vypočítat inverze.
Případně matici můžeme sloučat a ořízat (pro oříznutí program požádá vektor s určenými body), a takže ukladát do proměn typu 'char', pro které možně dálší používání do skončení běhu programy.
Takže program umožnuje vypočet soustav rovnic pomocí Gaussové eliminační metodě ( sloupců má být více než řádků).

## Implementace

Program implementuje několik tříd:
  1. CMatrix - pro prace z maticemi.
  2. CGem a CGemKomentare - pro vypocet řešení soustavy rovnic.
  3. DiffMatrix, SumMatrix a MultMatrix - pro základní algebraické operaci mezi maticemi.

Hlavní třída CMatrix má public a protected metody a atributy(není private, protože možně dálší rozvijení programy).

K private části patří:

       float ** _data

kde budou dynamické alokované 2D pole a uložení prvky matice

       size_t _rows, _cols

kde evidujeme velikost matice a metody

       void clearMemory()

pro uvolnení a smazání náhradných pole pro vypočty

       int findDet()

rekurzivní funkce vypočtu determinantu na různých etapech vypočtu hodnosti a determinantu matice

       int l_min()

pomocná metoda pro hodnost a determinant, vypočítá nejmenší z delek velikosti matice

K public části patří:

       CMatrix(size_t rows = 1, size_t cols = 1)

konstructor matice,který alokuje paměť pro matice, s počatečnými hodnotami 1, 1 ,pokud neukázali rozměr matice. Dostáváme matice { 0 }.

       CMatrix(size_t rows, size_t cols, float ** data)

pomocní konstructor pro alokace a přídavání nejakého 2D pole pro matice

       CMatrix(const CMatrix& b)

kopirovácí konstruktor matic, přenese poli do _data a přepíše prvky

       ~CMatrix()

destructor, který uvolní alokované prostředky paměti pro matice

       size_t rows() const, size_t cols() const , float ** data()const

gettery pro protected atributy matice, a přístup k prvkům

       void Power(size_t n)

umocňování matice na nějaké kladné číslo

       CMatrix Trans()

metoda transponuje matice a vrácí se novou matice

       bool IsSquare() const

metoda pro určení, zda ta matice je čtvercová nebo ne, pokud ano se vrátí true, pokud ne - false

       bool IsRegular()

určuje regularitu matice

       float Det()

vypočítá determinant matice pomocí protected metody findDet()

       int Rank()

vypočítá hodnost matice pomocí determinantů

       CMatrix Inverse()

metoda udělá novou inverzní matice a vrátí jí, nemění původní matice

       CMatrix Split(size_t new_rows = 0, size_t new_cols = 0)

metoda ořízne matice na nějaký vector, pak se vrátí novou matice, nemění původní matice

       CMatrix Merge(const CMatrix& a)

metoda sloučí matici, vrátí se novou matice, nemění původní

Třida CGem implementuje vypočet řešení soustavy rovnic bez komentaře , a dědiná od CGem třida CGemKomentare vypočítá řešení s komentařemi.

Třida DiffMatrix a její dědiné třidy SumMatrix a MultMatrix implementování, aby mohli použivat algebraické operaci s maticemi v běhu programy.
