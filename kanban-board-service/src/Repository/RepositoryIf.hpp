#pragma once

#include "Core/Model/Board.hpp"
#include "optional"

namespace Prog3 {
namespace Repository {
class RepositoryIf {
  public:
    virtual ~RepositoryIf() {}

    virtual Prog3::Core::Model::Board getBoard() = 0;
    virtual std::vector<Prog3::Core::Model::Column> getColumns() = 0;
    virtual std::optional<Prog3::Core::Model::Column> getColumn(int id) = 0;
    virtual std::optional<Prog3::Core::Model::Column> postColumn(std::string name, int position) = 0;
    virtual std::optional<Prog3::Core::Model::Column> putColumn(int id, std::string name, int position) = 0;
    virtual void deleteColumn(int id) = 0;
    virtual std::vector<Prog3::Core::Model::Item> getItems(int columnId) = 0;
    virtual std::optional<Prog3::Core::Model::Item> getItem(int columnId, int itemId) = 0;
    virtual std::optional<Prog3::Core::Model::Item> postItem(int columnId, std::string title, int position) = 0;
    virtual std::optional<Prog3::Core::Model::Item> putItem(int columnId, int itemId, std::string title, int position) = 0;
    virtual void deleteItem(int columnId, int itemId) = 0;
};

} // namespace Repository
} // namespace Prog3
