#pragma once

#include <stdexcept>

namespace Prog3 {
namespace Core {
namespace Exception {
class NotImplementedException : public std::logic_error {
  public:
    NotImplementedException() : std::logic_error("Function not yet implemented"){};
};
} // namespace Exception
} // namespace Core
} // namespace Prog3