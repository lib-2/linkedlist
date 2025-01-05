#ifndef G_2_LINKEDLIST_FUNCTIONS_H
#define G_2_LINKEDLIST_FUNCTIONS_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stdbool.h>
#include <stddef.h>
#endif

#include "-0/allocator_types.h"
#include "-0_common.h"

#include "linkedlist_types.h"

#ifdef __cplusplus
extern "C" {
#endif

g_2_linkedlist_s_t *g_2_linkedlist_s_new(size_t element_size,
                                         g_0_allocator_t *allocator);

void g_2_linkedlist_s_init(size_t element_size, g_0_allocator_t *allocator,
                           g_2_linkedlist_s_t *out);

/**
 * @param out optional pointer to retrieve node in list
 */
g_err_t g_2_linkedlist_s_push(g_2_linkedlist_s_t *self, const void *data,
                              g_2_linkedlist_s_node_t **out);

/**
 * @param out optional pointer to retrieve node in list
 */
g_err_t g_2_linkedlist_s_unshift(g_2_linkedlist_s_t *self, const void *data,
                                 g_2_linkedlist_s_node_t **out);

void g_2_linkedlist_s_shift(g_2_linkedlist_s_t *self, void *out);

/**
 * @param node detached node from list with same allocator, element_size
 */
void g_2_linkedlist_s_push_node(g_2_linkedlist_s_t *self,
                                g_2_linkedlist_s_node_t *node);

/**
 * @param node detached node from list with same allocator, element_size
 */
void g_2_linkedlist_s_unshift_node(g_2_linkedlist_s_t *self,
                                   g_2_linkedlist_s_node_t *node);

/**
 * @return detached node
 */
g_2_linkedlist_s_node_t *g_2_linkedlist_s_shift_node(g_2_linkedlist_s_t *self);

/**
 * @return detached node
 */
g_2_linkedlist_s_node_t *g_2_linkedlist_s_node_new(size_t element_size,
                                                   g_0_allocator_t *allocator,
                                                   const void *data);

void *g_2_linkedlist_s_node_get_addr(g_2_linkedlist_s_node_t *node);

/**
 * @param node detached node to dispose
 */
void g_2_linkedlist_s_node_dispose(g_2_linkedlist_s_node_t *node,
                                   g_0_allocator_t *allocator);

/**
 * @param node node in the list
 */
g_err_t g_2_linkedlist_s_insert_after(g_2_linkedlist_s_t *self,
                                      g_2_linkedlist_s_node_t *node,
                                      const void *data);

/**
 * @param node node in the list
 * @param to_insert detached node from list with same allocator, element_size
 */
void g_2_linkedlist_s_insert_node_after(g_2_linkedlist_s_t *self,
                                        g_2_linkedlist_s_node_t *node,
                                        g_2_linkedlist_s_node_t *to_insert);

void g_2_linkedlist_s_remove_after(g_2_linkedlist_s_t *self,
                                   g_2_linkedlist_s_node_t *node);

/**
 * @param node detached node
 */
g_2_linkedlist_s_node_t *
g_2_linkedlist_s_remove_node_after(g_2_linkedlist_s_t *self,
                                   g_2_linkedlist_s_node_t *node);

void g_2_linkedlist_s_move_all_after(g_2_linkedlist_s_t *to,
                                     g_2_linkedlist_s_t *from);

void g_2_linkedlist_s_move_all_after_node(g_2_linkedlist_s_t *to,
                                          g_2_linkedlist_s_node_t *node,
                                          g_2_linkedlist_s_t *from);

void g_2_linkedlist_s_deinit(g_2_linkedlist_s_t *self);

void g_2_linkedlist_s_dispose(g_2_linkedlist_s_t *self);

g_2_linkedlist_d_t *g_2_linkedlist_d_new(size_t element_size,
                                         g_0_allocator_t *allocator);

void g_2_linkedlist_d_init(size_t element_size, g_0_allocator_t *allocator,
                           g_2_linkedlist_d_t *out);

/**
 * @param out optional pointer to retrieve node in list
 */
g_err_t g_2_linkedlist_d_push(g_2_linkedlist_d_t *self, const void *data,
                              g_2_linkedlist_d_node_t **out);

void g_2_linkedlist_d_pop(g_2_linkedlist_d_t *self, void *out);

/**
 * @param out optional pointer to retrieve node in list
 */
g_err_t g_2_linkedlist_d_unshift(g_2_linkedlist_d_t *self, const void *data,
                                 g_2_linkedlist_d_node_t **out);

void g_2_linkedlist_d_shift(g_2_linkedlist_d_t *self, void *out);

/**
 * @param node detached node from list with same allocator, element_size
 */
void g_2_linkedlist_d_push_node(g_2_linkedlist_d_t *self,
                                g_2_linkedlist_d_node_t *node);

/**
 * @return detached node
 */
g_2_linkedlist_d_node_t *g_2_linkedlist_d_pop_node(g_2_linkedlist_d_t *self);

/**
 * @param node detached node from list with same allocator, element_size
 */
void g_2_linkedlist_d_unshift_node(g_2_linkedlist_d_t *self,
                                   g_2_linkedlist_d_node_t *node);

/**
 * @return detached node
 */
g_2_linkedlist_d_node_t *g_2_linkedlist_d_shift_node(g_2_linkedlist_d_t *self);

/**
 * @return detached node
 */
g_2_linkedlist_d_node_t *g_2_linkedlist_d_node_new(size_t element_size,
                                                   g_0_allocator_t *allocator,
                                                   const void *data);

void *g_2_linkedlist_d_node_get_addr(g_2_linkedlist_d_node_t *node);

/**
 * @param node detached node to dispose
 */
void g_2_linkedlist_d_node_dispose(g_2_linkedlist_d_node_t *node,
                                   g_0_allocator_t *allocator);

/**
 * @param node node in the list
 */
g_err_t g_2_linkedlist_d_insert_before(g_2_linkedlist_d_t *self,
                                       g_2_linkedlist_d_node_t *node,
                                       const void *data);

/**
 * @param node node in the list
 * @param to_insert detached node from list with same allocator, element_size
 */
void g_2_linkedlist_d_insert_node_before(g_2_linkedlist_d_t *self,
                                         g_2_linkedlist_d_node_t *node,
                                         g_2_linkedlist_d_node_t *to_insert);

/**
 * @param node node in the list
 */
g_err_t g_2_linkedlist_d_insert_after(g_2_linkedlist_d_t *self,
                                      g_2_linkedlist_d_node_t *node,
                                      const void *data);

/**
 * @param node node in the list
 * @param to_insert detached node from list with same allocator, element_size
 */
void g_2_linkedlist_d_insert_node_after(g_2_linkedlist_d_t *self,
                                        g_2_linkedlist_d_node_t *node,
                                        g_2_linkedlist_d_node_t *to_insert);

void g_2_linkedlist_d_remove_before(g_2_linkedlist_d_t *self,
                                    g_2_linkedlist_d_node_t *node);

/**
 * @param node detached node
 */
g_2_linkedlist_d_node_t *
g_2_linkedlist_d_remove_node_before(g_2_linkedlist_d_t *self,
                                    g_2_linkedlist_d_node_t *node);

void g_2_linkedlist_d_remove_after(g_2_linkedlist_d_t *self,
                                   g_2_linkedlist_d_node_t *node);

/**
 * @param node detached node
 */
g_2_linkedlist_d_node_t *
g_2_linkedlist_d_remove_node_after(g_2_linkedlist_d_t *self,
                                   g_2_linkedlist_d_node_t *node);

void g_2_linkedlist_d_move_all_before(g_2_linkedlist_d_t *to,
                                      g_2_linkedlist_d_t *from);

void g_2_linkedlist_d_move_all_after(g_2_linkedlist_d_t *to,
                                     g_2_linkedlist_d_t *from);

void g_2_linkedlist_d_move_all_before_node(g_2_linkedlist_d_t *to,
                                           g_2_linkedlist_d_node_t *node,
                                           g_2_linkedlist_d_t *from);

void g_2_linkedlist_d_move_all_after_node(g_2_linkedlist_d_t *to,
                                          g_2_linkedlist_d_node_t *node,
                                          g_2_linkedlist_d_t *from);

void g_2_linkedlist_d_deinit(g_2_linkedlist_d_t *self);

void g_2_linkedlist_d_dispose(g_2_linkedlist_d_t *self);

#ifdef __cplusplus
}
#endif

#endif
