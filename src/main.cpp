#define _POSIX_C_SOURCE 200112L
#include <string.h>
#include <wayland-client.h>
#include <iostream>
#include "xdg-shell-client-protocol.h"
#include "client.hpp"

static void
wl_buffer_release(void *data, struct wl_buffer *wl_buffer)
{
    /* Sent by the compositor when it's no longer using this buffer */
    wl_buffer_destroy(wl_buffer);
}

static const struct wl_buffer_listener bufferListener = {
    .release = wl_buffer_release,
};

static void xdg_surface_configure(void* data, struct xdg_surface *xdg_surface, uint32_t serial)
{
    Client* client = (Client*)data;
    xdg_surface_ack_configure(xdg_surface, serial);

    struct wl_buffer *buffer = client->drawFrame(&bufferListener);
    wl_surface_attach(client->wlSurface, buffer, 0, 0);
    wl_surface_commit(client->wlSurface);
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_configure,
};

static void
xdg_wm_base_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial)
{
    xdg_wm_base_pong(xdg_wm_base, serial);
}

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

static void
registry_global(void *data, struct wl_registry *wl_registry,
        uint32_t name, const char *interface, uint32_t version)
{
    Client* client = (Client*)data;
    if (strcmp(interface, wl_shm_interface.name) == 0) {
        client->wlShm = (wl_shm*)wl_registry_bind(
                wl_registry, name, &wl_shm_interface, 1);
    } else if (strcmp(interface, wl_compositor_interface.name) == 0) {
        client->wlCompositor = (wl_compositor*)wl_registry_bind(
                wl_registry, name, &wl_compositor_interface, 4);
    } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
        client->xdgWmBase = (xdg_wm_base*)wl_registry_bind(
                wl_registry, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(client->xdgWmBase,
                &xdg_wm_base_listener, client);
    }
}

static void
registry_global_remove(void *data,
        struct wl_registry *wl_registry, uint32_t name)
{
    /* This space deliberately left blank */
}

static const struct wl_registry_listener wl_registry_listener = {
    .global = registry_global,
    .global_remove = registry_global_remove,
};

int
main(int argc, char *argv[])
{
    std::string answer;
    int height, width;
    std::cout << "enter screen height" << std::endl;
    std::cin >> answer;
    height = std::stoi(answer);
    std::cout << "enter screen width" << std::endl;
    std::cin >> answer;
    width = std::stoi(answer);


    Client client{height, width};


    client.wlDisplay = wl_display_connect(NULL);
    client.wlRegistry = wl_display_get_registry(client.wlDisplay);
    wl_registry_add_listener(client.wlRegistry, &wl_registry_listener, &client);
    wl_display_roundtrip(client.wlDisplay);

    client.wlSurface = wl_compositor_create_surface(client.wlCompositor);
    client.xdgSurface = xdg_wm_base_get_xdg_surface(
            client.xdgWmBase, client.wlSurface);
    xdg_surface_add_listener(client.xdgSurface, &xdg_surface_listener, &client);
    client.xdgToplevel = xdg_surface_get_toplevel(client.xdgSurface);
    xdg_toplevel_set_title(client.xdgToplevel, "Example client");
    wl_surface_commit(client.wlSurface);

    while (wl_display_dispatch(client.wlDisplay)) {
        /* This space deliberately left blank */
    }

    return 0;
}