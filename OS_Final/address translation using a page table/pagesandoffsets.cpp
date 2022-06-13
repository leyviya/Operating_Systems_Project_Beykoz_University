#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;



int toInt(string bin) 
{
    int spot = 0, num = 0;
    for(int i = (bin.size()-1); i >= 0; i--){
            if(bin[i]== '1'){
                num += pow(2,spot);
            }
            spot++;
        }
    return num;
}

string toBinary(int n) 
{
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while(r.size() != 32) {r = '0' + r;}

    return r;
}

int main()
{
    ifstream address;
    int page, offset, data;
    string binary;
    address.open("address.txt"); 
	while(!address.eof())	
	{

        address >> data; 

		binary = toBinary(data); 

		page = toInt(binary.substr(16,8)); 
		offset = toInt(binary.substr(24,8)); 

        cout << data << "\t" << page << "\t" << offset << endl;
	}

    return 0;
}