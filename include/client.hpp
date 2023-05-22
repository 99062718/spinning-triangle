#pragma once
#include <wayland-client.h>
#include "shmHandler.hpp"

class Client{
private:
    ShmHandler shmHandler;
public:
    /* Globals */
    struct wl_display *wlDisplay;
    struct wl_registry *wlRegistry;
    struct wl_shm *wlShm;
    struct wl_compositor *wlCompositor;
    struct xdg_wm_base *xdgWmBase;
    /* Objects */
    struct wl_surface *wlSurface;
    struct xdg_surface *xdgSurface;
    struct xdg_toplevel *xdgToplevel;

    struct wl_buffer* drawFrame(const wl_buffer_listener* bufferListener);
};