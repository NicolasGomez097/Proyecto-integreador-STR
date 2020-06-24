#include "SelectManager.h"

#define THIS this->

void SelectManager::addReadFD(int fd) {
    THIS fd_set_vector.push_back(fd);
}

int SelectManager::waitForSelect() {
    FD_ZERO(&readfds);
    int max_fd = 0;
    for(int i = 0; i < THIS fd_set_vector.size(); i++) {
        FD_SET(THIS fd_set_vector[i], &readfds);
        if(max_fd < THIS fd_set_vector[i]) {
            max_fd = THIS fd_set_vector[i];
        }
    }
    max_fd++;
    return select(max_fd, &readfds, NULL, NULL, NULL);
}

bool SelectManager::wasTrigger(int fd) {
    return FD_ISSET(fd, &readfds);
}

void SelectManager::removeFD(int fd) {
    int index = getIndexOfInt(THIS fd_set_vector, fd);
    THIS fd_set_vector.erase(THIS fd_set_vector.begin() + index);
}