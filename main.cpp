#include <iostream>
#include <string>
#include "database.h"

int main(){
    std::string key;
    std::string type;
    int size;
    Database database;
    init(database);

    std::string command;
    
    do{
        int countNum = 0;
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> command;

        if(command == "list"){
            for(int i = 0; i < database.size; i++){
                if(database.entry[i].type == INT){
                    std::cout << database.entry[i].key << " : " << *static_cast<int*>(database.entry[i].value) << std::endl;
                }
                
                else if(database.entry[i].type == DOUBLE){
                    std::cout << database.entry[i].key << " : " << *static_cast<double*>(database.entry[i].value) << std::endl;
                }

                else if(database.entry[i].type == STRING){
                    std::cout << database.entry[i].key << " : " << *static_cast<std::string*>(database.entry[i].value) << std::endl;
                }

                else if(database.entry[i].type == ARRAY){
                     printArray(static_cast<Array*>(database.entry[i].value));
                }
            }
        }

        else if(command == "add"){
            std::cout << "key: ";
            std::cin >> key;
            std::cout << "type(int, double, string, array): ";
            std::cin >> type;
                                                                                                                                                
            if(type == "int"){
                std::cout << "value: ";
                int value;
                std::cin >> value;
                for (int i = 0; i < database.size; ++i){
                    if (database.entry[i].key == key){
                        Entry* entry = create(INT , key, &value);
                        database.entry[i] = *entry;
                        countNum++;
                    }

                }
                if(countNum == 0){
                    Entry* entry = create(INT, key, &value);
                    add(database, entry);
                }
                
            }

            else if(type == "double"){
                std::cout << "value: ";
                double value;
                std::cin >> value;
                for (int i = 0; i < database.size; ++i){
                    if (database.entry[i].key == key){
                        Entry* entry = create(DOUBLE , key, &value);
                        database.entry[i] = *entry;
                        countNum++;
                    }
                }
                if(countNum == 0){
                    Entry* entry = create(DOUBLE, key, &value);
                    add(database, entry);
                }
            }

            else if(type == "string"){
                std::cout << "value: ";
                std::string value;
                std::cin >> value;
                for (int i = 0; i < database.size; ++i){
                    if (database.entry[i].key == key){
                        Entry* entry = create(STRING , key, &value);
                        database.entry[i] = *entry;
                        countNum++;
                    }
                }
                if(countNum == 0){
                    Entry* entry = create(STRING, key, &value);
                    add(database, entry);
                }
            }

            else if (type == "array") {
                std::cout << "value: ";
                std::cout << "type (int, double, string, array): ";
                std::cin >> type;
                if(type == "int") {
                    Array* arrayValue = createArray(INT);
                    void *value = arrayValue;
                }
                else if(type == "double"){
                    Array* arrayValue = createArray(DOUBLE);
                    void *value = arrayValue;
                } 
                else if(type == "string"){
                    Array* arrayValue = createArray(STRING);
                    void *value = arrayValue;
                } 
                else if(type == "array"){
                    Array* arrayValue = createArray(ARRAY);
                    void *value = arrayValue;
                } 
            }
        }

        else if(command == "get"){
            std::cout << "key: ";
            std::cin >> key;
            Entry *entry = get(database, key);
            if(database.entry->type == INT){
                std::cout << database.entry->key << " : " << *static_cast<int*>(database.entry->value) << std::endl;
            }
            
            else if(database.entry->type == DOUBLE){
                std::cout << database.entry->key << " : " << *static_cast<double*>(database.entry->value) << std::endl;
            } 

            else if(database.entry->type == STRING){
                std::cout << database.entry->key << " : " << *static_cast<std::string*>(database.entry->value) << std::endl;
            }
            else if(database.entry->type == ARRAY){
                printArray(static_cast<Array*>(entry->value));
                break;
            }
        }

        else if(command == "del"){
            std::cout << "key: ";
            std::cin >> key;
            remove(database, key);
        }

        else if(command == "exit"){
            destroy(database);
            break;
        }

        std::cout << "\n" << std::endl;
    }while(true);

}

