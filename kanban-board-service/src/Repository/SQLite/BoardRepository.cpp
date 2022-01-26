#include "BoardRepository.hpp"
#include "Core/Exception/NotImplementedException.hpp"
#include <ctime>
#include <filesystem>
#include <string.h>

using namespace Prog3::Repository::SQLite;
using namespace Prog3::Core::Model;
using namespace Prog3::Core::Exception;
using namespace std;

#ifdef RELEASE_SERVICE
string const BoardRepository::databaseFile = "./data/kanban-board.db";
#else
string const BoardRepository::databaseFile = "../data/kanban-board.db";
#endif

BoardRepository::BoardRepository() : database(nullptr) {

    string databaseDirectory = filesystem::path(databaseFile).parent_path().string();

    if (filesystem::is_directory(databaseDirectory) == false) {
        filesystem::create_directory(databaseDirectory);
    }

    int result = sqlite3_open(databaseFile.c_str(), &database);

    if (SQLITE_OK != result) {
        cout << "Cannot open database: " << sqlite3_errmsg(database) << endl;
    }

    initialize();
}

BoardRepository::~BoardRepository() {
    sqlite3_close(database);
}

void BoardRepository::initialize() {
    int result = 0;
    char *errorMessage = nullptr;

    string sqlCreateTableColumn =
        "create table if not exists column("
        "id integer not null primary key autoincrement,"
        "name text not null,"
        "position integer not null UNIQUE);";

    string sqlCreateTableItem =
        "create table if not exists item("
        "id integer not null primary key autoincrement,"
        "title text not null,"
        "date text not null,"
        "position integer not null,"
        "column_id integer not null,"
        "unique (position, column_id),"
        "foreign key (column_id) references column (id));";

    result = sqlite3_exec(database, sqlCreateTableColumn.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
    result = sqlite3_exec(database, sqlCreateTableItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    // only if dummy data is needed ;)
    //createDummyData();
}

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

Board BoardRepository::getBoard() {
    throw NotImplementedException();
}

std::vector<Column> BoardRepository::getColumns() {
    throw NotImplementedException();
}

std::optional<Column> BoardRepository::getColumn(int id) {
    throw NotImplementedException();
}

std::optional<Column> BoardRepository::postColumn(std::string name, int position) {
    string sqlPostItem =
        "INSERT INTO column('name', 'position') "
        "VALUES('" +
        name + "', '" + to_string(position) + "')";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int columnId = sqlite3_last_insert_rowid(database);
        return Column(columnId, name, position);
    }

    return std::nullopt;
}

std::optional<Prog3::Core::Model::Column> BoardRepository::putColumn(int id, std::string name, int position) {
    int result = 0;
    char *errorMessage = nullptr;
    string emptyString = "";
    string emptyStringThisColumn = "";
    void *selectResult = static_cast<void *>(&emptyString);
    void *thisColumn = static_cast<void *>(&emptyStringThisColumn);

    string sqlSelectItems = "SELECT * from item WHERE column_id=" + to_string(id) + ";";
    string sqlPutColumn = "UPDATE column SET name= \"" + name + "\", position = " + to_string(position) + " WHERE id = " + to_string(id) + ";";
    string sqlSelectColumn = "SELECT * from column WHERE id=" + to_string(id) + ";";

    // CHECK IF COLUMN EXISTS
    result = sqlite3_exec(database, sqlSelectColumn.c_str(), BoardRepository::queryCallback, thisColumn, &errorMessage);
    handleSQLError(result, errorMessage);
    string *tempPointer = static_cast<string *>(thisColumn);
    string thisColumnString = *tempPointer;
    if (thisColumnString == "")
        return nullopt;
    // GET ALL ITEMS OUT OF THE COLUMN
    result = sqlite3_exec(database, sqlSelectItems.c_str(), BoardRepository::queryCallback, selectResult, &errorMessage);
    handleSQLError(result, errorMessage);
    string *sp = static_cast<string *>(selectResult);
    string data = *sp;
    vector items = split(data, ';');
    vector<Item> realItems{};
    for (auto item : items) {
        vector tuples = split(item, ',');

        string itemIdString = split(tuples[0], ':')[1];
        int itemId = stoi(itemIdString);

        string title = split(tuples[1], ':')[1];

        string datetime = split(tuples[2], ':')[1];

        string positionString = split(tuples[3], ':')[1];
        int position = stoi(positionString);

        // cout << "Id: " + to_string(itemId) + " title: " + title + " position: " + to_string(position) + " datetime: " + datetime << endl;
        realItems.push_back(Item(itemId, title, position, datetime));
    }
    // UPDATE COLUMN
    errorMessage = nullptr;
    result = sqlite3_exec(database, sqlPutColumn.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK != result) {
        cout << "Could not edit column with id " + to_string(id) + "." << endl;
        return nullopt;
    }
    cout << "Column with id " + to_string(id) + " sucessfully edited" << endl;
    Column column(id, name, position);
    for (auto item : realItems) {
        column.addItem(item);
    }
    return column;
}

void BoardRepository::deleteColumn(int id) {
    int result = 0;
    char *errorMessage = nullptr;

    string sqlDeleteColumn =
        "delete from column "
        "where id = " +
        std::to_string(id);

    result = sqlite3_exec(database, sqlDeleteColumn.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

void BoardRepository::deleteItem(int columnId, int itemId) {
    int result = 0;
    char *errorMessage = nullptr;

    string sqlDeleteItem =
        "delete from item "
        "where id = " +
        std::to_string(itemId) +
        " and column_id = " + std::to_string(columnId);

    result = sqlite3_exec(database, sqlDeleteItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

std::optional<Item> BoardRepository::getItem(int columnId, int itemId) {
    throw NotImplementedException();
}

std::optional<Item> BoardRepository::postItem(int columnId, std::string title, int position) {

    time_t now = time(0);
    char *datetime = ctime(&now);

    string sqlPostItem =
        "INSERT INTO item ('title', 'date', 'position', 'column_id') "
        "VALUES ('" +
        title + "', '" + datetime + "', " + to_string(position) + ", " + to_string(columnId) + ");";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    int itemId = INVALID_ID;
    if (SQLITE_OK == result) {
        itemId = sqlite3_last_insert_rowid(database);
        return Item(itemId, title, position, datetime);
    }
    return std::nullopt;
}

std::optional<Prog3::Core::Model::Item> BoardRepository::putItem(int columnId, int itemId, std::string title, int position) {
    time_t now = time(0);
    char *datetime = ctime(&now);

    char *errorMessage = nullptr;
    int result = 0;

    //  COMMENT THIS IS IN IF YOU WANT TO PREVENT USERS CREATING RESOURCES VIA PUT INSTEAD OF POST
    string emptyString = "";
    void *selectResult = static_cast<void *>(&emptyString);
    string sqlSelect = "SELECT * FROM item WHERE id =" + to_string(itemId) + ";";
    int selectAnswer = sqlite3_exec(database, sqlSelect.c_str(), BoardRepository::queryCallback, selectResult, &errorMessage);
    handleSQLError(selectAnswer, errorMessage);

    string *tempPointer = static_cast<string *>(selectResult);
    string thisItemString = *tempPointer;
    if (thisItemString == "") {
        return nullopt;
    }

    string sqlPutItem = "UPDATE item SET title =\"" + title + "\"" + ", position =" + to_string(position) + ", column_id= " + to_string(columnId) + " WHERE id = " + to_string(itemId) + ";";

    result = sqlite3_exec(database, sqlPutItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK != result) {
        cout << "Could not edit item with id " + to_string(itemId) + "." << endl;
        return nullopt;
    }
    std::cout << "Item with id " + to_string(itemId) + " sucessfully edited" << endl;
    return Item(itemId, title, position, datetime);
}

void BoardRepository::deleteItem(int columnId, int itemId) {
    throw NotImplementedException();
}

void BoardRepository::handleSQLError(int statementResult, char *errorMessage) {

    if (statementResult != SQLITE_OK) {
        cout << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

void BoardRepository::createDummyData() {

    cout << "creatingDummyData ..." << endl;

    int result = 0;
    char *errorMessage;
    string sqlInsertDummyColumns =
        "insert into column (name, position)"
        "VALUES"
        "(\"prepare\", 1),"
        "(\"running\", 2),"
        "(\"finished\", 3);";

    result = sqlite3_exec(database, sqlInsertDummyColumns.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    string sqlInserDummyItems =
        "insert into item (title, date, position, column_id)"
        "VALUES"
        "(\"in plan\", date('now'), 1, 1),"
        "(\"some running task\", date('now'), 1, 2),"
        "(\"finished task 1\", date('now'), 1, 3),"
        "(\"finished task 2\", date('now'), 2, 3);";

    result = sqlite3_exec(database, sqlInserDummyItems.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

/*
  I know source code comments are bad, but this one is to guide you through the use of sqlite3_exec() in case you want to use it.
  sqlite3_exec takes a "Callback function" as one of its arguments, and since there are many crazy approaches in the wild internet,
  I want to show you how the signature of this "callback function" may look like in order to work with sqlite3_exec()
*/
int BoardRepository::queryCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {
    string *stringPointer = static_cast<string *>(data);
    int size = sizeof(columnNames) / sizeof(columnNames[0]);
    for (int i = 0; i < numberOfColumns; i++) {
        *stringPointer = *stringPointer + columnNames[i] + ":" + fieldValues[i];
        if (i < numberOfColumns - 1)
            *stringPointer = *stringPointer + ",";
    }
    *stringPointer = *stringPointer + ";";
    return 0;
}
