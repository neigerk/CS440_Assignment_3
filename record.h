#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record {
public:
  Record();
  Record(std::string id, std::string name, std::string bio, std::string manager_id);
  Record(std::string line);
  void printRecord();
  std::string toString();
  int nameLength();
  int bioLength();
  int recordLength();
  std::string getId();



private:
  std::string id;
  std::string name;
  std::string bio;
  std::string manager_id;




};


#endif
