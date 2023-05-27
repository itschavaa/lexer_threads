//Codificado por: sAfOrAs
//Codigo fuente: Secuencia de fibonacci.
#include<iostream>
using namespace std;
 
int leedato()
{
    int n;
cin>>n;
return n;
}
int fibonacci(int n,int a,int b,int i)
{
    int c;
 
    c=a+b;
    if(c<=n)
    {
 
    cout<<c<<endl;
    a=b; b=c;
        return fibonacci(n,a,b,i+1);
    }
    else
        return 0;
}
void pideCantidad()
{
 
    int n,i=0,a=1,b=1;
    do
    {
    system("cls");
    cout<<"Ingrese la cantidad de cadena para presentar: ";
    n=leedato();
    }while(n<3);
    cout<<a<<endl;cout<<b<<endl;
    fibonacci(n,a,b,i);
 
}
 
void main()
{
 
    pideCantidad();
 
}