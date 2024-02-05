#ifndef FILE_ORCHESTRATOR_H
#define FILE_ORCHESTRATOR_H

#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <unordered_map>
#include <utility>
#include "options.h"


using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::to_string;
using std::size_t;
using std::cout;
using std::endl;
using std::unordered_map;
using std::pair;
using std::make_pair;

namespace fs = std::filesystem;


struct FileOrchestrator {
    ofstream activeStream;
    bitcask::Options ops;
    vector<string> files;
    const string dir;

    auto getAllFiles() -> const vector<string> {
        return files;
    }

    auto getActiveStream() -> ofstream& {
        return activeStream;
    }

    auto deleteFilesWithPrefix() -> void {
        try {
            for (const auto& entry : fs::directory_iterator(".")) {
                if (fs::is_regular_file(entry) && entry.path().filename().string().find(dir) == 0) {
                    fs::remove(entry.path());
                    std::cout << "Deleted: " << entry.path() << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;    
        }
    }

    FileOrchestrator(
        const string &dir,
        const bitcask::Options &ops
    ): ops(ops),dir(dir)  {
        try {
            for (const auto& entry : fs::directory_iterator(".")) {
                if (fs::is_regular_file(entry) && entry.path().filename().string().find(dir) == 0) {
                    files.emplace_back(entry.path().filename());
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;    
        }
    }
    ~FileOrchestrator() {
        if (ops.removeDir) {
            deleteFilesWithPrefix();
        }
        if (activeStream.is_open()) activeStream.close();
    }

    auto addNewFile() -> bool {
        auto epochTime = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        auto fileName = dir + "f" + to_string(epochTime);

        files.emplace_back(fileName);
        if (activeStream.is_open()) {
            activeStream.close();
        }

        activeStream = ofstream(fileName, std::ios::binary | std::ios::app);

        return true;
    }

    auto getActiveFileId() -> string {
        return files.size() ? files.back() : "";
    }
};
#endif