
#include <fstream>
#include <iostream>
#include <string.h>



using namespace std;

void CreateIndex();
void LookupRecord(string id);

int main(int argc, char const *argv[]) {
  //argument counts
  cout << "argc: " << argc << "\n";
  for (int i = 0; i < argc; i++){
    cout << "argv[" << i << "]:   " << argv[i] << "\n";
  }

  if (argc = 1){
    cout << "No function selected.\n -C Index Creation\n -L <ID> Lookup Record from ID\n";
  } else {
    cout << argv[1];
    if (strcmp(argv[1], "-C") == 0){
      CreateIndex();
    } else if(strcmp(argv[1], "-L") == 0){
      //string id;
      //string*argv[2];
      LookupRecord(argv[2]);
    } else {

    }
  }

  /*
  fstream outfile;
  outfile.open("test.txt");
  outfile << "This is a test";
  outfile.close();

  ifstream infile;
  infile.open("Employees.csv");
  string tp;
  while(getline(infile, tp)){
    cout << tp << "\n";
  }
  */
  //cout << "Hello World!";
  return 0;
}

void CreateIndex(){
  cout << "This is where the index creation happens. Not yet implemented.\n";
}

void LookupRecord(string id){
  cout << "This is where the index creation happens. Not yet implemented.\n";
}
