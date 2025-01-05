#include "-2_linkedlist.h"

#include <string.h>

#include "-0_allocator.h"

g_linkedlist_s_t *g_linkedlist_s_new(size_t element_size,
                                     g_allocator_t *allocator) {
  g_linkedlist_s_t *const result =
      (g_linkedlist_s_t *)g_alloc(allocator, sizeof(g_linkedlist_s_t));
  g_linkedlist_s_init(element_size, allocator, result);
  return result;
}

void g_linkedlist_s_init(size_t element_size, g_allocator_t *allocator,
                         g_linkedlist_s_t *out) {
  out->allocator = allocator;
  out->element_size = element_size;
  out->length = 0;
  out->head = out->tail = NULL;
}

g_err_t g_linkedlist_s_push(g_linkedlist_s_t *self, const void *data,
                            g_linkedlist_s_node_t **out) {
  g_linkedlist_s_node_t *const node =
      g_linkedlist_s_node_new(self->element_size, self->allocator, data);
  if (!node) {
    return true;
  }
  g_linkedlist_s_push_node(self, node);
  if (out) {
    *out = node;
  }
  return false;
}

g_err_t g_linkedlist_s_unshift(g_linkedlist_s_t *self, const void *data,
                               g_linkedlist_s_node_t **out) {
  g_linkedlist_s_node_t *const node =
      g_linkedlist_s_node_new(self->element_size, self->allocator, data);
  if (!node) {
    return true;
  }
  g_linkedlist_s_unshift_node(self, node);
  if (out) {
    *out = node;
  }
  return false;
}

void g_linkedlist_s_shift(g_linkedlist_s_t *self, void *out) {
  g_linkedlist_s_node_t *const node = g_linkedlist_s_shift_node(self);
  if (out) {
    memcpy(out, node->opaque, self->element_size);
  }
  g_dealloc(self->allocator, node);
}

void g_linkedlist_s_push_node(g_linkedlist_s_t *self,
                              g_linkedlist_s_node_t *node) {
  if (self->tail) {
    self->tail->next = node;
  }
  self->tail = node;
  if (!self->head) {
    self->head = node;
  }
  self->length++;
}

void g_linkedlist_s_unshift_node(g_linkedlist_s_t *self,
                                 g_linkedlist_s_node_t *node) {
  node->next = self->head;
  self->head = node;
  if (!self->tail) {
    self->tail = node;
  }
  self->length++;
}

g_linkedlist_s_node_t *g_linkedlist_s_shift_node(g_linkedlist_s_t *self) {
  g_linkedlist_s_node_t *const node = self->head;
  self->head = node->next;
  if (!self->head) {
    self->tail = NULL;
  }
  self->length--;
  return node;
}

g_linkedlist_s_node_t *g_linkedlist_s_node_new(size_t element_size,
                                               g_allocator_t *allocator,
                                               const void *data) {
  g_linkedlist_s_node_t *const node = (g_linkedlist_s_node_t *)g_alloc(
      allocator, sizeof(g_linkedlist_s_node_t) + element_size);
  if (!node) {
    return NULL;
  }
  node->next = NULL;
  if (data) {
    memcpy(node->opaque, data, element_size);
  }
  return node;
}

void *g_linkedlist_s_node_get_addr(g_linkedlist_s_node_t *node) {
  return (void *)node->opaque;
}

void g_linkedlist_s_node_dispose(g_linkedlist_s_node_t *node,
                                 g_allocator_t *allocator) {
  g_dealloc(allocator, node);
}

g_err_t g_linkedlist_s_insert_after(g_linkedlist_s_t *self,
                                    g_linkedlist_s_node_t *node,
                                    const void *data) {
  g_linkedlist_s_node_t *const new_node =
      g_linkedlist_s_node_new(self->element_size, self->allocator, data);
  if (!new_node) {
    return true;
  }
  g_linkedlist_s_insert_node_after(self, node, new_node);
  return false;
}

void g_linkedlist_s_insert_node_after(g_linkedlist_s_t *self,
                                      g_linkedlist_s_node_t *node,
                                      g_linkedlist_s_node_t *to_insert) {
  to_insert->next = node->next;
  node->next = to_insert;
  if (node == self->tail) {
    self->tail = to_insert;
  }
  self->length++;
}

void g_linkedlist_s_remove_after(g_linkedlist_s_t *self,
                                 g_linkedlist_s_node_t *node) {
  g_linkedlist_s_node_t *const to_remove =
      g_linkedlist_s_remove_node_after(self, node);
  g_linkedlist_s_node_dispose(to_remove, self->allocator);
}

g_linkedlist_s_node_t *
g_linkedlist_s_remove_node_after(g_linkedlist_s_t *self,
                                 g_linkedlist_s_node_t *node) {
  g_linkedlist_s_node_t *const to_remove = node->next;
  node->next = to_remove->next;
  if (to_remove == self->tail) {
    self->tail = node;
  }
  self->length--;
  return to_remove;
}

void g_linkedlist_s_move_all_after(g_linkedlist_s_t *to,
                                   g_linkedlist_s_t *from) {
  if (to->tail) {
    to->tail->next = from->head;
  } else {
    to->head = from->head;
  }
  to->tail = from->tail;
  to->length += from->length;
  from->head = from->tail = NULL;
  from->length = 0;
}

void g_linkedlist_s_move_all_after_node(g_linkedlist_s_t *to,
                                        g_linkedlist_s_node_t *node,
                                        g_linkedlist_s_t *from) {
  if (to->tail) {
    to->tail->next = node->next;
  } else {
    to->head = node->next;
  }
  to->tail = from->tail;
  to->length += from->length;
  node->next = NULL;
  from->head = from->tail = NULL;
  from->length = 0;
}

void g_linkedlist_s_deinit(g_linkedlist_s_t *self) {
  while (self->head) {
    g_linkedlist_s_shift(self, NULL);
  }
}

void g_linkedlist_s_dispose(g_linkedlist_s_t *self) {
  g_linkedlist_s_deinit(self);
  g_dealloc(self->allocator, self);
}
