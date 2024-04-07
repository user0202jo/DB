#ifndef DATABASE_H
#define DATABASE_H

#include <string>

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void **items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
  struct Entry *entry;
  struct Array *array;
  int size;
};

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value);

// 데이터베이스를 초기화한다.
void init(Database &database);

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry);

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key);

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key);

// 데이터베이스를 해제한다.
void destroy(Database &database);



Entry *create(Type type, std::string key, void *value){
  Entry *entry = new Entry;

  entry->type = type;
  entry->key = key;
  entry->value = value;

  return entry;
}

Array* createArray(Type type) {
    Array* newArray = new Array;
    std::cout << "size: ";
    std::cin >> newArray->size;
    newArray->type = type;  
    newArray->items = new void*[newArray->size]; 

    for (int i = 0; i < newArray->size; ++i) {

        if(type != ARRAY) std::cout << "item[" << i << "]: ";
        if(type == INT){
          int* intValue = new int;
          std::cin >> *intValue;
          newArray->items[i] = intValue;
        }

        else if(type == DOUBLE){
          double* doubleValue = new double;
          std::cin >> *doubleValue;
          newArray->items[i] = doubleValue;
        }
        
        else if(type == STRING){
          std::string* stringValue = new std::string;
          std::cin >> *stringValue;
          newArray->items[i] = stringValue;
        }

        else if(type == ARRAY){
          Type artype;
          std::cout << "item[" << i << "]: type (int, double, string, array): " ;
          std::string nextType;
          std::cin >> nextType;
          if(nextType == "int") artype = INT;
          else if(nextType == "double") artype = DOUBLE;
          else if(nextType == "string") artype = STRING;
          else if(nextType == "array") artype = ARRAY;
          newArray->items[i] = createArray(artype);
        }
    }

    return newArray;
}

void init(Database &database){
  database.size = 0;
  database.entry = nullptr;
}

void add(Database &database, Entry *entry) {
    Entry *newEntries = new Entry[database.size + 1];
    for (int i = 0; i < database.size; ++i) {
        newEntries[i] = database.entry[i];
    }
    newEntries[database.size] = *entry;
    delete[] database.entry; 
    database.entry = newEntries;
    database.size++;
}

Entry *get(Database &database, std::string &key) {
    for (int i = 0; i < database.size; i++) {
        if (database.entry[i].key == key) {
            return &(database.entry[i]);
        }
    }
    return nullptr; 
}

void remove(Database &database, std::string &key){
  for(int index = 0; index < database.size; index++){
    if(database.entry[index].key == key){
      if(index == database.size - 1){
        delete &(database.entry[index]);
        --database.size;
      }

      else{
        for(int i = index; i < database.size - 1; i++){
          database.entry[i] = database.entry[i + 1];
        }
        delete &(database.entry[database.size - 1]);
        --database.size;
      }
    }
  }
}

void destroy(Database &database) {
    delete[] database.entry; 
    database.size = 0;
}

void destroyArray(Array* array) 
{
    for (int i = 0; i < array->size; ++i) 
    {
        if (array->type == INT) 
        {
            delete static_cast<int*>(array->items[i]);
        } else if (array->type == DOUBLE) {
            delete static_cast<double*>(array->items[i]);
        } else if (array->type == STRING) {
            delete static_cast<std::string*>(array->items[i]);
        } else if (array->type == ARRAY) {
            destroyArray(static_cast<Array*>(array->items[i]));
        }
    }
    delete[] array->items;
    delete array; 
}

void printArray(Array* newArray) 
{
  
    
    std::cout << "[";
    for (int i = 0; i < newArray->size; ++i) {
        if (i > 0) std::cout << ", ";
        switch (newArray->type) {
            case INT:
                std::cout << *(static_cast<int*>(newArray->items[i]));
                break;
            case DOUBLE:
                std::cout << *(static_cast<double*>(newArray->items[i]));
                break;
            case STRING:
                std::cout << *(static_cast<std::string*>(newArray->items[i]));
                break;
            case ARRAY:
                printArray(static_cast<Array*>(newArray->items[i]));
                break;
        }
    }
    std::cout << "]";
}


#endif