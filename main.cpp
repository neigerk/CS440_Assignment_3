
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
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
  //cout << "Hello World!";
  return 0;
}
