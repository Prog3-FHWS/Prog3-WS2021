#include <iostream>
#include <string>

#include "Api/Endpoint.hpp"
#include "Api/Parser/JsonParser.hpp"
#include "Core/BoardManager.hpp"
#include "Repository/SQLite/BoardRepository.hpp"
#include "crow.h"

int main() {
    crow::SimpleApp crowApplication;
    Prog3::Repository::SQLite::BoardRepository sqlRepository;
    Prog3::Api::Parser::JsonParser jsonParser;

    Prog3::Core::BoardManager boardManager(jsonParser, sqlRepository);
    Prog3::Api::Endpoint endpoint(crowApplication, boardManager);

    crowApplication.port(8080)
        //        .multithreaded()
        .run();
}
