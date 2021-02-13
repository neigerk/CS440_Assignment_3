#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "block.h"
#include "record.h"
#include "bucket.h"

extern std::ofstream empOut;
extern std::ifstream empIn;
extern std::ifstream csvIn;
extern int blockCount;

//Create a new, empty block;
Block::Block()
  :blockNumber(0), numRecords(0), overflow(-1), bytes(0)
{}
//Read a block from the file
Block::Block(int num){
  empIn.seekg(num * BLOCKSIZE);
  char s[BLOCKSIZE];
  //std::printf("Contents of s:\n%s\n", s);
  empIn.get(s, BLOCKSIZE, '$');

  std::string str(s);
  std::stringstream ss;
  ss << str;
  std::string line;

  //std::cout << "Before stoi\n";

  getline(ss, line);
  //std::cout << num << "\n";
  blockNumber = stoi(line);
  //std::cout << "After stoi\n";

  getline(ss, line);
  overflow = stoi(line);

  getline(ss, line);
  numRecords = stoi(line);

  getline(ss, line);
  bytes = stoi(line);

  int i = 0;
  while(getline(ss, line) && i < MAXRECORDS){
    records[i] = Record(line);
    i++;
  }
  // std::cout << "Finished Reading a Block\n";

}


void Block::WriteBlock(){
  //Navigate in the file to the new block location.
  empOut.seekp(blockNumber * BLOCKSIZE);
  std::stringstream ss;
  std::string str = this->toString();
  int size = str.length() + 5 + numRecords; // return character offset, 4 from metadata, 1 from each record
  int nulls = BLOCKSIZE - size;
  //Write to stream
  ss << str;
  for (int i = 0; i < nulls; i++){
    ss << '\0';
  }
  empOut << ss.str();

/*
  if (overflow >= 0){
    Block block = Block(overflow);
    block.WriteBlock();
  }
  */
}


void Block::EmptyBlock(){
  //Navigate in the file to the new block location.
  empOut.seekp(blockNumber * BLOCKSIZE);
  std::string md = this->metadataString();
  std::stringstream ss;
  ss << md;
  int nulls = BLOCKSIZE - md.length();
  for (int i = 0; i < nulls; i++){
    ss << '\0';
  }
  empOut << ss.str();
}


//Returns 1 if the entry was added
//Returns 0 if a new overflow block was added
//Returns 2 if it was added to overflow
int Block::InsertRecord(std::string str){
  // std::cout << "Inserting a record\n";
  if (numRecords < MAXRECORDS){
    Record rec = Record(str);
    records[numRecords] = rec;
    numRecords++;
    bytes = this->toString().length() + 3;
    this->WriteBlock();
    return 1;
  } else if(overflow >= 0) {
    //std::cout << "Towards premade overflow\n";
    Block of = Block(overflow);
    of.InsertRecord(str);
  } else {
    //std::cout << "Creating new overflow\n";
    Block newOf = Block();
    newOf.blockNumber = blockCount;
    overflow = blockCount;
    blockCount++;
    // this->WriteBlock();
    newOf.InsertRecord(str);
    this->WriteBlock();

    //std::cout << "Block count: " << blockCount << "\n";
    //Can't Fit!
    return 0;
  }
}
int Block::InsertRecord(Record rec){
  if (numRecords < MAXRECORDS){
    records[numRecords] = rec;
    numRecords++;
    bytes = this->toString().length() + 3;
    this->WriteBlock();
    return 1;
  } else if(overflow >= 0) {
    //std::cout << "Towards premade overflow\n";
    Block of = Block(overflow);
    of.InsertRecord(rec);
  } else {
    //std::cout << "Creating new overflow\n";
    Block newOf = Block();
    newOf.blockNumber = blockCount;
    overflow = blockCount;
    blockCount++;
    // this->WriteBlock();
    newOf.InsertRecord(rec);
    this->WriteBlock();

    //std::cout << "Block count: " << blockCount << "\n";
    //Can't Fit!
    return 0;
  }
}
/*
int Block::InsertRecord(Record rec){
  if (numRecords < MAXRECORDS){
    records[numRecords] = rec;
    numRecords++;
    bytes = this->toString().length() + 3;
    return numRecords;
  } else if (overflow > -1){

  }
}
*/
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
  //std::cout << "Block Length: " << ss.str().length() << "\n";
  return ss.str();
  //TODO
}

void SplitRecords(Block split, Block newblock, int key, int level){
  for (int i = 0; i < split.numRecords; i++){
    std::string id = split.records[i].getId();
    std::size_t hash = Hash(id);
    int hlevelplus = hash % (int)(pow(2, level+1));
    if (hlevelplus == key){
      newblock.InsertRecord(split.records[i]);
      split.numRecords--;
      for(int j = i; j<split.numRecords; j++){
        split.records[j] = split.records[j+1];
      }
      i--;
    }
  }
  if(split.overflow > -1){
    Block over = Block(split.overflow);
    SplitRecords(over, newblock, key, level);
  }
  split.WriteBlock();
}
