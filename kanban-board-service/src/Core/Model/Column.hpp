#pragma once

#include "Item.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace Prog3 {
namespace Core {

namespace Model {

class Column {
  public:
    Column(int id, std::string givenName, int givenPosition);
    ~Column(){};

    int getId() const;
    std::string getName() const;
    int getPos() const;
    std::vector<Item> getItems() const;

    void setID(int givenId);
    void setName(std::string givenName);
    void setPos(int givenPos);
    void addItem(Item &givenItem);

  private:
    int id;
    std::string name;
    int position;
    std::vector<Item> items;
};

} // namespace Model
} // namespace Core
} // namespace Prog3
