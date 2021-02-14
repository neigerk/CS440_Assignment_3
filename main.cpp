
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


  if (argc == 1){
    cout << "No function selected.\n -C Index Creation\n -L <ID> Lookup Record from ID\n";
  } else {
    if (strcmp(argv[1], "-C") == 0){
      CreateIndex();
    } else if(strcmp(argv[1], "-L") == 0){
      LookupRecord(argv[2]);
    } else {}
  }

  return 0;
}


void CreateIndex(){
  //This is all just test/experimentation code.  Please ignore
  //Create BucketIndex
  empOut.open("EmployeeIndex");
  empIn.open("EmployeeIndex");
  csvIn.open("Employees.csv");
  BucketIndex index = BucketIndex();
  Record newrecord;
  string line;
  while(getline(csvIn, line)){
    newrecord = Record(line);
    index.Insert(newrecord);
  }
  //Write bucketFile
  std::ofstream bucketfile;
  bucketfile.open("BucketFile");
  bucketfile << index.toString();
  bucketfile.close();

  //Close global file accessors
  empOut.close();
  empIn.close();
  csvIn.close();
  std::cout << "Employee Index successfully create.\n";
}

void LookupRecord(std::string id){
  empIn.open("EmployeeIndex");

  std::ifstream bucketread;
  bucketread.open("BucketFile");
  BucketIndex readindex = BucketIndex(&bucketread);
  std::cout << "Finding Record: " << id << "\n";
  readindex.FindRecord(id);
  bucketread.close();

  empIn.close();

}
