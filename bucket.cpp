#include "bucket.h"

Bucket::Bucket(){
    this->id = 0;
    this->file_pointer = NULL;

}

Bucket::Bucket(int id, FILE* file_pointer){
    this->id = id;
    this->file_pointer = file_pointer;
}