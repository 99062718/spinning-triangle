#pragma once
#include <wayland-client.h>
#include "shmHandler.hpp"

class Client{
private:
    ShmHandler shmHandler{};
    int width, height;
    float offset;
    uint32_t lastFrame;
public:
    /* Globals */
    struct wl_display *wlDisplay = nullptr;
    struct wl_registry *wlRegistry = nullptr;
    struct wl_shm *wlShm = nullptr;
    struct wl_compositor *wlCompositor = nullptr;
    struct xdg_wm_base *xdgWmBase = nullptr;
    /* Objects */
    struct wl_surface *wlSurface = nullptr;
    struct xdg_surface *xdgSurface = nullptr;
    struct xdg_toplevel *xdgToplevel = nullptr;

    Client(int width, int height);

    void setOffset(float newOffset);
    void setLastFrame(uint32_t newFrame);
    float getOffset();
    uint32_t getLastFrame();

    struct wl_buffer* drawFrame(const wl_buffer_listener* bufferListener);
};