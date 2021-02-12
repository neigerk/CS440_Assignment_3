#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "block.h"
#include "record.h"


Block::Block(int num)
  :blockNumber(num), numRecords(0), overflow(-1)
{}
/*
void Block::EmptyBlock(ofstream output){
  //Navigate in the file to the new block location.
  //output.seekp(blockNumber * 4096);

}


void Block::InsertRecord(Record rec){

}*/

std::string Block::metadata(){
  std::stringstream ss;
  ss << blockNumber << "\n" << overflow << "\n" <<numRecords << "\n";
  for (int i = 0; i < 5; i++){
    if (filledRecords[i]){
      ss << "t";
    } else {
      ss << "f";
    }
    if (i != 4){
      ss << ",";
    }
  }
  ss << "\n";
  return ss.str();
  /*
  std::string nr = itoa(numRecords);
  std::string fr;
  for (int i = 0; i < 5; i++){
    if (filledRecords[i]){
      fr += "t";
    } else {
      fr += "f";
    }
    if (i != 4){
      fr += ",";
    }
  }
  std::string bn = itoa(blockNumber);
  std::string of = itoa(overflow);
  //return nr + "/n" + fr + "/n" + bn + "/n" + of + "/n";
  */
}
