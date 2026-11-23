#include <vector>

struct Interval
{
  int low;
  int high;
  std::string flight;
  std::string gate_id;
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

  void Destroy_Recursive(Node *root);

  Node *New_Node(int low, int high, std::string flight, std::string gate_id);

  void Insert_Interval(int a, int b, std::string flight, std::string gate_id);

  void Update_Maximum(Node *root);

  std::string report(Node *root);

  Node *Get_Root();

  bool Interval_Overlap(const Interval &a, const Interval &b);

  void Find_Helper(Node *node, const Interval &q, std::vector<Interval> &out);

  void All_Helper(Node *node, std::vector<Interval> &out);

  std::vector<Interval> Find_Conflicts(int low, int high, std::string flight, std::string gate_id);

  std::vector<Interval> All_Intervals();

private:
  Node *root = nullptr;
};