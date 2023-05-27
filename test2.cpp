int menor(int, int, int);
int mayor(int, int, int);
#include<iostream>
using namespace std;
int main()
{
    int a,b,c;
    cout<<"ingrese tres numeros\n";
    cin>>a>>b>>c;
    cout<<"el menor es: "<<menor(a,b,c)<<endl;
    cout<<"el mayor es: "<<mayor(a,b,c)<<endl;
    cin.ignore();return 0;
}
int menor(int a,int b,int c)
{
    if(a<b) b=a;
    if(a<c) c=a;
    if(b<c) c=b;
return c;
}
int mayor(int a,int b,int c)
{
    if(a>b) b=a;
    if(a>c) c=a;
    if(b>c) c=b;
return c;
}