#ifndef DATABASE_H
#define DATABASE_H

#include <string>

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void *items;
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

void init(Database &database){
  database.size = 0;
  database.entry = nullptr;
}

void add(Database &database, Entry *entry){
  Entry *newEntries = new Entry[database.size + 1];
    for(int i = 0; i < database.size; ++i){
        newEntries[i] = database.entry[i];
    }


    newEntries[database.size] = *entry;

    delete[] database.entry;


    database.entry = newEntries;


    ++database.size;
}

Entry *get(Database &database, std::string &key){
  for(int i = 0; i < database.size - 1; i++){
    if(database.entry[i].key == key){
      return &(database.entry[i]);
    }
  }
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

void destroy(Database &database){
  for(int i = 0; i < database.size - 1; i++){
        delete &(database.entry[i]);
  }
}

#endif