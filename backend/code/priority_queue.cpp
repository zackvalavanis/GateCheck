#include "priority_queue.h"

pq *init_priority_queue()
{
  pq *new_data = new pq();
  int capacity = INITIAL_PQ_MAX_CAP;
  new_data->capacity = capacity;
  new_data->arr = new pq_data[capacity];
  new_data->next_up = 0;
  new_data->size = 0;
  return new_data;
}

bool higher(pq_data &a, pq_data &b)
{
  if (a.priority < b.priority)
  {
    return true;
  }
  else if (a.priority > b.priority)
  {
    return false;
  }
  else if (a.priority == b.priority && a.order < b.order)
  {
    return true;
  }
  else if (a.priority == b.priority && a.order > b.order)
  {
    return false;
  }
  return false;
}