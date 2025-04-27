#include "crow/middlewares/cors.h"
#include "interpreter.cpp"
#include <crow.h>
int main() {
  crow::App<crow::CORSHandler> app;

  // Customize CORS settings
  auto &cors = app.get_middleware<crow::CORSHandler>();

  cors.global()
      .headers("Content-Type", "Accept") // Specify the headers you expect
      .methods("POST"_method, "GET"_method, "OPTIONS"_method) // Include OPTIONS
      .origin("http://localhost:8000") // Specify the allowed origin
      .max_age(
          3600); // Optional: Set a max age for preflight responses (in seconds)
  CROW_ROUTE(app, "/interprate").methods("OPTIONS"_method)([]() {
    // The CORS middleware should handle the OPTIONS response for this route
    // now. We might not need an explicit handler here, but it's good to have
    // for logging or customization.
    std::cout
        << "Received OPTIONS request for /interprate (handled by middleware)"
        << std::endl;
    crow::response res;
    res.code = 204;
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
