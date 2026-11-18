#include <iostream>
#include "../code/interval_tree.h"

int main()
{
  std::cout << "GateCheck Running..." << std::endl;
  ;
  Interval_Tree gate;

  gate.Insert_Interval(1, 2);
  gate.Insert_Interval(2, 3);
  gate.Insert_Interval(3, 5);
  gate.Insert_Interval(12, 14);
  gate.Insert_Interval(3, 4);
  gate.Insert_Interval(3, 6);
  gate.Insert_Interval(1, 3);

  std::cout << gate.report(gate.Get_Root()) << std::endl;
  std::cout << (gate.Interval_Overlap({1, 2}, {2, 3}) ? "True" : "False") << std::endl;
  std::cout << (gate.Interval_Overlap({1, 5}, {2, 3}) ? "True" : "False") << std::endl;

  for (const Interval &iv : gate.Find_Conflicts(4, 5))
    std::cout << "(" << iv.low << ", " << iv.high << ")\n";

  return 0;
}