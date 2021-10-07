#include "Item.hpp"

using namespace Prog3::Core::Model;

Item::Item(int id, std::string givenTitle, int givenPosition, std::string givenTimestamp)
    : id(id), title(givenTitle), position(givenPosition), timestamp(givenTimestamp) {}

int Item::getId() const {
    return id;
}

std::string Item::getTitle() const {
    return title;
}

int Item::getPos() const {
    return position;
}

std::string Item::getTimestamp() const {
    return timestamp;
}

void Item::setID(int givenID) {
    id = givenID;
}

void Item::setTitle(std::string givenTitle) {
    title = givenTitle;
}

void Item::setPos(int givenPos) {
    position = givenPos;
}

void Item::setTimestamp(std::string givenTime) {
    timestamp = givenTime;
}
