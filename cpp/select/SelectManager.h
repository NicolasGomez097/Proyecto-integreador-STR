#ifndef SELECT_MANAGER_H
#define SELECT_MANAGER_H

#include <sys/select.h>
#include <vector>
#include "../utils/utils.h"

class SelectManager
{
private:
    fd_set readfds;
    std::vector<int> fd_set_vector;
public:
    //SelectManager();
    void addReadFD(int fd);
    int waitForSelect();
    bool wasTrigger(int fd);
    void removeFD(int fd);
};

#endif