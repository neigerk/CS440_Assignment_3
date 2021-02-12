#include <iostream>
#include "record.h"

using namespace std;

Record::Record()
  :id(""), name(""), bio(""), manager_id("")
{}

Record::Record(std::string id, std::string name, std::string bio, std::string manager_id)
  :id(id), name(name), bio(bio), manager_id(manager_id)
{}

Record::Record(std::string line){

  size_t found = line.find(",");
  size_t pos = 0;
  size_t len = found - pos;
  id = line.substr(pos, len);

  pos = found + 1;
  found = line.find(",", found+1);
  len = found - pos;
  name = line.substr(pos, len);

  pos = found + 1;
  found = line.find(",", found+1);
  len = found - pos;
  bio = line.substr(pos, len);

  pos = found + 1;
  len = line.length() - pos;
  manager_id = line.substr(pos, len);

}

void Record::printRecord(){
  cout << "id: " << id << "\n";
  cout << "name: " << name << "\n";
  cout << "bio: " << bio << "\n";
  cout << "manager_id: " << manager_id << "\n";
}

string Record::toString(){
  string ret = id+","+name+","+bio+","+manager_id+"\n";
  return ret;
}


int Record::nameLength(){
  return name.length();
}
int Record::bioLength(){
  return bio.length();
}
int Record::recordLength(){
  return (name.length() + bio.length() + id.length() + manager_id.length());
}
