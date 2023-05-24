#include <wayland-client.h>
#include <sys/mman.h>
#include <unistd.h>
#include "client.hpp"
#include "xdg-shell-client-protocol.h"

Client::Client(int height, int width):
    height(height), width(width){}

void Client::setOffset(float newOffset){
    offset = newOffset;
}

void Client::setLastFrame(uint32_t newFrame){
    lastFrame = newFrame;
}

uint32_t Client::getLastFrame(){
    return lastFrame;
}

float Client::getOffset(){
    return offset;
}

struct wl_buffer * Client::drawFrame(const wl_buffer_listener* bufferListener)
{
    int stride = width * 4;
    int size = stride * height;

    int fd = ShmHandler::allocate_shm_file(size);
    if (fd == -1) {
        return NULL;
    }

    uint32_t *data = (uint32_t*)mmap(NULL, size,
            PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        close(fd);
        return NULL;
    }

    struct wl_shm_pool *pool = wl_shm_create_pool(wlShm, fd, size);
    struct wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0,
            width, height, stride, WL_SHM_FORMAT_XRGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);

    /* Draw checkerboxed background */
    int frameOffset = (int)offset % 8;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
			if (((x + frameOffset) + (y + frameOffset) / 8 * 8) % 16 < 8)
                data[y * width + x] = 0xFF666666;
            else
                data[y * width + x] = 0xFFEEEEEE;
        }
    }

    munmap(data, size);
    wl_buffer_add_listener(buffer, bufferListener, NULL);
    return buffer;
}

