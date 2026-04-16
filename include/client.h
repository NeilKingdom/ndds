#ifndef CLIENT_H
#define CLIENT_H

#include "topics.h"
#include "message.h"

typedef struct {
    DDSTopic_t *subs;
} Client_t;

// Public API
void ndds_connect();
void ndds_disconnect();
void ndds_sub_to(DDSTopic_t topic, ...);
void ndds_unsub_from(DDSTopic_t topic, ...);
void ndds_publish_msg(DDSMsg_t *msg);

#endif
