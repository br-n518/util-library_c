#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

#include "node.h"

#define queue_push(q_pp,data_p) node_push_back(q_pp,data_p)
#define queue_pop(q_pp) node_pop(q_pp,*q_pp)

#define stack_push(s_pp,data_p) node_push_front(q_pp,data_p)
#define stack_pop(s_pp) node_pop(s_pp,*s_pp)

#endif

