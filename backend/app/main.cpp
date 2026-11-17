#include <iostream>
#include "../code/interval_tree.h"

int main()
{
  std::cout << "GateCheck Running..." << std::endl;
  ;
  Interval_Tree gate;

  gate.Insert_Interval(1, 2);
  gate.Insert_Interval(2, 3);

  std::cout << gate.report(gate.Get_Root()) << std::endl;

  return 0;
}