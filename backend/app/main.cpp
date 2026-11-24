#include <iostream>
#include "../code/interval_tree.h"
#include "../code/priority_queue.h"
#include <map>

int main()
{
  std::cout << "GateCheck Running..." << std::endl;

  std::map<std::string, Interval_Tree> gates;

  gates["B12"].Insert_Interval(1, 2, "ORD", "UA1", "B12");
  gates["B12"].Insert_Interval(2, 3, "ORD", "UA2", "B12");
  gates["B12"].Insert_Interval(3, 5, "ORD", "UA3", "B12");
  gates["B12"].Insert_Interval(12, 14, "ORD", "UA4", "B12");
  gates["B12"].Insert_Interval(3, 4, "ORD", "UA5", "B12");
  gates["B12"].Insert_Interval(3, 6, "ORD", "UA6", "B12");
  gates["B12"].Insert_Interval(1, 3, "ORD", "UA7", "B12");
  gates["C4"].Insert_Interval(4, 5, "ORD", "UA99", "C4");

  std::cout << gates["B12"].report(gates["B12"].Get_Root()) << std::endl;
  std::cout << (gates["B12"].Interval_Overlap({1, 2}, {2, 3}) ? "True" : "False") << std::endl;
  std::cout << (gates["B12"].Interval_Overlap({1, 5}, {2, 3}) ? "True" : "False") << std::endl;

  std::cout << "Conflicts with (4, 5):\n";
  for (const Interval &iv : gates["B12"].Find_Conflicts(4, 5, "ORD", "", "B12"))
    std::cout << "(" << iv.low << ", " << iv.high << ", " << iv.airport << ", " << iv.flight << ", " << iv.gate_id << ")\n";

  std::cout << "All intervals:\n";
  for (const Interval &iv : gates["B12"].All_Intervals())
    std::cout << "(" << iv.low << ", " << iv.high << ", " << iv.airport << ", " << iv.flight << ", " << iv.gate_id << ")\n";

  std::cout << "C4 intervals:\n";
  for (const Interval &iv : gates["C4"].All_Intervals())
    std::cout << "(" << iv.low << ", " << iv.high << ", " << iv.airport << ", " << iv.flight << ", " << iv.gate_id << ")\n";

  pq *new_queue = init_priority_queue();
  insert_pq(new_queue, Interval{1, 2, "ORD", "UA1", ""}, 1);
  insert_pq(new_queue, Interval{2, 3, "ORD", "UA2", ""}, 2);
  insert_pq(new_queue, Interval{3, 5, "ORD", "UA3", ""}, 3);
  insert_pq(new_queue, Interval{12, 14, "ORD", "UA4", ""}, 12);
  insert_pq(new_queue, Interval{3, 4, "ORD", "UA5", ""}, 3);
  insert_pq(new_queue, Interval{3, 6, "ORD", "UA6", ""}, 3);
  insert_pq(new_queue, Interval{1, 3, "ORD", "UA7", ""}, 1);
  insert_pq(new_queue, Interval{4, 5, "ORD", "UA99", "C4"}, 4);

  std::cout << "Priority queue test:\n";
  while (new_queue->size != 0)
  {
    Interval f = remove_pq(new_queue);
    std::cout << f.flight << " " << f.low << std::endl;
  }

  return 0;
}