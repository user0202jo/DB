#include <iostream>
#include <string>
#include "database.h"

int main(){
    std::string key;
    std::string type;
    int size;
    int value;
    Database database;
    init(database);

    std::string command;
    
    do{
        std::cout << "command (list, add, get, del, exit): ";
        std::cin >> command;

        if(command == "list"){
            for(int i = 0; i < database.size; i++){
                std::cout << database.entry[i].key << " : " << database.entry[i].value << "\n" << std::endl;
            }
        }

        else if(command == "add"){
            std::cout << "key: " ;
            std::cin >> key;

            for(int i = 0; i < database.size; i++){
                if(key == database.entry[i].key){
                 std::cout << "type(int, double, string, array): ";
                 std::cin >> type;

                 if(type == "int"){
                    std::cin >> value;
                    Entry* entry = create(INT, key, &value);
                    add(database, entry);
                 }

                 else if(type == "double"){
                   std::cin >> value;
                   Entry* entry = create(DOUBLE, key, &value);
                   add(database, entry);
                 }

                 else if(type == "string"){
                   std::cin >> value;
                   Entry* entry = create(STRING, key, &value);
                   add(database, entry);
                 }
              }
            }

            std::cout << "type(int, double, string, array): ";
            std::cin >> type;

            if(type == "int"){
                std::cin >> value;
                Entry* entry = create(INT, key, &value);
                add(database, entry);
            }

            else if(type == "double"){
                std::cin >> value;
                Entry* entry = create(DOUBLE, key, &value);
                add(database, entry);
            }

            else if(type == "string"){
                std::cin >> value;
                Entry* entry = create(STRING, key, &value);
                add(database, entry);
            }
        }

        else if(command == "get"){
            std::cin >> key;
            Entry *entry = get(database, key);
            std::cout << key << " : " << database.entry->value << std::endl;           
        }

        else if(command == "del"){
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

