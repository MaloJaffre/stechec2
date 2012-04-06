#include "socket.hh"

#include <stdexcept>

#include <utils/log.hh>
#include <net/message.hh>

namespace net {

Socket::Socket(const std::string& pubsub_addr,
               const std::string& reqrep_addr,
               int io_thread)
    : pubsub_addr_(pubsub_addr),
      reqrep_addr_(reqrep_addr),
      ctx_(io_thread)
{
}

bool Socket::send(const Message& msg)
{
    try
    {
        zmq::message_t zmsg(sizeof (Message) + msg.size);
        memcpy(zmsg.data(), &msg, sizeof (Message) + msg.size);

        if (!reqrep_sckt_->send(zmsg))
            throw std::runtime_error("Could not send message");

        return true;
    }
    catch(const std::exception& e)
    {
        ERR("%s", e.what());
        return false;
    }
}

Message* Socket::recv()
{
    try
    {
        zmq::message_t zmsg;

        if (!reqrep_sckt_->recv(&zmsg))
            throw std::runtime_error("Could not get message");

        Message* msg = reinterpret_cast<Message*>(new char[zmsg.size()]);
        memcpy(msg, zmsg.data(), zmsg.size());

        return msg;
    }
    catch(const std::exception& e)
    {
        ERR("%s", e.what());
        return nullptr;
    }
}

} // namespace net
