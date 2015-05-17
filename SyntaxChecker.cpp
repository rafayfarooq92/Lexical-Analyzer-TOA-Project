#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <regex>
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

class Syntax
{
        private:
            ifstream Ob;
            ifstream Cb;
            ifstream Key;
            ifstream Id;
            ifstream Bo;
            ifstream Str;
            ifstream Term;
            int left,right;
            char a;
            int i;
            int Hash;
            int include;
            int main;
            int use,name,st,ter;
            string StoringKeyWords;
        public:
            Syntax()
            {
            Ob.open("OpeningBraces.txt");
            Key.open("Keywords.txt");
            Id.open("Identifiers.txt");
            Bo.open("Binary Operators.txt");
            Str.open("Stream.txt");
            Term.open("Terminators.txt");
            Cb.open("ClosingBraces.txt");
            left=0;
            right=0;
            Hash=0;
            use=0;
            name=0;
            st=0;
            include=0;
            i=0;
            ter=0;
            main=0;
            }
            ~Syntax()
            {

            }
            bool IsBalanceBraces()
            {
                Ob.clear();
                Ob.seekg(ios::beg);

                while (!Ob.eof())
                {
                    while(Ob>>a!=NULL)
                        left++;
                }
                Cb.clear();
                Cb.seekg(ios::beg);

                while (!Cb.eof())
                {
                    while(Cb>>a!=NULL)
                        right++;
                }
                if(right==left)
                    return true;
                else
                    return false;
            }
            void SyntaxChecker()
            {
                CheckLibrarySyntax();
                CheckMain();
                CheckNameSpace();
                CheckBraces();
            }
            void CheckNameSpace()
            {
                Key.clear();
                Key.seekg(ios::beg);
                while (Key >> StoringKeyWords)
                {
                if(StoringKeyWords=="using")
                use++;
                }
                Key.clear();
                Key.seekg(ios::beg);
                while (Key >> StoringKeyWords)
                {
                if(StoringKeyWords=="namespace")
                name++;
                }
                Key.clear();
                Key.seekg(ios::beg);
                while (Key >> StoringKeyWords)
                {
                if(StoringKeyWords=="std")
                st++;
                }

                if(use==name&&name==st&&use==st)
                    cout<<"NameSpace is Correctly Included"<<endl;
                else
                    cout<<"Error:NameSpace is not properly Included"<<endl;


            }
            void CheckMain()
            {
                Key.clear();
                Key.seekg(0, ios::beg);
                while (Key >> StoringKeyWords)
                if(StoringKeyWords=="main")
                main++;
                if(main==1)
                    cout<<"Main is Correctly Included"<<endl;
                else
                    cout<<"Error:Main is not properly Included"<<endl;
            }
            void CheckBraces()
            {
                if( IsBalanceBraces() )
                    cout<<"Paranthesis are matched"<<endl;
                else
                    cout<<"Error:Paranthesis are Not Balanced"<<endl;
            }
            void CheckLibrarySyntax()
            {
                Key.clear();

                Key.seekg(ios::beg);
                while (Key >> StoringKeyWords)
                {
                if(StoringKeyWords=="#")
                Hash++;
                }
                 Key.clear();
                Key.seekg(ios::beg);

                while (Key >> StoringKeyWords)
                {
                if(StoringKeyWords=="include")
                include++;
                }
                if(Hash==include)
                    cout<<"Libraries are properly included"<<endl;
                else
                    cout<<"Error:Libraries are not properly included"<<endl;
            }

};
int main()
{
    Syntax syn;
    syn.SyntaxChecker();
}
