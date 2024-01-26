#include <string>
#include <string_view>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

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
using std::ifstream;
using std::cout;
using std::endl;

namespace bitcask {

    // auto open(const std::string_view dirName, Options opts) -> KVStore;
    // auto open(const std::string_view dirName) -> KVStore;
    
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


    struct FileOrchestrator {
        unordered_map<string, int> fileMapping;
        ofstream activeFileHandle;
        int totalFiles;
        auto updateActiveFileHandle(const string &filename) -> void {
            if (activeFileHandle.is_open()) {
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
        ofstream outputFile(filename, std::ios::binary | std::ios::app);

        if (outputFile.is_open()) {
            outputFile.write(reinterpret_cast<const char*>(&dp), sizeof(dp));
            outputFile.close();
            return true;
        }

        return false;
    }

    template<typename K, typename V>
    auto storeToFile(const DataPacket<K, V> &dp, ofstream &fileHandle) -> bool {
        if (fileHandle.is_open()) {
            fileHandle.write(reinterpret_cast<const char*>(&dp), sizeof(dp));
            return true;
        }
        return false;
    }


    template<typename K, typename V>
    auto getAllData(ifstream &fileHandle, vector<DataPacket<K, V>> &results) -> void {
        if (fileHandle.is_open()) {
            fileHandle.seekg(0, std::ios::end);
            auto fileSize = static_cast<size_t>(fileHandle.tellg());
            fileHandle.seekg(0, std::ios::beg);

            const auto totalDataPackets = fileSize / sizeof(DataPacket<K, V>);
            results.resize(totalDataPackets);

            fileHandle.read(reinterpret_cast<char*>(results.data()), fileSize);
            return;
        }

    }

    template<typename K, typename V>
    auto get(const K& key) -> V {
        vector<DataPacket<K, V>> results;
        ifstream file("data.txt", std::ios::binary);
        getAllData(file, results);

        for(auto &entry : results) {
            if (entry.key == key) return entry.value;
        }

        return V();
    }
    template<typename K, typename V>
    auto put(const K& key, const V& value) -> int {
        DataPacket<K, V> dp(key, value);
        storeToFile(dp, "data.txt");
        return 0;
    }
    template<typename K>
    auto deleteKey(const int &handle, const K& key) -> int {
        return 0;
    };

}