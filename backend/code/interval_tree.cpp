#include "interval_tree.h"
#include <algorithm>

Interval_Tree::Interval_Tree() {};

void Interval_Tree::Destroy_Recursive(Node *root)
{
  if (root == nullptr)
  {
    return;
  }

  Destroy_Recursive(root->left);
  Destroy_Recursive(root->right);
  delete root;
}

Interval_Tree::~Interval_Tree()
{
  Destroy_Recursive(root);
};

Node *Interval_Tree::New_Node(int low, int high, std::string airport, std::string flight, std::string gate_id)
{
  Node *new_node = new Node();
  new_node->i.high = high;
  new_node->i.low = low;
  new_node->i.airport = airport;
  new_node->i.gate_id = gate_id;
  new_node->i.flight = flight;
  new_node->left = nullptr;
  new_node->right = nullptr;
  new_node->max = high;
  return new_node;
};

void Interval_Tree::Insert_Interval(int a, int b, std::string airport, std::string flight, std::string gate_id)
{

  if (root == nullptr)
  {
    root = New_Node(a, b, airport, flight, gate_id);
    return;
  }
  Node *curr = root;

  while (curr != nullptr)
  {
    curr->max = std::max(curr->max, b);

    if (a < curr->i.low)
    {
      if (curr->left == nullptr)
      {
        curr->left = New_Node(a, b, airport, flight, gate_id);
        return;
      }
      else
      {
        curr = curr->left;
      }
    }
    else
    {
      if (curr->right == nullptr)
      {
        curr->right = New_Node(a, b, airport, flight, gate_id);
        return;
      }
      else
      {
        curr = curr->right;
      }
    }
  }
};

std::string Interval_Tree::report(Node *root)
{
  if (root == nullptr)
  {
    return "";
  }

  std::string left = report(root->left);
  std::string here = "(" + std::to_string(root->i.low) + ", " + std::to_string(root->i.high) + ") max = " + std::to_string(root->max) + "\n";
  std::string right = report(root->right);

  return left + here + right;
}

void Interval_Tree::Update_Maximum(Node *root)
{
  if (root == nullptr)
  {
    return;
  }

  Node *curr = root;
  int m = curr->i.high;

  if (curr->left != nullptr)
  {
    m = std::max(m, curr->left->max);
  }

  if (curr->right != nullptr)
  {
    m = std::max(m, curr->right->max);
  }

  root->max = m;
}

Node *Interval_Tree::Get_Root()
{
  return root;
}

bool Interval_Tree::Interval_Overlap(const Interval &a, const Interval &b)
{
  if (a.gate_id != b.gate_id || a.airport != b.airport)
  {
    return false;
  }

  if (a.gate_id == b.gate_id && a.airport == b.airport)
  {
    if (a.high <= b.high && a.high > b.low || b.high <= a.high && b.high > a.low)
    {
      return true;
    }
  }

  if (a.gate_id == b.gate_id && a.airport == b.airport)
  {
    if (a.low >= b.low && a.low < b.high || b.low >= a.low && b.low < a.high)
    {
      return true;
    }
  }
  return false;
}

std::vector<Interval> Interval_Tree::Find_Conflicts(int low, int high, std::string airport, std::string flight, std::string gate_id)
{
  std::vector<Interval> out;
  Find_Helper(root, Interval{low, high, airport, flight, gate_id}, out);
  return out;
}

void Interval_Tree::Find_Helper(Node *node, const Interval &q, std::vector<Interval> &out)
{
  if (node == nullptr)
  {
    return;
  }

  if (node->max <= q.low)
  {
    return;
  }

  Find_Helper(node->left, q, out);

  if (Interval_Overlap(node->i, q))
  {
    out.push_back(node->i);
  }

  if (node->i.low >= q.high)
  {
    return;
  }
  Find_Helper(node->right, q, out);
};

void Interval_Tree::All_Helper(Node *node, std::vector<Interval> &out)
{
  if (node == nullptr)
  {
    return;
  }

  All_Helper(node->left, out);

  out.push_back(node->i);

  All_Helper(node->right, out);
}

std::vector<Interval> Interval_Tree::All_Intervals()
{
  std::vector<Interval> out;
  All_Helper(root, out);
  return out;
}
