#ifndef BUCKET_H
#define BUCKET_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "record.h"
#include "block.h"


class Bucket {
public:
    //Bucket();
    //Bucket(int id, int blockNumber, std::ofstream* empOut);
    Bucket();
    Bucket(int id);
    Bucket(int id, int block);
    void InsertRecord(Record rec);
    void FindRecord(std::string id);
    Block getBlock();
    std::string toString();
private:
    int id;
    int blockNumber;
};

class BucketIndex {
public:
    BucketIndex();
    BucketIndex(std::ifstream* bucketfile);
    //BucketIndex(std::ifstream* csvIn, std::ifstream* empIn, std::ofstream* empOut);
    void Insert(Record rec);
    void FindRecord(std::string id);
    std::string toString();
    int getBlockCount();
    //void AddBucket(int id, int blockNumber, ofstream* empOut);
private:
    //std::ifstream* csvIn;
    //std::ifstream* empIn;
    //std::ofstream* empOut;
    int totalRecords;
    //Algorithm
    int N;
    int Nlevel;
    int Level;
    int Next;
    std::vector<Bucket>::iterator it;
    std::vector <Bucket> Index;

};
size_t Hash(std::string str);
#endif
