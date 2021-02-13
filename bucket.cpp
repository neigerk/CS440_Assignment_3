#include <functional>
#include <sstream>
#include <vector>
#include <cmath>
#include "bucket.h"
#include "block.h"
#include "record.h"
//#include "GlobalVariables.h"
extern std::ofstream empOut;
extern std::ifstream empIn;
extern std::ifstream csvIn;
extern int blockCount;

/*
Bucket::Bucket(){
    this->id = 0;
    this->file_pointer = NULL;

}
*/

//Bucket::Bucket(int id, int blockNumber, std::ofstream* empOut){
Bucket::Bucket(int id){
    this->id = id;
    this->blockNumber = blockCount;
    Block block = Block();
    block.blockNumber = blockCount;
    blockCount++;
    block.WriteBlock();
}

void Bucket::InsertRecord(Record rec){
  //std::cout << "Bucket Number " << id << "Points to Block " << blockNumber << "\n";
  Block block = Block(blockNumber);
  block.InsertRecord(rec);
}

Block Bucket::getBlock(){
  return Block(blockNumber);
}
std::string Bucket::toString(){
  std::stringstream ss;
  ss << id << ", " << blockNumber << "\n";
  return ss.str();
}


//BucketIndex::BucketIndex(std::ifstream* csvIn, std::ifstream* empIn, std::ofstream*)
BucketIndex::BucketIndex()
  :N(1), Nlevel(1), Level(0), Next(0), totalRecords(0)
{
    //this->csvIn = csvIn;
    //this->empIn = empIn;
    //this->empOut = empOut;
    it = Index.begin();
    Index.insert(it, Bucket(0));
}

void BucketIndex::Insert(Record rec){
    //hash the record id
    std::size_t hashed = Hash(rec.getId());
    // std::cout << hashed << '\n';

    int power = pow(2, Level);
    int hlevel = hashed % (power);
    int powerplus = pow(2, Level + 1);
    int hlevelplus = hashed % (powerplus);
    //std::cout << "Power: " << power <<"\n";
    // std::cout << "hlevel: " << hlevel << "\n";
    // std::cout << "Powerplus: " << powerplus <<"\n";
    // std::cout << "hlevelplus: " << hlevelplus << "\n";
    if (hlevel >= Next && hlevel <= Nlevel){
      Bucket buck = Index[hlevel];
      std::cout<<"Inserting into bucket: "<<hlevel<<"\n";
      buck.InsertRecord(rec);
    } else {
      Bucket buck = Index[hlevelplus];
      std::cout<<"Inserting into bucket p: "<<hlevelplus<<"\n";
      buck.InsertRecord(rec);
    }
    totalRecords++;
    float tr = static_cast<float>(totalRecords);
    float bc = static_cast<float>(blockCount);
    float fill = tr / (bc * 5.);
    //std::cout << "Fill Level: " << fill << "\n";
    if (fill > 0.8){
      //create new Bucket

      Bucket newbuck = Bucket(Next + Nlevel);
      it = Index.begin();
      Index.insert(it + Next + Nlevel, newbuck);

      int size = Index.size();
      for(int i = 0; i < size; i++){
        Bucket buck = Index[i];
        //std::cout << buck.toString();
      }
      //Bucket buck = Index.pop_back();
      Block newblock = newbuck.getBlock();
      Bucket split = Index[Next];
      Block splitblock = split.getBlock();
      SplitRecords(splitblock, newblock, Next + Nlevel, Level);



      //move records from old blocks
        //open old block, new block number - 2^i
      //Increment N, determine if i needs to increase, increment Next
      Next++;
      if(Next == Nlevel){
        Next = 0;
        N = (int)pow(2,Level);
        Level++;
        std::cout << "NEW LEVEL!  LEVEL " << Level << "\n";
        Nlevel = (int)pow(2,Level);
      }
    }

}

int BucketIndex::getBlockCount(){
  return blockCount;
}

size_t Hash(std::string str){
  std::hash<std::string> hasher;
  std::size_t hashed = hasher(str);
  return hashed;
}
/*
void AddBucket(int id, int blockNumber, ofstream* empOut){

}
*/
