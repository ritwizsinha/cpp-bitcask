#include <string>
#include <vector>
#include <fstream>

#include "options.h"
#include "datapacket.h"
#include "fileOrchestrator.h"

using std::string;
using std::vector;
using std::ifstream;

template<typename K, typename V>
class Store {
    private:
        const string parentDir;
        const bitcask::Options options; 
        FileOrchestrator orch;
    public:
        Store(const string dirName, const bitcask::Options &opts = {}):parentDir(dirName),options(opts), orch(dirName) {

        }

        auto get(const K& key) -> V {
            vector<DataPacket<K, V>> results;
            orch.getAllData(results);
            
            for(auto &entry : results) {
                cout <<entry.key <<" " << entry.value << endl;
                if (entry.key == key) return entry.value;
            }

            return V();
        }

        auto put(const K& key, const V& value) -> int {
            DataPacket<K, V> dp(key, value);
            orch.storeToFile(dp);
            return 0;
        }

        auto deleteKey(const int &handle, const K& key) -> int {
            return 0;
        };     
};