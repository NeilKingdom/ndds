#ifndef MESSAGE_H
#define MESSAGE_H

#include "common.h"
#include "topics.h"

typedef struct {
    DDSTopic_t topic;
    u8 data[KB(1)];
} DDSMsg_t;

#endif
