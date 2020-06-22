#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fcntl.h>

std::vector<std::string> substring(std::string text);
bool isSocketOpen(int socket_fd);
int getIndexOfInt(std::vector<int> vector, int value);

#endif