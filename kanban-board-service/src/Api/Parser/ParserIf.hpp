#pragma once

#include "Core/Model/Board.hpp"
#include "optional"

namespace Prog3 {
namespace Api {
namespace Parser {

class ParserIf {
  public:
    virtual ~ParserIf() {}

    virtual std::string getEmptyResponseString() = 0;

    virtual std::string convertToApiString(Prog3::Core::Model::Board &board) = 0;
    virtual std::string convertToApiString(Prog3::Core::Model::Column &column) = 0;
    virtual std::string convertToApiString(std::vector<Prog3::Core::Model::Column> &columns) = 0;

    virtual std::string convertToApiString(Prog3::Core::Model::Item &item) = 0;
    virtual std::string convertToApiString(std::vector<Prog3::Core::Model::Item> &items) = 0;

    virtual std::optional<Prog3::Core::Model::Column> convertColumnToModel(int columnId, std::string &request) = 0;
    virtual std::optional<Prog3::Core::Model::Item> convertItemToModel(int itemId, std::string &request) = 0;
};

} // namespace Parser
} // namespace Api
} // namespace Prog3