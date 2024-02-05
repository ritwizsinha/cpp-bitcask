#include <string>
#include <vector>
#include <fstream>

#include "options.h"
#include "datapacket.h"
#include "fileOperator.h"
#include "slice.h"

using std::string;
using std::vector;
using std::ifstream;

class Store {
    private:
        const string parentDir;
        const bitcask::Options options; 
        FileOperator opr;
    public:
        Store(const string dirName, const bitcask::Options &opts = {}):parentDir(dirName),options(opts), opr(dirName, opts) {

        }

        template<typename K>
        auto get(K& key, Slice &value) -> bool {
            auto k = Slice(key);
            return opr.getValue(k, value);
        }

        template<typename K, typename V>
        auto put(K& key, V& value) -> int {
            auto keySlice = Slice(key);
            auto valueSlice = Slice(value);

            DataPacket dp(keySlice, valueSlice, PacketType::UPDATE);
            opr.storeToFile(dp);
            return 0;
        }

        template<typename K>
        auto deleteKey(const K& key) -> int {
            auto keySlice = Slice(key);
            Slice valueSlice;
            DataPacket dp(keySlice, valueSlice, PacketType::DELETE);

            opr.storeToFile(dp);
            return 0;
        };     
};