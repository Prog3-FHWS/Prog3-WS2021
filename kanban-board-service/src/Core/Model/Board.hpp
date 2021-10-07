#pragma once

#include "Column.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace Prog3 {
namespace Core {
namespace Model {

class Board {
  public:
    Board(std::string givenTitle);
    ~Board() {}

    std::string getTitle() const;

    std::vector<Column> &getColumns();
    void setColumns(std::vector<Column> const &columns);

  private:
    std::string title;
    std::vector<Column> columns;
};

} // namespace Model
} // namespace Core
} // namespace Prog3
