#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <fstream>
#include <iostream>
#include "record.h"

class Block {
public:
  Block(int num);
  //void EmptyBlock(ofstream output);
  //void InsertRecord(Record rec);
  std::string metadata();

private:

  const int headerlength = 30;
  const int recordSize = 720;
  //metadata
  int numRecords;
  bool filledRecords[5];
  int blockNumber;
  int overflow;
};

#endif
