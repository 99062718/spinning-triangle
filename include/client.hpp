#pragma once
#include "shmHandler.hpp"

class Client{
private:
    ShmHandler shmHandler;
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

public:
    wl_display* getDisplay();
    wl_registry* getRegistry();
    wl_shm* getShm();
    wl_compositor* getCompositor();
    xdg_wm_base* getWmBase();
    wl_surface* getWlSurface();
    xdg_surface* getXdgSurface();
    xdg_toplevel* getTopLevel();

    struct wl_buffer* drawFrame(const wl_buffer_listener* bufferListener);
};