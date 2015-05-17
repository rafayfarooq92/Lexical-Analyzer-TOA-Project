#include <iostream>
#include <regex>
#include <fstream>
#include <string.h>
#include <tr1/memory>
using namespace std;

int main()
{

    ofstream outfile;
    ifstream infile;
    string a;
    char EOL = '\n';
    int i=0;
    infile.open("PutYourCode.txt");
    outfile.open("Formatted Code.txt");
    while(!infile.eof())
    {
          while(getline(infile,a))
          {
            outfile<<a;
             outfile<<" ";
        }


    }
    outfile<<"\r"<<endl;


}
