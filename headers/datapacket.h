#include <chrono>

using std::time_t;
using std::size_t;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;


template<typename K, typename V>
struct DataPacket {
    // TODO: add a crc to check if the data packet is correct
    time_t timestamp;
    size_t keySize;
    size_t valueSize;
    K key;
    V value;

    DataPacket(const K& key, const V& value): key(key), value(value) {
        keySize = sizeof(key);
        valueSize = sizeof(value);
        timestamp = system_clock::to_time_t(system_clock::now());
    }

    DataPacket():key(K{}),value(V{}) {}
};