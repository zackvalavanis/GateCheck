#include "../third_party/httplib.h"
#include "../third_party/json.hpp"
#include "../code/interval_tree.h"
#include <mutex>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int to_minutes(const std::string &time)
{
  int hours = std::stoi(time.substr(0, 2));
  int minutes = std::stoi(time.substr(3, 2));
  return hours * 60 + minutes;
}

int main()
{
  httplib::Server svr;
  Interval_Tree gate;
  std::mutex mtx;

  std::ifstream file("../data/flights.json");
  json flights = json::parse(file);

  for (const auto &f : flights)
  {
    std::string flight = f["flight"];
    std::string gate_id = f["gate"];
    int low = to_minutes(f["arrive"]);
    int high = to_minutes(f["depart"]);

    std::cout << flight << " at " << gate_id << ": " << low << " to " << high << std::endl;
    gate.Insert_Interval(low, high);
  }

  svr.Post("/api/intervals", [&](const httplib::Request &req, httplib::Response &res)
           {
    auto body = json::parse(req.body);;
    std::lock_guard<std::mutex> lock(mtx);
    gate.Insert_Interval(body["low"], body["high"]);
    res.set_content(json{{"ok", true}}.dump(), "application/json"); });

  svr.Get("/api/report", [&](const httplib::Request &req, httplib::Response &res)
          {
    std::lock_guard<std::mutex> lock(mtx);
    res.set_content(gate.report(gate.Get_Root()), "text/plain"); });

  svr.Get("/api/all_intervals", [&](const httplib::Request &req, httplib::Response &res)
          {
    std::lock_guard<std::mutex> lock(mtx);
    json out = json::array();
    for(const Interval & iv : gate.All_Intervals())
      out.push_back({{"low", iv.low}, {"high", iv.high}}); 
    res.set_content(out.dump() + "\n", "application/json"); });

  svr.Post("/api/conflicts", [&](const httplib::Request &req, httplib::Response &res)
           {
    auto body = json::parse(req.body);
    std::lock_guard<std::mutex> lock(mtx);

    json out = json::array();

    for(const Interval &iv : gate.Find_Conflicts(body["low"], body["high"]))
    out.push_back({{"low", iv.low}, {"high", iv.high}});
    res.set_content(out.dump() + "\n", "application/json"); });

  std::cout << "Gatecheck server on http://localhost:8080" << std::endl;

  if (!svr.listen("0.0.0.0", 8080))
  {
    std::cerr << "Failed to start: port 8080 may be in use" << std::endl;
    return 1;
  }
}
