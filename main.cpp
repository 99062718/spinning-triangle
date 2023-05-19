#include <stdio.h>
#include <string.h>
#include <wayland-client.h>

struct clientState{
    struct wl_compositor *compositor;
};

static void registry_handle_global(void *data, struct wl_registry *wl_registry,
		uint32_t name, const char *interface, uint32_t version)
{
    struct clientState *state = (struct clientState*)data;
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        state->compositor = (wl_compositor*)wl_registry_bind(
            wl_registry, name, &wl_compositor_interface, 4);
    }
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry,
		uint32_t name)
{
	// This space deliberately left blank
}

static const struct wl_registry_listener registry_listener = {
	.global = registry_handle_global,
	.global_remove = registry_handle_global_remove,
};


int main(int argc, char *argv[])
{
    struct wl_display *display = wl_display_connect(NULL);
    struct clientState state = {0};

    if (!display) {
        fprintf(stderr, "Failed to connect to Wayland display.\n");
        return 1;
    }
    fprintf(stderr, "Connection established!\n");

    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, &state);
	wl_display_roundtrip(display);

    struct wl_surface *surface = wl_compositor_create_surface(state.compositor);

    while (wl_display_dispatch(display) != -1) {
        break;
    }

    wl_display_disconnect(display);
    return 0;
}