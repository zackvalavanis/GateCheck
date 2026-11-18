#include <vector>

struct Interval
{
  int low;
  int high;
};

struct Node
{
  Interval i;
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

  Node *New_Node(int low, int high);

  void Insert_Interval(int a, int b);

  void Update_Maximum(Node *root);

  std::string report(Node *root);

  Node *Get_Root();

  bool Interval_Overlap(const Interval &a, const Interval &b);

  void find_helper(Node *node, const Interval &q, std::vector<Interval> &out);

private:
  Node *root = nullptr;
};