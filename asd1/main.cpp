#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

ifstream f("date.in");
ofstream g("date.out");

long long max_number,sizee;
long long v[1000000],t[1000000],v_count[1000000],c[1000000],a[1000000];
long long output[1000000];
void generator_numere()
{   ofstream g("date.in");
    long long x,len;
    len = sizee;
    srand(time(NULL));
    for (long long i = 1; i<= len; i++)
    {
       x = rand()% max_number;
        g << x << " ";
        cout << x <<" ";
    }
    g.close();
}
///Verificare
bool verifica(long long v[], long long sizee)
{
    for(long long i=1;i<sizee;i++)
            if(v[i]>v[i+1])
                return 0;
    return 1;

}
///Bubble Sort
void BubbleSort(long long v[], long long sizee)
{
    long long i,j,aux;
    for(long long i=1; i<=sizee-1; i++)
        for(long long j=i+1; j<= sizee; j++)
            if (v[i]>v[j])
             {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
             }
}
///Radix Sort----------------------------------------------------------------------------------------
int getMax(long long v[], long long sizee)
{
    int maxx = v[0];
    for(long long i=1;i < sizee;i++)
        if(v[i]>maxx)
            maxx = v[i];
    return maxx;
}
void countsort(long long v[], long long sizee,long long k)
{
    int maxim = 10;
    long long c[maxim];
    for(long long i=0;i<maxim;++i)
        c[i]=0;
    for(long long i=0;i<sizee;i++)
        c[(v[i]/k)%10]++;
    for(long long i=1;i<maxim;i++)
        c[i]+=c[i-1];
    for(long long i=sizee-1;i>=0;i--)
    {
        output[c[(v[i]/k)%10]-1] = v[i];
        c[(v[i]/k)%10]--;
    }
    for(long long i=0;i<sizee;i++)
        v[i]=output[i];
}
void RadixSort( long long v[], long long sizee)
{
    long long m = getMax(v,sizee);
    for(int k = 1; m/k > 0; k = k*10)
        countsort(v,sizee,k);
}
///COUNT SORT
void CountSort(long long v[],long long v_final[], long long sizee)
{
    long long maxim = getMax(v,sizee);

    for(long long i=0; i< maxim; i++)
        c[i] = 0;
    for(long long i=1; i<=sizee;i++)
        c[v[i]]++;
    for(long long i=1; i <= maxim; i++)
        c[i] += c[i-1];
    for(long long i = sizee; i>=1; i--)
    {
        v_final[c[v[i]]] = v[i];
        c[v[i]] = c[v[i]]-1;
    }
}
/// Quick Sort
int partitie(long long v[], long long st, long long dr)
{
    long long aux;
    long long piv = v[dr];
    long  long i = (st - 1);
    for ( long long j = st; j <= dr - 1; j++)
        if(v[j]<piv)
        {
         i++;
         aux = a[i];
         a[i] = a[j];
         a[j] = aux;
        }
    aux = v[i+1];
    v[i+1] = v[dr];
    v[dr] = aux;
    return(i+1);
}
void QuickSort(long long v[], long long st,long long dr)
{
    if(st<dr)
    {
        long long k = partitie(v,st,dr);
        QuickSort(v,st,k-1);
        QuickSort(v,k+1,dr);
    }
}
/// Merge Sort
void MergeSort(long long v[], long long  st, long long dr)
{
    if(st<dr)
    {
        long long m = (st+dr)/2;
        MergeSort(v,st,m);
        MergeSort(v,m+1,dr);
        //Interclasare:
        long long i = st, j = m+1, k = 0;
        while (i <= m && j<= dr)
            if(v[i] < v[j])
                t[++k] = v[i++];
            else
                t[++k] = v[j++];
        while(i <= m)
            t[++k] = v[i++];
        while(j <= dr)
            t[++k] = v[j++];
        for(i = st, j=1; i<=dr; i++, j++)
            v[i] = t[j];
    }
}

void citire(){
    for(long long i = 1;i<=sizee;i++)
        f>>v[i];
}
void afisare(long long v[],long long sizee)
{
    for(long long i=1;i<=sizee;i++)
        cout<< v[i]<< " ";

}
long long n;
double start,stop,start1,stop1,start2,stop2,start3,stop3,start4,stop4,duration;
int main()
{   cin>>max_number>>sizee;
    n = sizee;
    generator_numere();
    citire();
    for (int i = 1;i<=n;i++)
        a[i] = v[i];
    auto start = high_resolution_clock::now();
    BubbleSort(a,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    if(verifica(a,n)){
        g<<"Vectorul a fost sortat cu BubbleSort.";
        g<<" Timpul de executie este:"<<duration.count()<<endl;
    }
    else
        g<<"BubbleSort nu sorteaza."<<endl;
    for (long long i = 0;i<n;i++)
        a[i] = v[i];
    auto start1 = high_resolution_clock::now();
    RadixSort(a,n);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1-start1);
    if(verifica(a,n)){
        g<<"Vectorul a fost sortat cu RadixSort.";
        g<<" Timpul de executie este: "<<duration.count()<<endl;
    }
    else
        g<<"RadixSort nu sorteaza."<<endl;
   for (long long i = 1;i<=n;i++)
        a[i] = v[i];
    auto start2 = high_resolution_clock::now();
    CountSort(a,v_count,n);
    auto stop2= high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2-start2);
    if(verifica(v_count,n)){
        g<<"Vectorul a fost sortat cu CountSort.";
        g<<" Timpul de executie este: "<<duration.count()<<endl;
    }
    else
        g<<"CountSort nu sorteaza."<<endl;
    for (long long i = 1;i<=n;i++)
        a[i] = v[i];
    auto start3 = high_resolution_clock::now();
    QuickSort(a,1,n);
    auto stop3= high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3-start3);
    if(verifica(a,n)){
        g<<"Vectorul a fost sortat cu QuickSort.";
        g<<" Timpul de executie este: "<<duration.count()<<endl;
    }
    else
        g<<"QuickSort nu sorteaza."<<endl;
     for (long long i = 1;i<=n;i++)
        a[i] = v[i];
    auto start4 = high_resolution_clock::now();
    MergeSort(a,1,n);
    auto stop4= high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(stop4-start4);
    if(verifica(a,n)){
        g<<"Vectorul a fost sortat cu MergeSort.";
        g<<" Timpul de executie este: "<<duration.count()<<endl;
    }
    else
        g<<"MergeSort nu sorteaza."<<endl;
    return 0;
}
