#include <tribefiochat.hpp>

uint64_t tribefiochat::get_next_id()
{
    id next_id{ids.exists() ? ids.get().value + 1 : 1};
    ids.set(next_id, get_self());
    return next_id.value;
}

void tribefiochat::addmessage(string from,
                     string to,
                     string message,
                     name author)
{
    require_auth(author);
    check(author.to_string() == "fiomsglogger", "user unauthorized to add message");
    check(!from.empty(), "from address field cannot be empty");
    check(!to.empty(), "to address field cannot be empty");
    check(!message.empty(), "message cannot be empty");
    messages.emplace(get_self(), [&](auto &row) {
        row.id = get_next_id();
        row.from = from;
        row.to = to;
        row.message = message;
        row.recorder = author;
        row.created = time_point_sec(current_time_point());
    });

}







