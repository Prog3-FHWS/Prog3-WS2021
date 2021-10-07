#include "Column.hpp"

using namespace Prog3::Core::Model;

Column::Column(int id, std::string givenName, int givenPosition)
    : id(id), name(givenName), position(givenPosition) {}

int Column::getId() const {
    return id;
}

std::string Column::getName() const {
    return name;
}

int Column::getPos() const {
    return position;
}

std::vector<Item> Column::getItems() const {
    return items;
}

void Column::setID(int givenId) {
    id = givenId;
}

void Column::setName(std::string givenName) {
    name = givenName;
}

void Column::setPos(int givenPos) {
    position = givenPos;
}

void Column::addItem(Item &givenItem) {
    items.push_back(givenItem);
}
