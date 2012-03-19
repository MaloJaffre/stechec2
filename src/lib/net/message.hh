#ifndef LIB_NET_MESSAGE_HH_
# define LIB_NET_MESSAGE_HH_

# include <cstdint>
# include <iostream>

namespace net {

// Message types of stechec2 (not the rules)
enum MsgType
{
    MSG_ERR     = 0,
    MSG_CONNECT = 1,
    MSG_GAME    = 2,
    MSG_IGNORED = 3
};

struct Message
{
    Message(uint32_t type_ = 0, uint32_t client_id_ = 0);

    // String representation of a message
    std::string str() const;

    // Type of the message (see MsgType)
    uint32_t type;

    // Id of the client that sent the packet
    // It is ignored for replies
    uint32_t client_id;

    // Size of data to send
    uint32_t size;
};

} // namespace net

std::ostream& operator<<(std::ostream& os, const net::Message& msg);

#endif // !LIB_NET_MESSAGE_HH_