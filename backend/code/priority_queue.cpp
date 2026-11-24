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

void percolate_up(pq_data *arr, int i)
{
  while (i > 0)
  {
    int parent_index = (i - 1) / 2;

    if (arr[i].priority >= arr[parent_index].priority)
    {
      return;
    }
    else
    {
      pq_data temp = arr[i];
      arr[i] = arr[parent_index];
      arr[parent_index] = temp;
      i = parent_index;
    }
  }
}

void insert_pq(pq *&queue, Interval flight, float priority)
{
  queue->arr[queue->size].flight = flight;
  queue->arr[queue->size].priority = priority;
  queue->arr[queue->size].order = queue->next_up;
  queue->next_up++;

  percolate_up(queue->arr, queue->size);
  queue->size++;
}

Interval peek_pq(pq *&queue)
{
  return queue->arr->flight;
}