#include "-2_linkedlist.h"

#include <stdint.h>
#include <string.h>

#include "-0_allocator.h"

g_linkedlist_x_t *g_linkedlist_x_new(size_t element_size,
                                     g_allocator_t *allocator) {
  g_linkedlist_x_t *const result =
      (g_linkedlist_x_t *)g_alloc(allocator, sizeof(g_linkedlist_x_t));
  g_linkedlist_x_init(element_size, allocator, result);
  return result;
}

void g_linkedlist_x_init(size_t element_size, g_allocator_t *allocator,
                         g_linkedlist_x_t *out) {
  out->allocator = allocator;
  out->element_size = element_size;
  out->length = 0;
  out->head = out->tail = NULL;
}

static inline uintptr_t xor_pointers(void *a, void *b) {
  return (uintptr_t)a ^ (uintptr_t)b;
}

g_err_t g_linkedlist_x_push(g_linkedlist_x_t *self, const void *data,
                            g_linkedlist_x_node_t **out) {
  g_linkedlist_x_node_t *const node = (g_linkedlist_x_node_t *)g_alloc(
      self->allocator, sizeof(g_linkedlist_x_node_t) + self->element_size);
  if (!node) {
    return true;
  }
  memcpy(node->opaque, data, self->element_size);
  node->xor_prev_next = xor_pointers(self->tail, NULL);

  if (self->tail) {
    self->tail->xor_prev_next ^= xor_pointers(NULL, node);
  } else {
    self->head = node;
  }

  self->tail = node;
  self->length++;

  if (out) {
    *out = node;
  }

  return false;
}

void g_linkedlist_x_pop(g_linkedlist_x_t *self, void *out) {
  g_linkedlist_x_node_t *const node = self->tail;
  if (!node) {
    return;
  }

  if (out) {
    memcpy(out, node->opaque, self->element_size);
  }

  g_linkedlist_x_node_t *const prev =
      (g_linkedlist_x_node_t *)xor_pointers(NULL, (void *)node->xor_prev_next);

  if (prev) {
    prev->xor_prev_next ^= xor_pointers(node, NULL);
  } else {
    self->head = NULL;
  }

  self->tail = prev;
  self->length--;
  g_dealloc(self->allocator, node);
}

g_err_t g_linkedlist_x_unshift(g_linkedlist_x_t *self, const void *data,
                               g_linkedlist_x_node_t **out) {
  g_linkedlist_x_node_t *const node = (g_linkedlist_x_node_t *)g_alloc(
      self->allocator, sizeof(g_linkedlist_x_node_t) + self->element_size);
  if (!node) {
    return true;
  }
  memcpy(node->opaque, data, self->element_size);
  node->xor_prev_next = xor_pointers(NULL, self->head);

  if (self->head) {
    self->head->xor_prev_next ^= xor_pointers(NULL, node);
  } else {
    self->tail = node;
  }

  self->head = node;
  self->length++;

  if (out) {
    *out = node;
  }

  return false;
}

void g_linkedlist_x_shift(g_linkedlist_x_t *self, void *out) {
  g_linkedlist_x_node_t *const node = self->head;
  if (!node) {
    return;
  }

  if (out) {
    memcpy(out, node->opaque, self->element_size);
  }

  g_linkedlist_x_node_t *const next =
      (g_linkedlist_x_node_t *)xor_pointers(NULL, (void *)node->xor_prev_next);

  if (next) {
    next->xor_prev_next ^= xor_pointers(node, NULL);
  } else {
    self->tail = NULL;
  }

  self->head = next;
  self->length--;
  g_dealloc(self->allocator, node);
}

void g_linkedlist_x_deinit(g_linkedlist_x_t *self) {
  while (self->head) {
    g_linkedlist_x_shift(self, NULL);
  }
}

void g_linkedlist_x_dispose(g_linkedlist_x_t *self) {
  g_linkedlist_x_deinit(self);
  g_dealloc(self->allocator, self);
}
