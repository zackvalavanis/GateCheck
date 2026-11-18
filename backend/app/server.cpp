#include "../third_party/httplib.h"
#include "../third_party/json.hpp"
#include "../code/interval_tree.h"
#include <mutex>

using json = nlohmann::json;

int main()
{
  httplib::Server svr;
  Interval_Tree gate;
  std::mutex mtx;

  svr.Post("/api/intervals", [&](const httplib::Request &req, httplib::Response &res)
           {
    auto body = json::parse(req.body);;
    std::lock_guard<std::mutex> lock(mtx);
    gate.Insert_Interval(body["low"], body["high"]);
    res.set_content(json{{"ok", true}}.dump(), "application/json"); });

  svr.Get("/api/report", [&](const httplib::Request &, httplib::Response &res)
          {
    std::lock_guard<std::mutex> lock(mtx);
    res.set_content(gate.report(gate.Get_Root()), "text/plain"); });
}
