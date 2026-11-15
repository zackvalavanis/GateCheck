#include <vector>

struct Interval
{
  int low;
  int high;
};

struct Node
{
  Interval *i;
  int max;
  Node *left;
  Node *right;
};

class Interval_Tree
{
public:
  // Initiates the interval tree data structure
  Interval_Tree();

  // Destroys the interval tree
  ~Interval_Tree();

private:
  Node *root = nullptr;
};