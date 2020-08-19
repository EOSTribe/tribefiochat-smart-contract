#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/time.hpp>
#include <eosio/singleton.hpp>
#include <eosio/system.hpp>
#include <string>
#include <vector>

using namespace eosio;
using std::string;
using std::vector;

CONTRACT tribefiochat : public contract
{
public:
    using contract::contract;
    tribefiochat(name receiver, name code, datastream<const char *> ds)
        : contract(receiver, code, ds),
          messages(receiver, receiver.value),
          ids(receiver, receiver.value) {}

    ACTION addmessage(string from,
                     string to,
                     string message,
                     name author);              

    uint64_t get_next_id();

private:
    struct id
    {
        uint64_t value;
    };
    typedef singleton<"id"_n, id> id_index;
    id_index ids;

    TABLE message
    {
        uint64_t id;
        string from;
        string to;
        string message;
        name recorder;
        time_point_sec created;
        uint64_t primary_key() const { return id; }
    };
    typedef multi_index<"message"_n, message> message_index;
    message_index messages;

};
