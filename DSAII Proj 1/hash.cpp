#include <iostream>
#include "hash.h"
#include <vector>
#include <string>
#include <list>

const int primelist[26] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 
24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 
12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

hashTable::hashTable(int size){
    capacity = getPrime(size);
    data.resize(capacity);  
    filled = 0;
}

bool hashTable::contains(const std::string &key){
    if (findPos(key) == -1){
        return false;
    } 
    else {
        return true;
    }
    }
int hashTable::insert(const std::string &key, void *pv){
    lowerkey = tolower(key);
    if(contains(key)){
        //std::cout << "DUPLICATE: " << key << std::endl;
        return 1;   
    }
    int index = hash(key);
    int counter = 0;
    while (data[index].isOccupied && !data[index].isDeleted) {
        index ++;
        if (counter > capacity){
        std::cout<<"OverLoaded"<<std::endl;
        }

    }
    filled++;
    if(filled > capacity>>1) 
    if(!rehash()) {
        return 2;
    }
    data[index].isOccupied=true;
    data[index].isDeleted=false;
    data[index].key=lowerkey;
    data[index].pv = pv;
    return 0;
}


int hashTable::hash(const std::string & key){
    int hashVal = 0;
    std::string testkey = key;
    for (int i = 0; i < key.length(); i++){
        testkey[i] = tolower(key[i]);
    }
    for (int i =0; i<=testkey.length(); i++){
        hashVal= 37 * hashVal+ testkey[i];
    }
    
    hashVal %= capacity;
    if (hashVal <0){
        hashVal += capacity;
    } 
    return hashVal;
}
unsigned int hashTable::getPrime(int size){
    for (int i=0; i<sizeof(primelist); i++){
        if(primelist[i]>size){
            return primelist[i];
        }
    }
}
int hashTable::findPos(const std::string &key){
  int index = hashTable::hash(key);
  while (data[index].isOccupied==true){  
    if(index==capacity-1){ //implement wrap around
      index=0;
    }
    if (data[index].key==key && data[index].isDeleted==false){
     return index;
    }
    else{
      index++;
            }
    }
  return -1;
}
void *hashTable::getPointer(const std::string &key, bool *b ){
    int position = findPos(key);
    *b = false;
    if (position == -1){
        return nullptr;
    }
    *b = true;
    return data[position].pv;
}
int hashTable::setPointer(const std::string &key, void *pv){
    int pos = findPos(key);
    if (pos == -1){
        return 1;
    data[pos].pv = pv;
    return 0;      
  }
}

bool hashTable::rehash(){
    int old_cap = capacity;
    capacity = getPrime(capacity);
    if (old_cap == capacity){
        return false;
    }
    std::vector<hashItem> temp = data;
    data.clear();
    data.resize(capacity);
    //filled = 0;
    for (int i = 0; i < old_cap; i++){
        data[hash(temp[i].key)]=temp[i];
    }
    temp.clear();
    return true;
}