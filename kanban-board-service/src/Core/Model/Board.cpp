#include "Board.hpp"

using namespace Prog3::Core::Model;

Board::Board(std::string givenTitle) : title(givenTitle) {}

std::string Board::getTitle() const {
    return title;
}

std::vector<Column> &Board::getColumns() {
    return columns;
}

void Board::setColumns(std::vector<Column> const &columns) {
    this->columns = columns;
}
