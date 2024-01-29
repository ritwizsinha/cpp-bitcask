#include <fstream>
#include <vector>
#include <string>
#include <chrono>


using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::to_string;
using std::size_t;
using std::cout;
using std::endl;

struct FileOrchestrator {
    ofstream activeStream;
    size_t activeFileCapacity{10000};
    size_t size;
    const string dir;

    vector<string> files;
    auto flushActiveStream() -> void {
        if (activeStream.is_open()) {
            activeStream.flush();
        }
    }
    auto createNew() -> void {
        auto epochTime = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        auto fileName = dir + "f" + to_string(epochTime);

        files.emplace_back(fileName);
        if (activeStream.is_open()) {
            activeStream.close();
        }

        activeStream = ofstream(fileName, std::ios::binary | std::ios::app);
        size = 0;
    }
    public:
    FileOrchestrator(const string &dir): dir(dir) {}
    ~FileOrchestrator() {

    }
    template<typename K, typename V>
    auto storeToFile(DataPacket<K, V> &dp) -> bool {
        auto sizeOfPacket = sizeof(dp);
        if (activeStream.is_open() and size + sizeOfPacket < activeFileCapacity)  {
            activeStream.write(reinterpret_cast<const char*>(&dp), sizeOfPacket);
            activeStream.flush();
            size += sizeOfPacket;
            return true;
        } else {
            createNew();
            if (activeStream.is_open()) {
                activeStream.write(reinterpret_cast<const char*>(&dp), sizeOfPacket);
                activeStream.flush();
                size+= sizeOfPacket;
                return true;
            }

        }
        return false;
    }


    template<typename K, typename V>
    auto getAllData(vector<DataPacket<K, V>> &results) -> void {

        for(auto &file : files) {
            vector<DataPacket<K, V>> temp;
            auto fileHandle = ifstream(file, std::ios::binary);
            if (fileHandle.is_open()) {
                fileHandle.seekg(0, std::ios::end);
                auto fileSize = static_cast<size_t>(fileHandle.tellg());
                fileHandle.seekg(0, std::ios::beg);

                const auto totalDataPackets = fileSize / sizeof(DataPacket<K, V>);
                temp.resize(totalDataPackets);

                fileHandle.read(reinterpret_cast<char*>(temp.data()), fileSize);
                for(auto &item : temp) results.emplace_back(item);
            }
        }

    };
};