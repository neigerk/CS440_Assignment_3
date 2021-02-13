
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include "main.h"
#include "record.h"
#include "block.h"
#include "bucket.h"
//#include "GlobalVariables.h"
using namespace std;

std::ofstream empOut;
std::ifstream empIn;
std::ifstream csvIn;
int blockCount = 0;

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
  //This is all just test/experimentation code.  Please ignore
  cout << "This is where the index creation happens. Not yet implemented.\n";
  empOut.open("EmployeeIndex");
  empIn.open("EmployeeIndex");
  csvIn.open("Employees.csv");

  //Create BucketIndex
  BucketIndex index = BucketIndex();
  //Record testrecord = Record("11111111,Kevin Neiger,This is a bio,99999999\n");
  //cout << testrecord.getId();
  //index.Insert(testrecord);
  Record newrecord;
  string line;
  while(getline(csvIn, line)){
    newrecord = Record(line);
    index.Insert(newrecord);
  }

  /*
  //Record testrecord = Record("11111111,Kevin Neiger,This is a bio,99999999");
  //cout << "Length of record: " << testrecord.recordLength() << "\n";
  //testrecord.printRecord();
  //cout << testrecord.toString();
  Block testBlock = Block(0);
  //cout << testBlock.metadataString();
  string line;
  for (int i = 0; i < MAXRECORDS; i++){
    getline(csvIn, line);
    testBlock.InsertRecord(line);
  }
  //cout << testBlock.toString();
  testBlock.WriteBlock(&empOut);
  testBlock = Block(1);
  for (int i = 0; i < MAXRECORDS; i++){
    getline(csvIn, line);
    testBlock.InsertRecord(line);
  }
  //cout << testBlock.toString();
  testBlock.WriteBlock(&empOut);

  testBlock = Block(1, &empIn);
  cout << testBlock.toString();

  //while(getline(infile,line)){
  //    outfile << line << "\n";
  //}
  //outfile.seekp(0);
  //outfile << "hi";
  //Block testBlock = Block(0);
  //testBlock.EmptyBlock(&outfile);
  //cout << testBlock.metadataString();
  //ifstream file;
  //file.open("EmployeeIndex");
  //cout <<"\n\n\n";
  //Block test2 = Block(0, &file);
*/
  empOut.close();
  empIn.close();
  csvIn.close();
}

void LookupRecord(std::string id){
  cout << "This is where the index creation happens. Not yet implemented.\n";
}
