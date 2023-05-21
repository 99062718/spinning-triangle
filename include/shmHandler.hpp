#pragma once
#include <fcntl.h>

class ShmHandler{
private:

public:
    static void randname(char *buf);

    static int create_shm_file(void);
    
    static int allocate_shm_file(size_t size);

};