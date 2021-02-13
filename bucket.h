#ifndef BUCKET_H
#define BUCKET_H

#include <string>

class Bucket {
public:
    Bucket();
    Bucket(int id, FILE* file_pointer);

private:
    int id;
    FILE* file_pointer;
};


#endif