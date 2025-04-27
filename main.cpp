#include "interpreter.cpp"
#include <crow.h>

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "interprate")
      .methods("POST"_method)([](const crow::request &req) {
        auto json = crow::json::load(req.body);
        if (!json)
          return crow::response(400);
        std::string code = json["code"].s();
        std::string input = json["input"].s();
        std::string output = interpret_bf(code, input);
        crow::json::wvalue response;
        response["output"] = output;
        return crow::response(response);
      });

  app.port(19090).multithreaded().run();
}
