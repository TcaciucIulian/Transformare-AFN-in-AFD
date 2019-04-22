#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
struct AFD
{
    int numarInitialeAfd;
    int numarFinaleAfd;
    int caracatereAlfabetAfd;
    int numarStariAfd;
};
struct AFN
{
    int  numarInitiale;
    int  numarFinale;
    int  caractereAlfabet;
    int  numarStari;
};
// citim datele din fisier si consturim matricea de adiacenta pentru AFN;
void creareGraf(int a[20][20][20],int stariFinale[100],char vectorCaractere[100], AFN &afn)
{
    // citim datele din fisier;
    ifstream f("AFN.txt");
    f>>afn.numarStari;
    f>>afn.caractereAlfabet;
    f>>afn.numarInitiale;
    f>>afn.numarFinale;
    cout<<" numar stari totale "<<afn.numarStari<<endl;
    cout<<" caracater alfabet "<<afn.caractereAlfabet<<endl;
    cout<<" numar stari initiale "<<afn.numarInitiale<<endl;
    cout<<" numar stari finale "<<afn.numarFinale<<endl;
    int nr=1;
    while(nr<=afn.numarFinale)
    {
        f>>stariFinale[nr];
        nr++;
    }
    int nr1=0;
    while(nr1<afn.caractereAlfabet)
    {
     f>>vectorCaractere[nr1];
     nr1++;
    }
    for(int i=1; i<nr; i++)
    {
        cout<<" Stare finala  "<<i<<" -> "<< stariFinale[i]<<endl;
    }
    // initializare matrice cu 0;
    for(int i=1; i<=afn.numarStari; i++)
        for(int j=1; j<=afn.numarStari; j++)
         for(int k=1;k<=afn.caractereAlfabet;k++)
        {

            a[i][j][k]=0;
        }
    // citim starile si litera ;
    int x,y;
    while(f>>x && f>>y)
    {
        char c;
        f>>c;
   //     cout<<c<<" ";
        a[x][y][c-'a'+1]=1;
        cout<< x <<" "<<y<<" "<<c-'a'+1<<" "<< c<<endl;
    }
    //afisare matrice AFN
    for(int i=1; i<=afn.numarStari; i++)
    {
        cout<<endl;
        for(int j=1; j<=afn.numarStari; j++)
         {
           cout<<endl;
           for(int k=0;k<=afn.caractereAlfabet;k++)
                cout<<a[i][j][k]<<" ";
         }
    }
    cout<<endl;
}
// cautare element x intr-un vector
int cautareVector(int vectorAFD[100], int nr, int x)
{
 for(int i=1;i<=nr;i++)
    if(vectorAFD[i]==x) return 1;
 return 0;
}
// verificare daca exista tranzitie de la x la y si o memoram
int intersecatareStari(int t[20][20],char vectorCaractere[100],AFN &afn, int x, int y)
{
  int p=0;
  p=t[x][y];
  return p;
}
// creare tabel cu stari si tranzitii ale AFN-ului necesar pentru algoritm.
void creareTabel(int a[20][20][20],int t[20][20], char vectorCaractere[100], AFN &afn,int vectorAFD[100], int &nr)
{
 int p=0;
 //matrice bidimmensionala unde linile sunt stari, coloanele alfabetul, iar valoarea din t[i][j] reprezinta starile cu care se intersecteaza cu litera j;
 // de exemplu daca de la i la j = 12 inseamna ca i cu litera vectorCaractere[j]-'a'+1 avem tranzitii in 12
 for(int i=1;i<=afn.numarStari;i++)
    for(int j=0;j<afn.caractereAlfabet;j++)
        t[i][j]=0;
 for(int i=1;i<=afn.numarStari;i++)
    for(int k=0;k<afn.caractereAlfabet;k++)
    {
     for(int j=1;j<=afn.numarStari;j++)
        if(a[i][j][vectorCaractere[k]-'a'+1]==1)
            {
              p=p*10+j;
            }
    t[i][k]=p;
    p=0;
    }
//afisare tabel
 for(int i=1;i<=afn.numarStari;i++)
 {
    cout<<endl;
    for(int k=0;k<afn.caractereAlfabet;k++)
           cout<<t[i][k]<<" ";
}
//starea de pornire in noul tabel si in continuare avem starile cu care se intersecteaza prin litera ;
cout<<endl<<endl;
nr=1;
vectorAFD[nr]=1;
for(int k=0;k<afn.caractereAlfabet;k++)
{
 nr++;
 vectorAFD[nr]=t[1][k];
}

}
// scirerea inversa a unui numar
int scriereInversa(int x)
{
 int c;
 int y=0;
 while(x%10==0) x=x/10;
 while(x!=0)
 {
    c=x%10;
    y=y*10+c;
    x=x/10;
 }
 return y;
}
// cautare cifra intr-un numar
int cautareNumar(int x,int y)
{
 while(x!=0)
 {
  int c=x%10;
  if(c==y) return 1;
  x=x/10;
 }
 return 0;
}
// Aici facem AFD-ul intr-un vector in care avem starea initiala, urmata de starile cu care se interseaza prin litere in ordine, prima litera a, a doua litera b, etc.
void creareAFD(int t[20][20], int vectorAFD[100], int &nr, int pozitie, AFN &afn,char vectorCaractere[100])
{
 //conditie de oprire
 if(pozitie>nr)  cout<<" Vector gata ";
    else
    {
       // punem in vector starea de la care pornim; exemplu : avem starea 1, o punem in vector si continuam ;
       nr++;
       vectorAFD[nr]=vectorAFD[pozitie];
       // for-ul ne ajuta sa luam pentur fiecare litera sa verificam;
       for(int i=0;i<afn.caractereAlfabet;i++)
       {
            //memoram starea de pe pozitie;
            int z=vectorAFD[pozitie];
            int lambda=0;
            // ne ajuta as luam in ordine normala, deoarece la creare este invers;
            z=scriereInversa(z);
            /*
            in urmatorul while se ia starea invers, a.i pentru starea 12 , se ia starea 1 si se verificare cu cine se intersecteaza prin litera a;
            apoi se adauga in numar. Se ia starea 2 , se verificare si daca nu mai apare in numar, se adauga. Asadar, se obtine intersectia.
            Daca de la 1 avem stare 2 3 prin litera a, si de la 2 avem cu 3 4, se va obtine 234 si se adauga in vector cu stari si tranzitii;
            */
            while(z!=0)
                {
                    int c=z%10;
                    if(intersecatareStari(t,vectorCaractere,afn,c,vectorCaractere[i]-'a')!=0)
                        if(cautareNumar(lambda,intersecatareStari(t,vectorCaractere,afn,c,vectorCaractere[i]-'a'))==0)
                            {

                            lambda=lambda*10+intersecatareStari(t,vectorCaractere,afn,c,vectorCaractere[i]-'a');
                            }

                    z=z/10;
                }
            nr++;
            vectorAFD[nr]=lambda;

      }

      // daca starea mai apare si inainte, inseamna ca s-a verificat si s-a adaugat, asadar nu mai avem de ce sa reluam pentru starea deja verificata
      while(cautareVector(vectorAFD,pozitie,vectorAFD[pozitie+1])==1 || vectorAFD[pozitie+1]==0)
         {
         pozitie++;
         }
         // cand ajungem la o pozitie+1 a carei valoare nu a fost verificata, apelam cu pozitie+1;
         if(cautareVector(vectorAFD,pozitie,vectorAFD[pozitie+1])==0)  creareAFD(t,vectorAFD,nr,pozitie+1,afn,vectorCaractere);



    }
}
//se citeste AFD si stariFinale | se afiseaza in fisierul afd.txt ;
void citireAFD(int b[20][20][20], int vectorAFD[100], int nr,char vectorCaractere[100],int stariFinaleAFD[100],int stariFinale[100],AFN afn,AFD afd)
{
ofstream g("afd.txt");

afd.numarInitialeAfd=1;
afd.numarStariAfd=nr/(afn.caractereAlfabet+1);
afd.caracatereAlfabetAfd=afn.caractereAlfabet;
g<<afd.numarInitialeAfd<<" ";
g<<afd.numarStariAfd<<" ";
g<<afd.caracatereAlfabetAfd<<" ";
g<<" \n";

int z;
int i=1;
while(i<=nr)
 {
  z=vectorAFD[i];
  while(z!=0)
  {
   int c=z%10;
 //  cout<<"c= "<<c;
   if(cautareVector(stariFinale,afn.numarFinale,c)==1) { afd.numarFinaleAfd++;
                                                         stariFinaleAFD[afd.numarFinaleAfd]=vectorAFD[i];
                                                         z=0;
                                                           }
   z=z/10;
  }
  int x=1;
  int k=i;
  while(x<=afn.caractereAlfabet)
  {
   i++;
   g<<vectorAFD[k]<<" ";
   g<<vectorAFD[i]<<" ";
   g<<vectorCaractere[x-1]<<"\n";
   x++;

  }
  i++;
  cout<<" De la starea  " << vectorAFD[i] << " se trece la starea "<< vectorAFD[i+1] <<" cu a si la starea "<<vectorAFD[i+2]<<" cu b "<<endl;
 }
cout<<endl<<" Stari finale : ";
 for(int i=1;i<=afd.numarFinaleAfd;i++) cout<<stariFinaleAFD[i]<<" ";
}

int main()
{
    int a[20][20][20]; // matrice tridimensioanala in care memoram starile si litera cu care se trece
    int stariFinale[100]; // matrice unde avem starile finale;
    char vectorCaractere[100]; // vector caractere;
    AFN afn; // variabila unde avem informatiile afn-ului;
// alfabetul peste care lucram;
    creareGraf(a,stariFinale,vectorCaractere,afn); // apelam crearea matricei tridimensionale;

    int t[20][20];
    int nr=0;
    int vectorAFD[100];
    for(int i=0;i<100;i++)
        vectorAFD[i]=0;

    creareTabel(a,t,vectorCaractere,afn,vectorAFD,nr);
    // se merge de la 2, deoarece pentur prima stare am adaugat deja in creareTabel;
    int pozitie=2;
    creareAFD(t,vectorAFD,nr,pozitie,afn,vectorCaractere);
    cout<<endl<<endl;
    for(int i=1;i<=nr;i++)
        cout<<vectorAFD[i]<<" ";
    cout<<endl;
    cout<<strlen(vectorCaractere)<<" ";
    cout<<endl;

    int b[20][20][20];
    cout<<endl<<endl;
    int stariFinaleAFD[20];
    AFD afd;
    citireAFD(b,vectorAFD,nr,vectorCaractere, stariFinaleAFD,stariFinale,afn,afd);




}



