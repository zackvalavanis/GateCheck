#include "../third_party/httplib.h"
#include "../third_party/json.hpp"
#include "../code/interval_tree.h"
#include "../code/priority_queue.h"
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

std::string assign_flights(std::map<std::string, Interval_Tree> &gates, Interval flight)
{
  for (auto &gate : gates)
  {
    std::vector<Interval> conflicts = gate.second.Find_Conflicts(flight.low, flight.high, flight.airport, flight.flight, gate.first);
    if (conflicts.empty())
    {
      gate.second.Insert_Interval(flight.low, flight.high, flight.airport, flight.flight, gate.first);
      return gate.first;
    }
  }
  return "";
}

int main()
{
  httplib::Server svr;
  std::map<std::string, Interval_Tree> gates;
  pq *new_queue = init_priority_queue();
  std::mutex mtx;

  std::ifstream flight_info("../data/flights.json");
  json flights = json::parse(flight_info);

  for (const auto &f : flights)
  {
    std::string airport = f["airport"];
    std::string flight = f["flight"];
    int low = to_minutes(f["arrive"]);
    int high = to_minutes(f["depart"]);

    insert_pq(new_queue, Interval{low, high, airport, flight, ""}, low);
  }

  std::ifstream gate_info("../data/ord.json");
  json gate_list = json::parse(gate_info);

  for (const auto &g : gate_list.at("gates"))
  {
    std::string gate_id = g.at("gate_id");
    gates[gate_id];
  }

  std::cout << "Loaded " << gates.size() << " gates, " << new_queue->size << " flights queued" << std::endl;

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

  svr.Post("/api/next", [&](const httplib::Request &req, httplib::Response &res)
           {
             std::lock_guard<std::mutex> lock(mtx);
             json out = json::array();
             if (new_queue->size == 0)
             {
               res.set_content(json{{"done", true}}.dump() + "\n", "application/json");
             }
             else
             {
               Interval next_flight = remove_pq(new_queue);
               std::string gate = assign_flights(gates, next_flight);
               res.set_content(json{{"flight", next_flight.flight}, {"low", next_flight.low}, {"high", next_flight.high}, {"gate_id", gate}}.dump() + "\n", "application/json");
             } });

  svr.Get("/api/state", [&](const httplib::Request &req, httplib::Response &res)
          {
    std::lock_guard<std::mutex> lock(mtx);
    json out = json::array();

    for(auto & entry : gates){
      json flights_out = json::array();
      for(const Interval & iv : entry.second.All_Intervals())
        flights_out.push_back({{"low", iv.low}, {"high", iv.high}, {"airport", iv.airport}, {"flight", iv.flight}, {"gate_id", iv.gate_id}}); 
      out.push_back({{"gate_id", entry.first}, {"flights", flights_out}});
    }
    res.set_content(out.dump() + "\n", "application/json"); });

  std::cout << "Gatecheck server on http://localhost:8080" << std::endl;

  if (!svr.listen("0.0.0.0", 8080))
  {
    std::cerr << "Failed to start: port 8080 may be in use" << std::endl;
    return 1;
  }
}
