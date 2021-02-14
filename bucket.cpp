#include <functional>
#include <sstream>
#include <vector>
#include <cmath>
#include "bucket.h"
#include "block.h"
#include "record.h"
extern std::ofstream empOut;
extern std::ifstream empIn;
extern std::ifstream csvIn;
extern int blockCount;

Bucket::Bucket()
{}

Bucket::Bucket(int id){
    this->id = id;
    this->blockNumber = blockCount;
    Block block = Block();
    block.blockNumber = blockCount;
    blockCount++;
    block.WriteBlock();
}

Bucket::Bucket(int id, int block){
    this->id = id;
    this->blockNumber = block;
}

void Bucket::InsertRecord(Record rec){

  Block block = Block(blockNumber);
  block.InsertRecord(rec);
}

void Bucket::FindRecord(std::string id){
  Block block = Block(blockNumber);
  block.FindRecord(id);
}

Block Bucket::getBlock(){
  return Block(blockNumber);
}
std::string Bucket::toString(){
  std::stringstream ss;
  ss << id << "\n" << blockNumber << "\n";
  return ss.str();
}

BucketIndex::BucketIndex()
  :N(1), Nlevel(1), Level(0), Next(0), totalRecords(0)
{
    it = Index.begin();
    Index.insert(it, Bucket(0));
}

BucketIndex::BucketIndex(std::ifstream* bucketfile){
  std::string line;
  getline(*bucketfile, line);
  this->totalRecords = stoi(line);
  getline(*bucketfile, line);
  this->N = stoi(line);
  getline(*bucketfile, line);
  this->Nlevel = stoi(line);
  getline(*bucketfile, line);
  this->Level = stoi(line);
  getline(*bucketfile, line);
  this->Next = stoi(line);
  int i = 0;
  while(getline(*bucketfile, line)){
    this->it = Index.begin();
    int id = stoi(line);
    getline(*bucketfile, line);
    int block = stoi(line);
    Bucket buck = Bucket(id, block);
    Index.insert(it+i, buck);
    i++;
  }
}

void BucketIndex::Insert(Record rec){
    //hash the record id
    std::size_t hashed = Hash(rec.getId());

    int power = pow(2, Level);
    int hlevel = hashed % (power);
    int powerplus = pow(2, Level + 1);
    int hlevelplus = hashed % (powerplus);
    if (hlevel >= Next && hlevel <= Nlevel){
      Bucket buck = Index[hlevel];
      //std::cout<<"Inserting into bucket: "<<hlevel<<"\n";
      buck.InsertRecord(rec);
    } else {
      Bucket buck = Index[hlevelplus];
      //std::cout<<"Inserting into bucket p: "<<hlevelplus<<"\n";
      buck.InsertRecord(rec);
    }
    totalRecords++;
    float tr = static_cast<float>(totalRecords);
    float bc = static_cast<float>(blockCount);
    float fill = tr / (bc * 5.);
    if (fill > 0.8){
      //create new Bucket
      Bucket newbuck = Bucket(Next + Nlevel);
      it = Index.begin();
      Index.insert(it + Next + Nlevel, newbuck);

      int size = Index.size();
      for(int i = 0; i < size; i++){
        Bucket buck = Index[i];
      }
      //Bucket buck = Index.pop_back();
      Block newblock = newbuck.getBlock();
      Bucket split = Index[Next];
      Block splitblock = split.getBlock();
      SplitRecords(splitblock, newblock, Next + Nlevel, Level);

      Next++;
      if(Next == Nlevel){
        Next = 0;
        N = (int)pow(2,Level);
        Level++;
        //std::cout << "NEW LEVEL!  LEVEL " << Level << "\n";
        Nlevel = (int)pow(2,Level);
      }
    }

}

void BucketIndex::FindRecord(std::string id){
  //std::cout << "Finding record(Index): " << id << "\n";
  std::size_t hashed = Hash(id);
  int power = pow(2, Level);
  int hlevel = hashed % (power);
  int powerplus = pow(2, Level + 1);
  int hlevelplus = hashed % (powerplus);
  if (hlevel >= Next && hlevel <= Nlevel){
    Bucket buck = Index[hlevel];
    //std::cout << "hlevel: " << hlevel << "\n" << buck.toString() << "\n";
    //std::cout<<"Inserting into bucket: "<<hlevel<<"\n";
    buck.FindRecord(id);
  } else {
    Bucket buck = Index[hlevelplus];
    //std::cout << "hlevelplus: " << hlevelplus << "\n" << buck.toString() << "\n";
    //std::cout<<"Inserting into bucket p: "<<hlevelplus<<"\n";
    buck.FindRecord(id);
  }
}

std::string BucketIndex::toString(){
  std::stringstream ss;
  Bucket buck;
  int length = Index.size();
  ss  << totalRecords << "\n"
      << N << "\n"
      << Nlevel << "\n"
      << Level << "\n"
      << Next  << "\n";
  for (int i = 0; i < length; i++){
    buck = Index[i];
    ss << buck.toString();
  }
  return ss.str();
}

int BucketIndex::getBlockCount(){
  return blockCount;
}

size_t Hash(std::string str){
  std::hash<std::string> hasher;
  std::size_t hashed = hasher(str);
  return hashed;
}
