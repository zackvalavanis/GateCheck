#include "../third_party/httplib.h"
#include "../third_party/json.hpp"
#include "../code/interval_tree.h"
#include <mutex>
#include <iostream>
#include <fstream>
#include <map>

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
  std::map<std::string, Interval_Tree> gates;
  std::mutex mtx;

  std::ifstream file("../data/flights.json");
  json flights = json::parse(file);

  for (const auto &f : flights)
  {
    std::string airport = f["airport"];
    std::string flight = f["flight"];
    std::string gate_id = f["gate_id"];
    int low = to_minutes(f["arrive"]);
    int high = to_minutes(f["depart"]);

    std::cout << flight << " at " << gate_id << ": " << low << " to " << high << std::endl;
    gates[gate_id].Insert_Interval(low, high, airport, flight, gate_id);
  }

  svr.Post("/api/intervals", [&](const httplib::Request &req, httplib::Response &res)
           {
    auto body = json::parse(req.body);;
    std::lock_guard<std::mutex> lock(mtx);
    std::string gate_id = body["gate_id"]; 
    gates[gate_id].Insert_Interval(body["low"], body["high"], body["airport"], body["flight"], body["gate_id"]);
    res.set_content(json{{"ok", true}}.dump(), "application/json"); });

  svr.Get("/api/all_intervals", [&](const httplib::Request &req, httplib::Response &res)
          {
    std::lock_guard<std::mutex> lock(mtx);
    json out = json::array();
    for(auto & entry : gates){
      for(const Interval & iv : entry.second.All_Intervals())
        out.push_back({{"low", iv.low}, {"high", iv.high}, {"airport", iv.airport}, {"flight", iv.flight}, {"gate_id", iv.gate_id}}); 
    }
    res.set_content(out.dump() + "\n", "application/json"); });

  svr.Post("/api/conflicts", [&](const httplib::Request &req, httplib::Response &res)
           {
    auto body = json::parse(req.body);
    std::lock_guard<std::mutex> lock(mtx);
    std::string gate_id = body["gate_id"]; 

    json out = json::array();
    
    for(const Interval &iv : gates[gate_id].Find_Conflicts(body["low"], body["high"], body["airport"], body["flight"], body["gate_id"]))
    out.push_back({{"low", iv.low}, {"high", iv.high}, {"airport", iv.airport}, {"flight", iv.flight}, {"gate_id", iv.gate_id}});
    res.set_content(out.dump() + "\n", "application/json"); });

  std::cout << "Gatecheck server on http://localhost:8080" << std::endl;

  if (!svr.listen("0.0.0.0", 8080))
  {
    std::cerr << "Failed to start: port 8080 may be in use" << std::endl;
    return 1;
  }
}
