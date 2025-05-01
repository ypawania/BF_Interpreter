#include "crow/middlewares/cors.h"
#include "interpreter.cpp"
#include <crow.h>
int main() {
  crow::App<crow::CORSHandler> app;

  // CORS handling for OPTIONS request
  CROW_ROUTE(app, "/interprate")
      .methods("OPTIONS"_method)([](const crow::request &req) {
        crow::response res;
        res.code = 204;
        res.add_header("Access-Control-Allow-Origin", "*"); // Allow all origins
        res.add_header("Access-Control-Allow-Methods",
                       "POST, OPTIONS"); // Allow POST and OPTIONS
        res.add_header("Access-Control-Allow-Headers",
                       "Content-Type"); // Allow Content-Type header
        return res;
      });

  CROW_ROUTE(app, "/interprate")
      .methods("POST"_method)([](const crow::request &req) {
        auto json = crow::json::load(req.body);
        if (!json)
          return crow::response(400);
        std::string code = json["code"].s();
        std::string input = json["input"].s();
        std::string output = interpret_bf(code, input);
        crow::json::wvalue response;
        response["output"] = output;
        crow::response res(response);

        // Add CORS headers
        return res;
      });

  app.port(18080).multithreaded().run();
}
