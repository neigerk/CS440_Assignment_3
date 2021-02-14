
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
    //CreateIndex();
    empOut.close();
    empIn.close();
    csvIn.close();
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

  std::ifstream bucketread;
  bucketread.open("BucketFile");
  BucketIndex readindex = BucketIndex(&bucketread);
  readindex.FindRecord("11432123");
  bucketread.close();

  //Close global file accessors
  empOut.close();
  empIn.close();
  csvIn.close();
}

void LookupRecord(std::string id){
  empOut.open("EmployeeIndex");
  empIn.open("EmployeeIndex");
  csvIn.open("Employees.csv");
  std::ifstream bucketread;
  bucketread.open("BucketFile");
  BucketIndex readindex = BucketIndex(&bucketread);
  bucketread.close();
  std::cout << Block(0).toString();
  //readindex.FindRecord("11432123");


  empOut.close();
  empIn.close();
  csvIn.close();
  //cout << "This is where the index creation happens. Not yet implemented.\n";
}
