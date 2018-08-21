#ifndef  _HPP_UTILS_HPP_
#define  _HPP_UTILS_HPP_
#include <unordered_map>
#include <chrono>
namespace  ecs
{
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


inline std::time_t getTimeStamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).
		 time_since_epoch() ).count();

}

enum class KeyboradCode
{
	KEY_W = 0x1,
	KEY_S = 0x2,
	KEY_A = 0x3,
	KEY_D = 0x4,
};

}//ecs
#endif
