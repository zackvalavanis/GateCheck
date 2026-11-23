#include <vector>
#include <string>

#define INITIAL_PQ_MAX_CAP 256

struct pq_data
{
  std::string data;
  int order;
  float priority;
};

struct pq
{
  pq_data *arr;
  int capacity;
  int size = 0;
  int next_up = 0;
};

pq *init_priority_queue();

std::string peek_pq(pq *&queue);

void insert_pq(pq *&queue, std::string text, float priority);

std::string remove_pq(pq *&queue);

bool higher(pq_data &a, pq_data &b);

void percolate_down(pq_data *arr, int n, int i);

void percolate_up(pq_data *arr, int i);

void heapify(pq_data *arr, int n);

void heapsort(pq_data *arr, int n);

void change_priority(pq *queue, int i, float newPriority);