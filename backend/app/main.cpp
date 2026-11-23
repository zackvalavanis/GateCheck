#include <iostream>
#include "../code/interval_tree.h"

int main()
{
  std::cout << "GateCheck Running..." << std::endl;
  ;
  Interval_Tree gate;

  std::cout << gate.report(gate.Get_Root()) << std::endl;
  std::cout << (gate.Interval_Overlap({1, 2}, {2, 3}) ? "True" : "False") << std::endl;
  std::cout << (gate.Interval_Overlap({1, 5}, {2, 3}) ? "True" : "False") << std::endl;

  std::cout << "Conflicts with (4, 5):\n";
  for (const Interval &iv : gate.Find_Conflicts(4, 5))
    std::cout << "(" << iv.low << ", " << iv.high << ")\n";

  std::cout << "All intervals:\n";
  for (const Interval &iv : gate.All_Intervals())
    std::cout << "(" << iv.low << ", " << iv.high << ")\n";

  return 0;
}