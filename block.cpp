#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "block.h"
#include "record.h"

//Create a new, empty block;
Block::Block(int num)
  :blockNumber(num), numRecords(0), overflow(-1), bytes(0)
{}
//Read a block from the file
Block::Block(int num, std::ifstream* file){
  file->seekg(num * BLOCKSIZE);
  char s[BLOCKSIZE];
  file->get(s, BLOCKSIZE, '$');

  //Block ret = Block(num);
  std::string str(s);
  std::stringstream ss;
  ss << str;
  std::string line;

  getline(ss, line);
  blockNumber = stoi(line);

  getline(ss, line);
  overflow = stoi(line);

  getline(ss, line);
  numRecords = stoi(line);

  getline(ss, line);
  bytes = stoi(line);

  int i = 0;
  while(getline(ss, line)){
    records[i] = Record(line);
    i++;
  }
  /*
  //std::cout << line << "\n";
  size_t found = str.find("\n");
  size_t pos = 0;
  size_t len = found - pos;
  int bn = std::stoi(str.substr(pos, len));

  pos = found + 1;
  found = str.find("\n", found+1);
  len = found - pos;
  int of = std::stoi(str.substr(pos, len));

  pos = found + 1;
  found = str.find("\n", found+1);
  len = found - pos;
  int nr = std::stoi(str.substr(pos, len));

  pos = found + 1;
  found = str.find("\n", found+1);
  len = found - pos;
  int bts = std::stoi(str.substr(pos, len));
  */



  //std::cout << bn << "\n" << of << "\n" << nr << "\n" << bts << "\n";
  //pos = found + 1;
  //found = str.find("\n", found+1);
  //len = found - pos;

  //TODO Read In Records

}
void Block::WriteBlock(std::ofstream* output){
  //Navigate in the file to the new block location.
  output->seekp(blockNumber * BLOCKSIZE);
  std::stringstream ss;
  std::string str = this->toString();
  int size = str.length();
  int nulls = BLOCKSIZE - size;
  //Write to stream
  ss << str;
  for (int i = 0; i < nulls; i++){
    ss << '\0';
  }
  *output << ss.str();
}
void Block::EmptyBlock(std::ofstream* output){
  //Navigate in the file to the new block location.
  output->seekp(blockNumber * BLOCKSIZE);
  std::string md = this->metadataString();
  std::stringstream ss;
  ss << md;
  int nulls = BLOCKSIZE - md.length();
  for (int i = 0; i < nulls; i++){
    ss << '\0';
  }
  *output << ss.str();
}
void Block::InsertRecord(std::string str){
  if (numRecords < MAXRECORDS){
    Record rec = Record(str);
    records[numRecords] = rec;
    numRecords++;
    bytes = this->toString().length() + 3;
  } else {
    std::cout << "Too many records!\n";
  }
}
std::string Block::metadataString(){
  std::stringstream ss;
  ss << blockNumber << "\n" << overflow << "\n" << numRecords << "\n" << bytes << "\n";

  return ss.str();
}
std::string Block::toString(){
  std::stringstream ss;
  ss <<  metadataString();
  for (int i = 0; i < numRecords; i++){
    ss << records[i].toString();
  }
  return ss.str();
  //TODO
}
