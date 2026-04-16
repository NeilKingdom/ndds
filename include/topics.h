#ifndef TOPICS_H
#define TOPICS_H

#include "common.h"

typedef const char* DDSTopic_t;

static void register_topics(void) {
    FILE *fp = fopen("res/topics", "r");
    if (fp == NULL) {
        perror("Failed to open file topics");
        exit(EXIT_FAILURE);
    }

    // Get file size
    struct stat info = { 0 };
    fstat(fileno(fp), &info);
    usize file_sz = info.st_size;

    // Reserve memory to read contents
    u8 *bytes = malloc(file_sz + 1);
    if (bytes == NULL) {
        perror("Could not allocate enough bytes for temporary buffer");
        exit(EXIT_FAILURE);
    }
    fread(bytes, 1, file_sz, fp);
    bytes[file_sz] = '\0';

    typedef struct {
        DDSTopic_t *topics;
        usize capacity;
    } TopicsList_t;

    // TODO: Replace with global topics list
    TopicsList_t topics_list = { .capacity = 10 };
    topics_list.topics = calloc(1, sizeof(DDSTopic_t) * topics_list.capacity);
    if (topics_list.topics == NULL) {
        perror("Could not allocate enough bytes for topics list");
        exit(EXIT_FAILURE);
    }

    // Split on newline
    u32 i = 0;
    char *next = strtok((char*)bytes, "\n");
    while (next != NULL) {
        // Dynamically grow topics list if not big enough
        if (i >= topics_list.capacity) {
            topics_list.capacity += 10;
            topics_list.topics = realloc(topics_list.topics, sizeof(DDSTopic_t) * topics_list.capacity);
            if (topics_list.topics == NULL) {
                perror("Coudl not reallocate enough bytes for topics list");
                exit(EXIT_FAILURE);
            }
        }

        topics_list.topics[i++] = strdup(next);
        next = strtok(NULL, "\n");
    }

    for (i = 0; i < topics_list.capacity; ++i) {
        if (topics_list.topics[i] == NULL) {
            break;
        }
        printf("%s\n", topics_list.topics[i]);
    }

    free(topics_list.topics); // TODO: Remove
    free(bytes);
    fclose(fp);
}

#endif
