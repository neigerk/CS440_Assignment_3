#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <fstream>
#include <iostream>
#include "record.h"

const int BLOCKSIZE = 4096;
const int MAXRECORDS = 5;
//const int recordSize = 720;
//const int headerlength = 30;

class Block {
public:
  Block(int num);
  Block(int num, std::ifstream* file);
  void EmptyBlock(std::ofstream* output);
  void WriteBlock(std::ofstream* output);
  std::string toString();
  void InsertRecord(std::string str);
  std::string metadataString();

private:

  //metadata
  int blockNumber;
  int overflow;
  int numRecords;
  int bytes;

  //Records
  Record records[MAXRECORDS];

};

//Block ReadBlock(int num, std::ifstream* file);

#endif
