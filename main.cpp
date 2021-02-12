
#include <fstream>
#include <iostream>
#include <string.h>
#include "main.h"
#include "record.h"




using namespace std;

int main(int argc, char const *argv[]) {
  //argument counts
  /*
  cout << "argc: " << argc << "\n";
  for (int i = 0; i < argc; i++){
    cout << "argv[" << i << "]:   " << argv[i] << "\n";
  }
  */

  if (argc == 1){
    cout << "No function selected.\n -C Index Creation\n -L <ID> Lookup Record from ID\n";
    CreateIndex();
  } else {
    if (strcmp(argv[1], "-C") == 0){
      CreateIndex();
    } else if(strcmp(argv[1], "-L") == 0){
      //string id;
      //string*argv[2];
      LookupRecord(argv[2]);
    } else {

    }
  }

  return 0;
}


void CreateIndex(){
  cout << "This is where the index creation happens. Not yet implemented.\n";
  ofstream outfile;
  outfile.open("EmployeeIndex");
  ifstream infile;
  infile.open("Employees.csv");
  Record testrecord = Record("11111111,Kevin Neiger,This is a bio,99999999");
  cout << "Length of record: " << testrecord.recordLength() << "\n";
  testrecord.printRecord();
  cout << testrecord.toString();
  string line;
  while(getline(infile,line)){
      outfile << line << "\n";
  }

  outfile.close();
  infile.close();
}

void LookupRecord(std::string id){
  cout << "This is where the index creation happens. Not yet implemented.\n";
}
