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

void percolate_down(pq_data *arr, int n, int i)
{
  while (i * 2 + 1 < n)
  {
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    int child = left;

    if (right < n &&
        (arr[right].priority < arr[left].priority ||
         (arr[right].priority == arr[left].priority &&
          arr[right].order < arr[left].order)))
    {
      child = right;
    }

    if (arr[i].priority < arr[child].priority || // This can be replaced by our higher function.
        (arr[i].priority == arr[child].priority &&
         arr[i].order < arr[child].order))
    {
      break;
    }
    pq_data temp = arr[i];
    arr[i] = arr[child];
    arr[child] = temp;
    i = child;
  }
}

Interval remove_pq(pq *&queue)
{
  if (queue->size < 1)
  {
    return Interval{};
  }
  Interval top_flight = peek_pq(queue);

  queue->arr[0] = queue->arr[queue->size - 1];

  queue->size--;

  percolate_down(queue->arr, queue->size, 0);

  return top_flight;
}