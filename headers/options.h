
#ifndef BITCASK_OPTIONS_H
#define BITCASK_OPTIONS_H

using std::size_t;
namespace bitcask {
    struct Options {
        bool read_write;
        bool sync_on;
        bool removeDir;
        size_t fileSize;
        Options():fileSize(10000) {}
    };
}

#endif