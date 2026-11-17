#include "interval_tree.h"
#include <algorithm>

Interval_Tree::Interval_Tree() {};

Interval_Tree::~Interval_Tree() {};

Node *Interval_Tree::New_Node(int low, int high)
{
  Node *new_node = new Node();
  new_node->i.high = high;
  new_node->i.low = low;
  new_node->left = nullptr;
  new_node->right = nullptr;
  new_node->max = high;
  return new_node;
};

void Interval_Tree::Insert_Interval(int a, int b)
{

  if (root == nullptr)
  {
    root = New_Node(a, b);
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
        curr->left = New_Node(a, b);
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
        curr->right = New_Node(a, b);
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
  if (a.high == NULL || a.low == NULL || b.high == NULL || b.low == NULL)
  {
    return false;
  }

  if (a.high <= b.high && a.high > b.low || b.high <= a.high && b.high > a.low)
  {
    return true;
  }

  if (a.low >= b.low && a.low < b.high || b.low >= a.low && b.low < a.high)
  {
    return true;
  }

  return false;
}