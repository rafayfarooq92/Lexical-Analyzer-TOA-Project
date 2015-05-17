#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <regex>
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;
class Lexical_Analyzer
{
    private:
        char LeftBracketRound = '(';
        char RightBracketRound=')';

        char LeftBracketSquare = '[';
        char RightBracketSquare= ']';

        char LeftBracketCurl = '{';
        char RightBracketCurl= '}';
        ifstream infile;
        ofstream outfile;
        ofstream Ob;
        ofstream Cb;
        ofstream Key;
        ofstream Id;
        ofstream Bo;
        ofstream Str;
        ofstream Term;


        string fileName;
        int length;
        int position;


        char terminator = ';';
        string keywords[24]   = {"if","else", "while", "do", "bool", "for", "int", "float",
                                 "namespace","conio.h","iostream", "include", "std", "return", "short", "long",
                                 "char", "cin", "cout", "main", "string", "#","using","endl"};
        string identifiers[65] =  { "a","b","c","d","e","f","g","h","i","j","k","l","m","n",
                                  "o","p","q","r","s","t","u","v","w","x","y","z","_","A",
                                  "B","C","D","E","F","G","H","I","J","K","L","M","N","O",
                                  "P","Q","R","S","T","U","V","W","X","Y","Z","."};
        string stream[3] ={ "<<", ">>", "\"" };

        char BinaryOperators[15]={'+','-','*','/','=','<=','>=','==','!=','<','>','&&','||','!' };
        char Code[1000];
        int i,j,k;


    public:
        Lexical_Analyzer()
        {
            i=0;j=0;k=0;
            outfile.open("Tokens.txt");
            infile.open("Formatted Code.txt");
            Ob.open("OpeningBraces.txt");
            Key.open("Keywords.txt");
            Id.open("Identifiers.txt");
            Bo.open("Binary Operators.txt");
            Str.open("Stream.txt");
            Term.open("Terminators.txt");
            Cb.open("ClosingBraces.txt");
        }
        ~Lexical_Analyzer()
        {
            outfile.close();
        }
        void printToken(char Token,string type)
        {
            outfile<<"Token: "<<setw(2)<<"\" "<<Token<<" \""<<"---"<<type<<endl;
        }
        void printToken(string Token,string type)
        {
            outfile<<"Token: "<<setw(2)<<"\" "<<Token<<" \""<<"---"<<type<<endl;

        }
        void Read()
        {
            i=0;
            if( infile.is_open() )
                {
                   while (! infile.eof())
                    {
                        Code[i]=infile.peek();
                        Scan(Code[i]);
                        i++;
                    }

                }
        }
        bool IsKeyWord()
        {
            string MayBeKeyWord;
            int position;
            infile>>MayBeKeyWord;
            if(keyword(MayBeKeyWord))
                {
                printToken(MayBeKeyWord,"Keyword");
                position=infile.tellg();
                infile.seekg(position);
                Key<<MayBeKeyWord<<" ";
                return true;
                }
            else
            {
               if(infile.tellg()!=-1)
               {
                printToken(MayBeKeyWord,"Identifier");
                position=infile.tellg();
                infile.seekg(position);
                Id<<MayBeKeyWord<<" ";
               }

               return false;
            }

        }
        bool isTerminator(char Code)
        {
            if( Code==terminator )

                {
                    printToken(Code,"Terminator");
                    position=infile.tellg();
                    infile.seekg(position+1);
                    return true;
                }


        }
        bool isBracketOpen(char Code)
        {
            if(Code==LeftBracketCurl||Code==LeftBracketRound||Code==LeftBracketSquare)
                {

                    printToken(Code,"Open Braces");
                    position=infile.tellg();
                    infile.seekg(position+1);
                    return true;
                }
        }

        bool isBracketClose(char Code)
        {
            if(Code==RightBracketCurl||Code==RightBracketRound||Code==RightBracketSquare)

                {

                    printToken(Code,"Close Braces");
                    position=infile.tellg();
                    infile.seekg(position+1);
                    return true;
                }

        }

        bool isBinaryOperator(char Code)
        {
            for(i=0;i<15;i++)
            {
                if(Code==BinaryOperators[i])
                {

                    printToken(Code,"Binary Operator");
                    position=infile.tellg();
                    infile.seekg(position+1);
                    return true;
                }
            }
            return false;
        }
        bool isStream (string MayBeStream)
        {
            for(i=0;i<3;i++)
            {
                if(MayBeStream==stream[i])
                    return true;
            }
            return false;
        }
        bool Stream()
        {
            string MayBeStream;
            infile>>MayBeStream;
            int position;
            if(isStream(MayBeStream))
            {
                    printToken(MayBeStream,"Stream Operator");
                    position=infile.tellg();
                    infile.seekg(position);
                    Str<<MayBeStream<<" ";
                    return true;
            }
            else
                return false;

        }

        void Scan (char Code)
        {

            if(isTerminator(Code))
            {
                cout<<"This is Terminator";
                Term<<Code<<" ";
            }

            else if(isBracketOpen(Code))
            {
                cout<<"This is Bracket Open"<<endl;
                Ob<<Code<<" ";
            }
            else if(isBracketClose(Code))
            {

                cout<<"This is Bracket Close"<<endl;
                Cb<<Code<<" ";
            }
             else if(isBinaryOperator(Code))
            {
                cout<<"This is Binary Operator"<<endl;
                Bo<<Code<<" ";
            }

            else if(IsKeyWord())
                {
                cout<<"This is Keyword"<<endl;
                }

           else if(Stream())
            {
                cout<<"This is Stream"<<endl;
            }

        }


        bool keyword(string Code)
        {

           for(k=0;k<24;k++)
                {
                if(keywords[k]==Code)
                return true;
                }
           return false;

        }
        void OpenTheFile()
        {
           /* cout<<"Enter File Name"<<endl;
            cin>>fileName;
            fileName.append(".txt");
            infile.open(fileName.c_str());*/


        }
};

int main()
{
    Lexical_Analyzer scan;
    scan.OpenTheFile();
    scan.Read();
}
