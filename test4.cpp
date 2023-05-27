//Codificado por: sAfOrAs
//Codigo fuente: Suma de múltiplos de 5 y 7
#include<iostream>
using namespace std;
int main()
{
    int n=1,i=0,p=0;
     
    while(n<=40)
    {
     
        if(n%5==0) i=i+n;
            cout<<n<<endl;
        if(n%7==0) p=p+n;
        n=n+1;
     
    }
    cout<<"suma de multiplos de 5: "<<i<<endl;
    cout<<"suma de multiplos de 7: "<<p<<endl;
    cin.ignore();return 0;
}