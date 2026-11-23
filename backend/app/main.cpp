#include <iostream>
#include "../code/interval_tree.h"

int main()
{
  std::cout << "GateCheck Running..." << std::endl;
  ;
  Interval_Tree gate;

  gate.Insert_Interval(1, 2, "UA1", "B12");
  gate.Insert_Interval(2, 3, "UA2", "B12");
  gate.Insert_Interval(3, 5, "UA3", "B12");
  gate.Insert_Interval(12, 14, "UA4", "B12");
  gate.Insert_Interval(3, 4, "UA5", "B12");
  gate.Insert_Interval(3, 6, "UA6", "B12");
  gate.Insert_Interval(1, 3, "UA7", "B12");
  gate.Insert_Interval(4, 5, "AA99", "C4");

  std::cout << gate.report(gate.Get_Root()) << std::endl;
  std::cout << (gate.Interval_Overlap({1, 2}, {2, 3}) ? "True" : "False") << std::endl;
  std::cout << (gate.Interval_Overlap({1, 5}, {2, 3}) ? "True" : "False") << std::endl;

  std::cout << "Conflicts with (4, 5):\n";
  for (const Interval &iv : gate.Find_Conflicts(4, 5, "", "B12"))
    std::cout << "(" << iv.low << ", " << iv.high << ")\n";

  std::cout << "All intervals:\n";
  for (const Interval &iv : gate.All_Intervals())
    std::cout << "(" << iv.low << ", " << iv.high << ")\n";

  return 0;
}