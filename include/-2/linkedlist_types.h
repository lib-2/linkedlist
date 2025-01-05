#ifndef G_2_LINKEDLIST_TYPES_H
#define G_2_LINKEDLIST_TYPES_H

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#endif

#include "-0/allocator_types.h"

typedef struct g_2_linkedlist_s_node {
  struct g_2_linkedlist_s_node *next;
  unsigned char opaque[];
} g_2_linkedlist_s_node_t;

typedef struct g_2_linkedlist_s {
  g_0_allocator_t *allocator;
  size_t element_size;
  size_t length;
  g_2_linkedlist_s_node_t *head;
  g_2_linkedlist_s_node_t *tail;
} g_2_linkedlist_s_t;

typedef struct g_2_linkedlist_d_node {
  struct g_2_linkedlist_d_node *prev;
  struct g_2_linkedlist_d_node *next;
  unsigned char opaque[];
} g_2_linkedlist_d_node_t;

typedef struct g_2_linkedlist_d {
  g_0_allocator_t *allocator;
  size_t element_size;
  size_t length;
  g_2_linkedlist_d_node_t *head;
  g_2_linkedlist_d_node_t *tail;
} g_2_linkedlist_d_t;

typedef struct g_2_linkedlist_x_node {
  uintptr_t xor_prev_next;
  unsigned char opaque[];
} g_2_linkedlist_x_node_t;

typedef struct g_2_linkedlist_x {
  g_0_allocator_t *allocator;
  size_t element_size;
  size_t length;
  g_2_linkedlist_x_node_t *head;
  g_2_linkedlist_x_node_t *tail;
} g_2_linkedlist_x_t;

#endif
