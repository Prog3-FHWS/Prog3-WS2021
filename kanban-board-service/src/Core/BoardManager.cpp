#include "BoardManager.hpp"
#include <iostream>

using namespace Prog3::Core;
using namespace Prog3::Core::Model;
using namespace Prog3::Api::Parser;
using namespace Prog3::Repository;
using namespace std;

BoardManager::BoardManager(ParserIf &givenParser, RepositoryIf &givenRepository)
    : parser(givenParser), repository(givenRepository) {
}

BoardManager::~BoardManager() {
}

std::string BoardManager::getBoard() {
    Board board = repository.getBoard();

    return parser.convertToApiString(board);
}

std::string BoardManager::getColumns() {
    std::vector<Column> columns = repository.getColumns();

    return parser.convertToApiString(columns);
}

std::string BoardManager::getColumn(int columnId) {

    std::optional<Column> column = repository.getColumn(columnId);
    if (column) {
        return parser.convertToApiString(column.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string BoardManager::postColumn(std::string request) {

    int const dummyId = -1;
    std::optional<Column> parsedColumnOptional = parser.convertColumnToModel(dummyId, request);
    if (false == parsedColumnOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Column parsedColumn = parsedColumnOptional.value();

    std::optional<Column> postedColumn = repository.postColumn(parsedColumn.getName(), parsedColumn.getPos());

    if (postedColumn) {
        return parser.convertToApiString(postedColumn.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string BoardManager::putColumn(int columnId, std::string request) {

    std::optional<Column> parsedColumnOptional = parser.convertColumnToModel(columnId, request);

    if (false == parsedColumnOptional.has_value()) {
        return parser.getEmptyResponseString();
    }
    Column column = parsedColumnOptional.value();
    std::optional<Column> putColumn = repository.putColumn(columnId, column.getName(), column.getPos());

    if (putColumn) {
        return parser.convertToApiString(putColumn.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

void BoardManager::deleteColumn(int columnId) {
    repository.deleteColumn(columnId);
}

std::string BoardManager::getItems(int columnId) {
    std::vector<Item> items = repository.getItems(columnId);

    return parser.convertToApiString(items);
}

std::string BoardManager::getItem(int columnId, int itemId) {

    std::optional<Item> item = repository.getItem(columnId, itemId);

    if (item) {
        return parser.convertToApiString(item.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string BoardManager::postItem(int columnId, std::string request) {

    int const dummyId = -1;
    std::optional parsedItemOptional = parser.convertItemToModel(dummyId, request);
    if (false == parsedItemOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Item item = parsedItemOptional.value();
    std::optional<Item> postedItem = repository.postItem(columnId, item.getTitle(), item.getPos());
    if (postedItem) {
        return parser.convertToApiString(postedItem.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string BoardManager::putItem(int columnId, int itemId, std::string request) {

    std::optional parsedItemOptional = parser.convertItemToModel(itemId, request);
    if (false == parsedItemOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Item item = parsedItemOptional.value();
    std::optional<Item> putItem = repository.putItem(columnId, itemId, item.getTitle(), item.getPos());

    if (putItem) {
        return parser.convertToApiString(putItem.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

void BoardManager::deleteItem(int columnId, int itemId) {
    repository.deleteItem(columnId, itemId);
}
