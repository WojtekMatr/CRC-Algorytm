#include<iostream>
#include <fstream>
using namespace std;
string xorfun( string encoded , string crc)
//Bitowa operacja XOR
{
int crclen = crc.length();
for ( int i = 0 ; i <= (encoded.length() - crclen) ; ) // petla
{
// " 0 xor 0 = 0" " 1 xor 1 = 0 "
for( int j=0 ; j < crclen ; j++) // " 0 xor 1

{
encoded[i+j] = encoded[i+j] == crc[j] ? '0' : '1' ; //jesli bit z pliku i

cout<<encoded<<endl;
}
for( ; i< encoded.length() && encoded[i] != '1' ; i++) ;
}
return encoded;
}
int main()
{
string data , crc , encoded = "";
string myText;
cout<<endl<<"-----------TWORZENIE CRC --------------"<<endl;
cout<<"Podaj nazwe pliku: "<<endl;
cin>>data;
ifstream MyReadFile(data);
while (getline (MyReadFile, myText)) {
cout << myText<<endl; }
MyReadFile.close();
crc="10000010011000001000111011011011";
cout<<"Wielomian generujacy: "<<crc<<endl;
encoded += myText;
int datalen = myText.length();
int crclen = crc.length();
for(int i=1 ; i <= (crclen - 1) ; i++)
encoded += '0';
encoded = xorfun(encoded , crc);
cout<<"Cykliczny kod nadmiarowy to: ";
cout<<encoded.substr(encoded.length() - (crclen-1) )<<endl<<endl;
cout<<myText + encoded.substr(encoded.length() - crclen + 1)<<endl;
string data2;
cout<<"Podaj nazwe pliku do zapisania: "<<endl;
cin>>data2;
ofstream MyFile(data2);
MyFile <<(myText + encoded.substr(encoded.length() - crclen + 1));
MyFile.close();
cout<<endl<<"---------------SPRWDZENIE-----------------"<<endl;
cout<<"Podaj nazwe pliku z zaszyfrowana wiadomoscia: "<<endl;
string msg, data1;
cin>>data1;
ifstream MyReadFile1(data1);
getline (MyReadFile1, msg);
MyReadFile1.close();
cout<<"Zakodowana wiadomosc to: "<<endl<<msg<<endl<<endl;
msg = xorfun( msg , crc);
for( char i : msg.substr(msg.length() - crclen + 1))
if( i != '0' )
{
cout<<"Blad w komunikacji "<<endl;
return 0;
}
cout<<"Brak bledu !"<<endl;
return 0;
}