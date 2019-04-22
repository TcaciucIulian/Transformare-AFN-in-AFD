# Transformare AFN->AFD

Implementare transformare automat finit nedeterminist in automat finit determinist

Realizator : Tcaciuc Iulian-Marius
Coordonator : -


Documentatie:
  
  IMPLEMENTARE TRANSFORMARE AFN->AFD
  
  Cerinta : Transformare AFN->AFD
    
  Descriere implementare:     

* Programul prezinta 2 structuri cu denumiri semnificative ( AFN , AFD ) in care se memoreaza informatii despre AFN, respectiv AFD.
Acesta contine 8 metode, fiecare cu un rol semnificativ ( creareGraf, cautareVector, intersectareStari, creareTabel, scriereInversa, cautareNumar, creareAFD, citireAFD )



  Explicarea metodelor:
   
  1. Functie de creare a matricei tridimensionale corespunzatoare AFN-ului . In aceasta functie citim caractersticile automatului dat si initializam matricea.

void creareGraf(int a[20][20][20],int stariFinale[100], char vectorCaractere[100], AFN &afn) unde:
 -> a[20][20][20] | matrice tridimensionala unde memoram starile si litera;
-> stariFinale[100]  | vector unde memoram starile finale
-> vectorCaractere[100] | literele din alfabet 
-> afn | variabile cu informatiile despre AFN

 2. Functie de cautare in vector. Se face o cautare a unei informatii intr-un vector. 

int cautare(int vector[100] ,int nr, int x) unde :
-> int x | starea pe care o cautam sa vedem daca este finala
-> vector[100] | vector in care dorim sa cautam
-> int nr | numarul de elemente din vector
 
 3. Functie pentru intersectare de stari. 
 
 int intersecatareStari(int t[20][20],char vectorCaractere[100],AFN &afn, int x, int y)
 -> int t[20][20] | matrice tabel unde linia reprezinta starea si coloanele litere, iar valoarea reprezinta tranzitiile din starea linie cu litera coloana
 -> vectorCaractere[100] | vector ce contine alfabetul
 -> AFN &afn | variabila de tip struct AFN ce contine informatii despre AFN
 -> int x | linie
 -> int y | coloana
 
 Functia returneaza un int p, ce reprezinta starile de intersectie dintre starea linie si litera coloana
 
 4. Functie pentru crearea tabelului in t[20][20]. Linia reprezinta starea, coloana reprezinta alfabetul, iar valoarea reprezinta starile in care se trece de la starea linie, cu litera coloana.  
 
 void creareTabel(int a[20][20][20],int t[20][20], char vectorCaractere[100], AFN &afn,int vectorAFD[100], int &nr)
 -> a[20][20][20] | matrice AFN
 -> t[20][20] | tabelul
 -> vectorCaractere[100] | vector ce contine alfabetul
 -> AFN &afn | variabila de tip struct AFN ce cotine informatii despre AFN
 -> vectorAFD[100] | vector in care punem starile de la fiecare stare, pentru starea 1, pune in urmatoarele " numar coloane " elemente cu cine se intersecteaza prin fiecare litera din alfabet.
 -> int &nr | numar elemente vectorAFD[100]
 
 5. Functie unde se intoarce un numar 
 int scriereInversa(int x)
 -> int x | numarul 
 
 6.  Functie de cautare a unei cifre intr-un numar.
 
 int cautareNumar(int x,int y)
 -> int x | numarul
 -> int y | cifra
 
 7. Functie pentru crearea AFD-ului. Se face in vectorAFD. 
   
 void creareAFD(int t[20][20], int vectorAFD[100], int &nr, int pozitie, AFN &afn,char vectorCaractere[100])
 -> t[20][20] | tabelul
 -> vectorAFD[100] | vector ce contine starea de plecare, urmata de starile in care se ajunge prin litera a,b, etc.
 -> int &nr | numarul de elemente din vectorAFD[100]
 -> int pozitie | pozitia pe care ne aflam in vectorAFD[100]
 -> AFN &afn | variabila de tip struct AFN ce contine informatii despre AFN
 -> vectorCaractere[100] | vector ce contine alfabetul
  
 8. Functie de citire a AFD-ului.
 
 void citireAFD(int b[20][20][20], int vectorAFD[100], int nr,char vectorCaractere[100],int stariFinaleAFD[100],int stariFinale[100],AFN afn,AFD afd)

-> b[20][20][20] | matrice unde se citeste AFD-ul dupa ce am bagat in fisierul g.
-> vectorAFD[100] | vector ce contine elementele AFD-ului
-> int nr | numarul de elemente din vectorAFD[100]
-> vectorCaractere[100] | vector ce contine alfabetul
-> stariFinaleAFD[100] | vector ce contine starile finale din AFD
-> int stariFinale[100] | stari finale AFN
-> AFN afn / AFD afd | variabile de tip struct AFN/AFD ce contin informatii despre AFN/AFD

9. Int main ()
  
  In main se apeleaza functiile
 
 Exemplu date intrare fisier :
5( numar stari ) 2 ( caractere alfabet )  1 (stari initiale ) 1 (stari finale)
5 (stare finala)
a b (litere alfabet)

starea initiala -> starea finala -> litera alfabet
1 1 a
1 2 a
1 3 a
1 4 b
1 4 a
1 5 a
1 5 b
2 3 a
2 5 b
3 2 b
4 5 a
 
 Exemplu date iesire fisier :

 
1 ( stari initiale ) 8 (nuamr stari ) 2 ( caractere alfabet)  

de la starea i la  starea j cu litera din alfabet
1 12345 a
1 45 b
12345 12345 a
12345 452 b
45 5 a
45 0 b
452 53 a
452 5 b
5 0 a
5 0 b
53 0 a
53 2 b
2 3 a
2 5 b
3 0 a
3 2 b
 
