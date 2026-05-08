#ifndef CLIENT_H
#define CLIENT_H

#include "topics.h"
#include "message.h"

// TODO:
// - Create Actions enum corresponding to each public API
//   - { CONN, DISCONN, SUB, UNSUB, PUB }
//   - These are used in the payload sent to the server
// - ndds_connect returns some kind of ctx containing sock fd used in other API calls
// - We invoke write(ctx.sock_fd) and send { Action + [payload] }

typedef struct {
    DDSTopic_t *subs;
} Client_t;

typedef struct {
    int fd;
} ServConn_t;

// Public API
ServConn_t ndds_connect(void);
void ndds_disconnect(ServConn_t conn);
void ndds_sub_to(DDSTopic_t topic, ...);
void ndds_unsub_from(DDSTopic_t topic, ...);
void ndds_publish_msg(DDSMsg_t *msg);

#endif
