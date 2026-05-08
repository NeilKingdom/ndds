#ifndef SERVER_H
#define SERVER_H

#include "common.h"

#define MAX_CONNS 5
#define PORT 8282

typedef struct sockaddr_un addr_t;

static atomic_int global_tid = 1;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *manage_client_conn(void *data) {
    int ssock_fd = *(int*)data;
    int tid = atomic_fetch_add(&global_tid, 1);

    while (true) {
        // Blocking call that waits for clients to connect
        int csock_fd = accept(ssock_fd, NULL, NULL);
        if (csock_fd < 0) {
            perror("Failed to create file descriptor for client socket");
            exit(EXIT_FAILURE);
        }

        isize n;
        ClientActions_t action;
        while ((n = read(csock_fd, &action, sizeof(action))) == sizeof(action)) {
            pthread_mutex_lock(&mutex);
            switch (action) {
                case DISCONN:
                    printf("Thread %d: DISCONN received\n", tid);
                    break;
                case PUB:
                    printf("Thread %d: PUB received\n", tid);
                    break;
                case SUB:
                    printf("Thread %d: SUB received\n", tid);
                    break;
                case UNSUB:
                    printf("Thread %d: UNSUB received\n", tid);
                    break;
            }
            pthread_mutex_unlock(&mutex);

            if (action == DISCONN) {
                break;
            }
        }

        close(csock_fd);
    }

    return NULL;
}

static void run(void) {
    // Obtain socket file descriptor
    int ssock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (ssock_fd < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    addr_t server_addr = { 0 };
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, UNIX_SOCK_ADDR, sizeof(server_addr.sun_path) - 1);

    // Remove existing socket if applicable
    unlink(UNIX_SOCK_ADDR);

    // Bind address 0.0.0.0:{PORT} to our socket struct
    int result = bind(ssock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (result < 0) {
        perror("Could not bind to address");
        exit(EXIT_FAILURE);
    }

    // Put server socket in LISTEN state
    result = listen(ssock_fd, MAX_CONNS);
    if (result < 0) {
        perror("Something went wrong while waiting for connections");
        exit(EXIT_FAILURE);
    }

    // Spawn MAX_CONNS threads to manage client connections
    pthread_t threads[MAX_CONNS];
    for (int i = 0; i < MAX_CONNS; ++i) {
        pthread_create((threads + i), NULL, &manage_client_conn, (void*)&ssock_fd);
    }

    // Runs till program dies
    while (true) ;
}

#endif
