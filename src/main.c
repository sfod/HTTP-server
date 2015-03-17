#include <stdlib.h>

#include <event2/event.h>
#include <event2/http.h>

static void time_request_cb(struct evhttp_request *req, void *arg)
{
    (void) arg;
    printf("Received request for %s\n", evhttp_request_get_uri(req));
    evhttp_send_reply(req, 200, "OK", NULL);
}

int main(int argc, char **argv) {
    struct event_base *base;
    struct evhttp *http;
    struct evhttp_bound_socket *handle;

    base = event_base_new();
    if (base == NULL) {
        fprintf(stderr, "couldn't create event base\n");
        return EXIT_FAILURE;
    }

    http = evhttp_new(base);
    if (http == NULL) {
        fprintf(stderr, "couldn't create evhttp\n");
        return EXIT_FAILURE;
    }

    evhttp_set_gencb(http, time_request_cb, NULL);
    handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", 8080);
    if (handle == NULL) {
        fprintf(stderr, "couldn't bind to port 8080\n");
        return EXIT_FAILURE;
    }

    event_base_dispatch(base);

    return EXIT_SUCCESS;
}