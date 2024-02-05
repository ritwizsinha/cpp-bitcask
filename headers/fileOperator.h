#include "fileOrchestrator.h"
#include "slice.h"
#include "datapacket.h"

struct FileOperator {
    FileOrchestrator orch;
    size_t curFileSize, fileCapacity;
    bitcask::Options ops;
    const string dir;
    unordered_map<Slice, pair<string, size_t>, Slice::HashFunction> offsetMap; 
    FileOperator(
        const string& dir,
        const bitcask::Options ops
    ):  orch(dir, ops), curFileSize(0), fileCapacity(ops.fileSize), ops(ops), dir(dir){}

    auto writeToStream(ofstream & stream, const DataPacket &dp) -> void {
        stream << dp;
        offsetMap.insert({ dp.key, make_pair(orch.getActiveFileId(), curFileSize) });
        curFileSize += dp.getSize();
        stream.flush();
    }
    
    auto getOpenStreamSize(ifstream &stream) const -> size_t {
        if (stream.is_open()) {
            stream.seekg(0, std::ios::end);
            auto fileSize = static_cast<size_t>(stream.tellg());
            stream.seekg(0, std::ios::beg);

            return fileSize;
        }

        return 0;
    }
    auto storeToFile(const DataPacket &dp) -> bool {
        auto& activeStream = orch.getActiveStream();
        auto sizeOfPacket = dp.getSize();
        if (activeStream.is_open() and curFileSize + sizeOfPacket < fileCapacity)  {
            writeToStream(activeStream, dp);
            return true;
        } else {
            orch.addNewFile();
            curFileSize = 0;
            if (activeStream.is_open()) {
                writeToStream(activeStream, dp);
                return true;
            }

        }
        return false;
    }

    auto getValue(const Slice &key, Slice &value) -> bool {
        auto& activeStream = orch.getActiveStream();
        if (offsetMap.contains(key)) {
            DataPacket dp;
            auto filename = offsetMap.at(key).first;
            auto offset = offsetMap.at(key).second;
            
            auto fileHandle = ifstream(filename, std::ios::binary);
            if (fileHandle.is_open()) {
                fileHandle.seekg(offset, std::ios::beg);
                fileHandle >> dp;
                fileHandle.close();
                // std::cout << __LINE__ << " " << dp.value << std::endl;
                value = dp.value;
                // Again workaround so that allocated memory doesn't get cleared.
                // dp.value.isSelfAllocated = false;
                return true;
            }

            return false;
        } else {
            vector<DataPacket> results;
            bool found = false;
            getAllData(results);
            for(auto &entry : results) {
                if (entry.key == key) {
                    value = entry.value;
                    found = true;
                }
            }

            return found;
        }
    }

    auto getAllData(vector<DataPacket> &results) -> void {
        
        for(auto &file : orch.getAllFiles()) {
            vector<DataPacket> temp;
            auto fileHandle = ifstream(file, std::ios::binary);
            if (fileHandle.is_open()) {
                auto fileSize = getOpenStreamSize(fileHandle);
                const auto totalDataPackets = fileSize / sizeof(DataPacket);
                temp.resize(totalDataPackets);

                fileHandle.read(reinterpret_cast<char*>(temp.data()), fileSize);
                for(auto &item : temp) results.emplace_back(item);
            }
        }

    };
};