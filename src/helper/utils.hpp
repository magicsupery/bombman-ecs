#ifndef  _HPP_UTILS_HPP_
#define  _HPP_UTILS_HPP_
#include <unordered_map>

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

template <typename Key>
using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;

template <typename Key, typename T>
using BoomUnorderedMap = std::unordered_map<Key, T, HashType<Key>>;

#endif
