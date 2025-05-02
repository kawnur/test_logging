#include "utils.hpp"

QString getRandomString(std::size_t size)
{
    std::string characters { "abcdefghijklmnopqrstuvwxyz0123456789" };
    std::size_t charactersSize = characters.size();

    QString result { "" };

    for (std::size_t s = 0; s < size; s++) {
        result += characters.at(rand() % charactersSize);
    }

    return result;
}
