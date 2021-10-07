#pragma once

#include <string>

namespace Prog3 {
namespace Core {
namespace Model {

class Item {
  public:
    Item(int id, std::string givenTitle, int givenPosition, std::string givenTimestamp);
    ~Item(){};

    int getId() const;
    std::string getTitle() const;
    int getPos() const;
    std::string getTimestamp() const;

    void setID(int givenID);
    void setTitle(std::string givenTitle);
    void setPos(int givenPos);
    void setTimestamp(std::string givenTime);

  private:
    int id;
    std::string title;
    int position;
    std::string timestamp;
};

} // namespace Model
} // namespace Core
} // namespace Prog3