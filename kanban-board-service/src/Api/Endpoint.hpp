#pragma once

#include "Core/BoardManager.hpp"
#include "crow.h"

namespace Prog3 {
namespace Api {

class Endpoint {
  public:
    Endpoint(crow::SimpleApp &givenApp, Prog3::Core::BoardManager &givenBoardManager);
    ~Endpoint();

    void registerRoutes();

  private:
    crow::SimpleApp &app;
    Prog3::Core::BoardManager &boardManager;
};

} // namespace Api
} // namespace Prog3
