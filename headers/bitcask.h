#include <string>
#include <string_view>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "options.h"

using std::time_t;
using std::size_t;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::vector;
using std::string;
using std::unordered_map;
using std::to_string;
using std::pair;
using std::ofstream;

namespace bitcask {
    auto open(const std::string_view dirName, Options opts) -> KVStore;
    auto open(const std::string_view dirName) -> KVStore;
    
    template<typename K, typename V>
    struct DataPacket {
        // TODO: add a crc to check if the data packet is correct
        time_t timestamp;
        size_t keySize;
        size_t valueSize;
        K key;
        V Value;

        DataPacket(const K& key, const V& value): key(key), value(value) {
            keySize = key.size();
            valueSize = value.size();
            timestamp = system_clock::to_time_t(system_clock::now());
        }
    };


    struct FileOrchestrator {
        unordered_map<string, int> fileMapping;
        ofstream activeFileHandle;
        int totalFiles;
        auto updateActiveFileHandle(const string &filename) -> void {
            if (activeFileHandle.isOpen()) {
                activeFileHandle.close();
            }
            
            activeFileHandle = ofstream(filename, std::ios::binary);
        }
        public:
        FileOrchestrator():totalFiles(0) {};
        auto createNew() -> bool {
            auto epochTime = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
            auto fileName = "f" + to_string(epochTime);
            fileMapping[fileName] = ++totalFiles;
        }

        auto deleteExisting(const string& filename) -> void {
            if (fileMapping.count(filename) > 0) fileMapping.erase(filename);
        }

        auto returnTwoFiles() -> pair<string, string> {

        }
    }

    template<typename K, typename V>
    auto storeToFile(const DataPacket<K, V>& dp, const string& filename) -> bool {
        ofstream outputFile(filename, std::ios::binary);

        if (outputFile.isOpen()) {
            outputFile.write(reinterpret_cast<const char*>(&dp), sizeof(dp));
            outputFile.close();
            return true;
        }

        return false;
    }

    template<typename K, typename V>
    auto storeToFile(const DataPacket<K, V> &dp, const ofstream &fileHandle) -> bool {
        if (fileHandle.isOpen()) {
            outputFile.write(reinterpret_cast<const char*>(&dp), sizeof(dp));
            return true;
        }

        return false;
    }


    template<typename K, typename V>
    auto readDataPacket(const ofstream &fileHandle) -> DataPacket<K, V> {
        DataPacket<K, V> result;
        if (fileHandle.isOpen()) {
            fileHandle.read(reinterpret_cast<char*>(&result), sizeof(result));
        }

`
        return result;
    }

    template<typename K, typename V>
    auto get(const int& handle, const K& key) -> V {

    }
    template<typename K, typename V>
    auto put(const K& key, const V& value) -> int {
        DataPacket<K, V> dp(key, value);
        storeToFile(dp, "data.txt");
    }
    template<typename K>
    auto deleteKey(const int &handle, const K& key) -> int;

}