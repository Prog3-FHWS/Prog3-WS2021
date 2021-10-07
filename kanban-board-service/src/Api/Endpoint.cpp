#include "Endpoint.hpp"

#include <iostream>

using namespace Prog3::Api;
using namespace Prog3::Core;
using namespace crow;
using namespace std;

Endpoint::Endpoint(SimpleApp &givenApp, BoardManager &givenBoardManager) : app(givenApp),
                                                                           boardManager(givenBoardManager) {
    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {
    CROW_ROUTE(app, "/api/board")
    ([this](const request &req, response &res) {
        std::string jsonBoards = boardManager.getBoard();
        res.write(jsonBoards);
        res.end();
    });

    CROW_ROUTE(app, "/api/board/columns")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res) {
            std::string jsonColumns;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumns = boardManager.getColumns();
                break;
            }
            case HTTPMethod::Post: {
                jsonColumns = boardManager.postColumn(req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumns);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/columns/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int columnID) {
            std::string jsonColumn = "{}";

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonColumn = boardManager.getColumn(columnID);
                break;
            }
            case HTTPMethod::Put: {
                jsonColumn = boardManager.putColumn(columnID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                boardManager.deleteColumn(columnID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonColumn);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/columns/<int>/items")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res, int columnID) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = boardManager.getItems(columnID);
                break;
            }
            case HTTPMethod::Post: {
                jsonItem = boardManager.postItem(columnID, req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/columns/<int>/items/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int columnID, int itemID) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = boardManager.getItem(columnID, itemID);
                break;
            }
            case HTTPMethod::Put: {
                jsonItem = boardManager.putItem(columnID, itemID, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                boardManager.deleteItem(columnID, itemID);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });
}
