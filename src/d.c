#include "-2_linkedlist.h"

#include <string.h>

#include "-0_allocator.h"

g_linkedlist_d_t *g_linkedlist_d_new(size_t element_size,
                                     g_allocator_t *allocator) {
  g_linkedlist_d_t *const result =
      (g_linkedlist_d_t *)g_alloc(allocator, sizeof(g_linkedlist_d_t));
  g_linkedlist_d_init(element_size, allocator, result);
  return result;
}

void g_linkedlist_d_init(size_t element_size, g_allocator_t *allocator,
                         g_linkedlist_d_t *out) {
  out->allocator = allocator;
  out->element_size = element_size;
  out->length = 0;
  out->head = out->tail = NULL;
}

g_err_t g_linkedlist_d_push(g_linkedlist_d_t *self, const void *data,
                            g_linkedlist_d_node_t **out) {
  g_linkedlist_d_node_t *const node =
      g_linkedlist_d_node_new(self->element_size, self->allocator, data);
  if (!node) {
    return true;
  }
  g_linkedlist_d_push_node(self, node);
  if (out) {
    *out = node;
  }
  return false;
}

void g_linkedlist_d_pop(g_linkedlist_d_t *self, void *out) {
  g_linkedlist_d_node_t *const node = g_linkedlist_d_pop_node(self);
  if (out) {
    memcpy(out, node->opaque, self->element_size);
  }
  g_dealloc(self->allocator, node);
}

g_err_t g_linkedlist_d_unshift(g_linkedlist_d_t *self, const void *data,
                               g_linkedlist_d_node_t **out) {
  g_linkedlist_d_node_t *const node =
      g_linkedlist_d_node_new(self->element_size, self->allocator, data);
  if (!node) {
    return true;
  }
  g_linkedlist_d_unshift_node(self, node);
  if (out) {
    *out = node;
  }
  return false;
}

void g_linkedlist_d_shift(g_linkedlist_d_t *self, void *out) {
  g_linkedlist_d_node_t *const node = g_linkedlist_d_shift_node(self);
  if (out) {
    memcpy(out, node->opaque, self->element_size);
  }
  g_dealloc(self->allocator, node);
}

void g_linkedlist_d_push_node(g_linkedlist_d_t *self,
                              g_linkedlist_d_node_t *node) {
  node->prev = self->tail;
  if (self->tail) {
    self->tail->next = node;
  }
  self->tail = node;
  if (!self->head) {
    self->head = node;
  }
  self->length++;
}

g_linkedlist_d_node_t *g_linkedlist_d_pop_node(g_linkedlist_d_t *self) {
  g_linkedlist_d_node_t *const node = self->tail;
  if (node->prev) {
    node->prev->next = NULL;
  } else {
    self->head = NULL;
  }
  self->tail = node->prev;
  self->length--;
  return node;
}

void g_linkedlist_d_unshift_node(g_linkedlist_d_t *self,
                                 g_linkedlist_d_node_t *node) {
  node->next = self->head;
  if (self->head) {
    self->head->prev = node;
  }
  self->head = node;
  if (!self->tail) {
    self->tail = node;
  }
  self->length++;
}

g_linkedlist_d_node_t *g_linkedlist_d_shift_node(g_linkedlist_d_t *self) {
  g_linkedlist_d_node_t *const node = self->head;
  if (node->next) {
    node->next->prev = NULL;
  } else {
    self->tail = NULL;
  }
  self->head = node->next;
  self->length--;
  return node;
}

g_linkedlist_d_node_t *g_linkedlist_d_node_new(size_t element_size,
                                               g_allocator_t *allocator,
                                               const void *data) {
  g_linkedlist_d_node_t *const node = (g_linkedlist_d_node_t *)g_alloc(
      allocator, sizeof(g_linkedlist_d_node_t) + element_size);
  if (!node) {
    return NULL;
  }
  node->next = node->prev = NULL;
  if (data) {
    memcpy(node->opaque, data, element_size);
  }
  return node;
}

void *g_linkedlist_d_node_get_addr(g_linkedlist_d_node_t *node) {
  return (void *)node->opaque;
}

void g_linkedlist_d_node_dispose(g_linkedlist_d_node_t *node,
                                 g_allocator_t *allocator) {
  g_dealloc(allocator, node);
}

g_err_t g_linkedlist_d_insert_before(g_linkedlist_d_t *self,
                                     g_linkedlist_d_node_t *node,
                                     const void *data) {
  g_linkedlist_d_node_t *const new_node =
      g_linkedlist_d_node_new(self->element_size, self->allocator, data);
  if (!new_node) {
    return true;
  }
  g_linkedlist_d_insert_node_before(self, node, new_node);
  return false;
}

void g_linkedlist_d_insert_node_before(g_linkedlist_d_t *self,
                                       g_linkedlist_d_node_t *node,
                                       g_linkedlist_d_node_t *to_insert) {
  to_insert->next = node;
  to_insert->prev = node->prev;
  if (node->prev) {
    node->prev->next = to_insert;
  } else {
    self->head = to_insert;
  }
  node->prev = to_insert;
  self->length++;
}

g_err_t g_linkedlist_d_insert_after(g_linkedlist_d_t *self,
                                    g_linkedlist_d_node_t *node,
                                    const void *data) {
  g_linkedlist_d_node_t *const new_node =
      g_linkedlist_d_node_new(self->element_size, self->allocator, data);
  if (!new_node) {
    return true;
  }
  g_linkedlist_d_insert_node_after(self, node, new_node);
  return false;
}

void g_linkedlist_d_insert_node_after(g_linkedlist_d_t *self,
                                      g_linkedlist_d_node_t *node,
                                      g_linkedlist_d_node_t *to_insert) {
  to_insert->prev = node;
  to_insert->next = node->next;
  if (node->next) {
    node->next->prev = to_insert;
  } else {
    self->tail = to_insert;
  }
  node->next = to_insert;
  self->length++;
}

void g_linkedlist_d_remove_before(g_linkedlist_d_t *self,
                                  g_linkedlist_d_node_t *node) {
  g_linkedlist_d_node_t *const to_remove =
      g_linkedlist_d_remove_node_before(self, node);
  g_linkedlist_d_node_dispose(to_remove, self->allocator);
}

void g_linkedlist_d_remove_after(g_linkedlist_d_t *self,
                                 g_linkedlist_d_node_t *node) {
  g_linkedlist_d_node_t *const to_remove =
      g_linkedlist_d_remove_node_after(self, node);
  g_linkedlist_d_node_dispose(to_remove, self->allocator);
}

g_linkedlist_d_node_t *
g_linkedlist_d_remove_node_before(g_linkedlist_d_t *self,
                                  g_linkedlist_d_node_t *node) {
  g_linkedlist_d_node_t *const to_remove = node->prev;
  if (to_remove->prev) {
    to_remove->prev->next = node;
  } else {
    self->head = node;
  }
  node->prev = to_remove->prev;
  self->length--;
  return to_remove;
}

g_linkedlist_d_node_t *
g_linkedlist_d_remove_node_after(g_linkedlist_d_t *self,
                                 g_linkedlist_d_node_t *node) {
  g_linkedlist_d_node_t *const to_remove = node->next;
  if (to_remove->next) {
    to_remove->next->prev = node;
  } else {
    self->tail = node;
  }
  node->next = to_remove->next;
  self->length--;
  return to_remove;
}

void g_linkedlist_d_move_all_before(g_linkedlist_d_t *to,
                                    g_linkedlist_d_t *from) {
  if (to->head) {
    from->tail->next = to->head;
    to->head->prev = from->tail;
  } else {
    to->tail = from->tail;
  }
  to->head = from->head;
  to->length += from->length;
  from->head = from->tail = NULL;
  from->length = 0;
}

void g_linkedlist_d_move_all_before_node(g_linkedlist_d_t *to,
                                         g_linkedlist_d_node_t *node,
                                         g_linkedlist_d_t *from) {
  if (node->prev) {
    from->tail->next = node;
    node->prev->next = from->head;
    from->head->prev = node->prev;
  } else {
    to->head = from->head;
  }
  node->prev = from->tail;
  to->length += from->length;
  from->head = from->tail = NULL;
  from->length = 0;
}

void g_linkedlist_d_move_all_after(g_linkedlist_d_t *to,
                                   g_linkedlist_d_t *from) {
  if (to->tail) {
    to->tail->next = from->head;
    from->head->prev = to->tail;
  } else {
    to->head = from->head;
  }
  to->tail = from->tail;
  to->length += from->length;
  from->head = from->tail = NULL;
  from->length = 0;
}

void g_linkedlist_d_move_all_after_node(g_linkedlist_d_t *to,
                                        g_linkedlist_d_node_t *node,
                                        g_linkedlist_d_t *from) {
  if (node->next) {
    from->head->prev = node;
    from->tail->next = node->next;
    node->next->prev = from->tail;
  } else {
    to->tail = from->tail;
  }
  node->next = from->head;
  to->length += from->length;
  from->head = from->tail = NULL;
  from->length = 0;
}

void g_linkedlist_d_deinit(g_linkedlist_d_t *self) {
  while (self->head) {
    g_linkedlist_d_shift(self, NULL);
  }
}

void g_linkedlist_d_dispose(g_linkedlist_d_t *self) {
  g_linkedlist_d_deinit(self);
  g_dealloc(self->allocator, self);
}
