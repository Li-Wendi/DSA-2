#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "hash.h"
#include <algorithm>
using namespace std;

void spellcheck(string inputfile, string outputfile, hashTable* dict){
  ifstream input_file;
	ofstream output_file;
  input_file.open(inputfile);
  output_file.open(outputfile);
    int num_line=0;
    string line="";
    bool longword = 0;
    while(getline (input_file,line)){
        line +="!";
        bool hasnumber = false;  
        int numberchar = 0;
        string word="";
      	num_line++;
        //transform(line.begin(), line.end(), line.begin(), ::tolower());
        for(int i=0; i<line.length()+1; i++){
            char c = tolower(line[i]);
            if (isdigit(c)){
                hasnumber = true;
                numberchar++;
            }
            else if (isalpha(c)|| c == '\'' || c == '-' ){
                if (numberchar+1 > 20){
                  longword = 1;
                  continue;
                }
                word+= c;
                numberchar++;  
            }
            else{
                if(longword){
                  output_file << "Long word at line "<<num_line<<", starts: "<<word<<endl;
                  longword = 0;
                }
                else if (word == ""){}
                else if (!dict->contains(word)) {
                  output_file << "Unknown word at line "<<num_line<<": "<<word<<endl;
                }
              word = "";
              numberchar = 0;
            }
        }
    }
}
void FillDict(string input_dict, hashTable* dictionary){
  string line;
  int wordcount = 0;
  ifstream dict_file;
  dict_file.open(input_dict);
    while (getline(dict_file, line)){
      std::for_each(line.begin(), line.end(), [](char & c){
        c = ::tolower(c);
      });
      dictionary->insert(line,nullptr);
    }
  dict_file.close();
}
    
int main(){
  string in_dict, in_file, out_file;
  hashTable* dict =new hashTable(100000);
  std::cout<<"Enter file name of Dictonary:"<<std::endl;
  cin >> in_dict;
  clock_t t0,t1;
  t0 = clock();
  FillDict(in_dict, dict);
  t1 = clock();
  cout<<"Total time (in seconds) to load dictionary:"<< ((float)(t1-t0))/CLOCKS_PER_SEC<<endl;

  cout<<"Enter name of input file:";
	cin>>in_file;
	cout<<"Enter name of output file:";
	cin>>out_file;
  t0 = clock();
  spellcheck(in_file, out_file, dict);
  t1 = clock();
  cout<<"Total time (in seconds) to check document:"<<((float)(t1-t0))/CLOCKS_PER_SEC<<endl;
  return 0;


}