#pragma once

#include "Api/Parser/ParserIf.hpp"
#include "Repository/RepositoryIf.hpp"

namespace Prog3 {
namespace Core {
class BoardManager {
  private:
    Prog3::Repository::RepositoryIf &repository;
    Prog3::Api::Parser::ParserIf &parser;

  public:
    BoardManager(Prog3::Api::Parser::ParserIf &givenParser, Prog3::Repository::RepositoryIf &givenRepository);
    ~BoardManager();

    std::string getBoard();
    std::string getColumns();
    std::string getColumn(int columnId);
    std::string postColumn(std::string request);
    std::string putColumn(int columnId, std::string request);
    void deleteColumn(int columnId);

    std::string getItems(int columnId);
    std::string getItem(int columnId, int itemId);
    std::string postItem(int columnId, std::string request);
    std::string putItem(int columnId, int itemId, std::string request);
    void deleteItem(int columnId, int itemId);
};

} // namespace Core
} // namespace Prog3
