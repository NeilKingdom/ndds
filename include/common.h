#ifndef COMMON_H
#define COMMON_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <stdatomic.h>
#include <sys/socket.h>

typedef uint8_t  u8;
typedef int8_t   i8;
typedef uint16_t u16;
typedef int16_t  i16;
typedef uint32_t u32;
typedef int32_t  i32;
typedef uint64_t u64;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;
typedef size_t   usize;
typedef ssize_t  isize;

#define KB(n) (1024 * (n))
#define MB(n) (1024 * 1024 * (n))
#define GB(n) (1024 * 1024 * 1024 * (n))

#define UNIX_SOCK_ADDR "/tmp/ndds"

typedef enum {
    DISCONN,
    SUB,
    UNSUB,
    PUB
} ClientActions_t;

#endif
