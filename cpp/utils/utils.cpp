#include "utils.h"

std::vector<std::string> substring(std::string text) {
    std::vector<std::string> strings;
    std::string aux = "";
    for(int i = 0; i < text.length(); i++) {
        if(text[i] == ',') {
            strings.push_back(aux);
            aux = "";
        } else {
            aux.push_back(text[i]);
        }
    }
    if(aux.compare("") != 0) {
        strings.push_back(aux);
    }
    return strings;
}

bool isSocketOpen(int socket_fd) { 
    return fcntl(socket_fd, F_GETFL) != -1;
} 

int getIndexOfInt(std::vector<int> vector, int value) {
    for(int i = 0; i < vector.size(); i++) {
        if(vector[i] == value){
            return i;
        }
    } 
    return -1;
} 