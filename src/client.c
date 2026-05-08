#include "client.h"

typedef struct sockaddr_un addr_t;

ServConn_t ndds_connect(void) {
    int csock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (csock_fd < 0) {
        perror("Failed to create a client socket");
        exit(EXIT_FAILURE);
    }

    addr_t addr = { 0 };
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, UNIX_SOCK_ADDR, sizeof(addr.sun_path) - 1);

    int result = connect(csock_fd, (struct sockaddr*)&addr, sizeof(addr));
    if (result < 0) {
        perror("Failed to establish connection with the server");
        exit(EXIT_FAILURE);
    }

    return (ServConn_t){ .fd = csock_fd };
}

void ndds_disconnect(ServConn_t conn) {
    ClientActions_t data[1] = { DISCONN };
    write(conn.fd, (void*)data, sizeof(data));
}
