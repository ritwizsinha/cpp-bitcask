// #include <string>
// #include <string_view>
// #include <chrono>
// #include <vector>
// #include <unordered_map>
// #include <fstream>
// #include <iostream>

// #include "options.h"

// using std::time_t;
// using std::size_t;
// using std::chrono::system_clock;
// using std::vector;
// using std::string;
// using std::unordered_map;
// using std::to_string;
// using std::pair;
// using std::ofstream;
// using std::ifstream;
// using std::cout;
// using std::endl;

// namespace bitcask {

//     auto open(const std::string_view dirName, Options opts) -> KVStore;
//     // auto open(const std::string_view dirName) -> KVStore;
    



//     // struct FileOrchestrator {
//     //     unordered_map<string, int> fileMapping;
//     //     ofstream activeFileHandle;
//     //     int totalFiles;
//     //     auto updateActiveFileHandle(const string &filename) -> void {
//     //         if (activeFileHandle.is_open()) {
//     //             activeFileHandle.close();
//     //         }
            
//     //         activeFileHandle = ofstream(filename, std::ios::binary);
//     //     }
//     //     public:
//     //     FileOrchestrator():totalFiles(0) {};
//     //     auto createNew() -> bool {
//     //         fileMapping[fileName] = ++totalFiles;
//     //     }

//     //     auto deleteExisting(const string& filename) -> void {
//     //         if (fileMapping.count(filename) > 0) fileMapping.erase(filename);
//     //     }

//     //     auto returnTwoFiles() -> pair<string, string> {

//     //     }
//     // }

//     template<typename K, typename V>
//     auto storeToFile(const DataPacket<K, V>& dp, const string& filename) -> bool {
//         ofstream outputFile(filename, std::ios::binary | std::ios::app);

//         if (outputFile.is_open()) {
//             outputFile.write(reinterpret_cast<const char*>(&dp), sizeof(dp));
//             outputFile.close();
//             return true;
//         }

//         return false;
//     }

//     template<typename K, typename V>
//     auto storeToFile(const DataPacket<K, V> &dp, ofstream &fileHandle) -> bool {
//         if (fileHandle.is_open()) {
//             fileHandle.write(reinterpret_cast<const char*>(&dp), sizeof(dp));
//             return true;
//         }
//         return false;
//     }


//     template<typename K, typename V>
//     auto getAllData(ifstream &fileHandle, vector<DataPacket<K, V>> &results) -> void {
//         if (fileHandle.is_open()) {
//             fileHandle.seekg(0, std::ios::end);
//             auto fileSize = static_cast<size_t>(fileHandle.tellg());
//             fileHandle.seekg(0, std::ios::beg);

//             const auto totalDataPackets = fileSize / sizeof(DataPacket<K, V>);
//             results.resize(totalDataPackets);

//             fileHandle.read(reinterpret_cast<char*>(results.data()), fileSize);
//             return;
//         }

//     }



// }