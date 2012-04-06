#include "message.hh"

#include <sstream>
#include <ostream>
#include <cstring>

namespace net {

Message::Message(uint32_t type_, uint32_t client_id_)
    : type(type_),
      client_id(client_id_),
      size(0)
{
    memset(data, 0, sizeof (data));
}

std::string Message::str() const
{
    std::stringstream ss;

    ss << "type      : " << type << "\n"
       << "client_id : " << client_id << "\n"
       << "size      : " << size;

    return ss.str();
}

} // namespace net

std::ostream& operator<<(std::ostream& os, const net::Message& msg)
{
    os << msg.str() << std::endl;

    return os;
}
