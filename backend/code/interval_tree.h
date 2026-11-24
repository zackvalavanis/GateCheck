#pragma once
#include <vector>
#include <string>

struct Interval
{
  int low;
  int high;
  std::string airport;
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
  Interval_Tree();

  ~Interval_Tree();

  void Insert_Interval(int a, int b, std::string airport, std::string flight, std::string gate_id);

  std::string report(Node *root);

  bool Interval_Overlap(const Interval &a, const Interval &b);

  std::vector<Interval> Find_Conflicts(int low, int high, std::string airport, std::string flight, std::string gate_id);

  std::vector<Interval> All_Intervals();

  Node *Get_Root();

private:
  Node *New_Node(int low, int high, std::string airport, std::string flight, std::string gate_id);

  void Destroy_Recursive(Node *root);

  void Update_Maximum(Node *root);

  void Find_Helper(Node *node, const Interval &q, std::vector<Interval> &out);

  void All_Helper(Node *node, std::vector<Interval> &out);

  Node *root = nullptr;
};