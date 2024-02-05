#ifndef BITCASK_DATAPACKET_H
#define BITCASK_DATAPACKET_H

#include <chrono>
#include <iostream>
#include <fstream>
#include "slice.h"

using std::time_t;
using std::size_t;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::ostream;
using std::istream;
using std::ofstream;

enum PacketType {
    UPDATE,
    DELETE
};

struct DataPacket {
    // TODO: add a crc to check if the data packet is correct
    time_t timestamp;
    size_t keySize;
    size_t valueSize;
    PacketType packetType;
    Slice key;
    Slice value;

    DataPacket(
        const time_t timestamp,
        const Slice& key,
        const Slice& value,
        const PacketType &pType)
    : timestamp(timestamp), keySize(key.len), valueSize(value.len), packetType(pType), key(key), value(value)  {}

    DataPacket(
        const Slice& key,
        const Slice& value,
        const PacketType& pType
    ):  keySize(key.len), valueSize(value.len), packetType(pType), key(key), value(value) {
        timestamp = system_clock::to_time_t(system_clock::now());
    }
    DataPacket():key(Slice{}),value(Slice{}) {}
    DataPacket(const DataPacket &other) {
        *this = std::move(DataPacket(other));
    }

    friend auto operator<<(ofstream &fs, const DataPacket &dp) -> ofstream& {
        fs.write(reinterpret_cast<const char*>(&dp.timestamp), sizeof(dp.timestamp));
        fs.write(reinterpret_cast<const char*>(&dp.keySize), sizeof(dp.keySize));
        fs.write(reinterpret_cast<const char*>(&dp.valueSize), sizeof(dp.valueSize));
        fs.write(reinterpret_cast<const char*>(&dp.packetType), sizeof(dp.packetType));
        fs.write(dp.key.dataPtr(), dp.keySize);
        fs.write(dp.value.dataPtr(), dp.valueSize);

        return fs;

    }

    friend auto operator<<(ostream& os, const DataPacket &dp) -> ostream& {
        os << dp.timestamp <<" " <<dp.packetType << " " << dp.keySize <<" "<< dp.valueSize << " " << dp.key << " "<<dp.value <<std::endl;
        return os;
    }

    friend auto operator>>(istream &is, DataPacket &dp) -> istream& {
        is.read(reinterpret_cast<char*>(&dp.timestamp), sizeof(dp.timestamp));
        is.read(reinterpret_cast<char*>(&dp.keySize), sizeof(dp.keySize));
        is.read(reinterpret_cast<char*>(&dp.valueSize), sizeof(dp.valueSize));
        is.read(reinterpret_cast<char*>(&dp.packetType), sizeof(dp.packetType));

        Slice keySlice(new char[dp.keySize], dp.keySize);
        Slice valueSlice(new char[dp.valueSize], dp.valueSize);
        is.read(keySlice.dataPtr(), dp.keySize);
        is.read(valueSlice.dataPtr(), dp.valueSize);

        dp.key = keySlice;
        dp.value = valueSlice;
        return is;
    }

    auto operator==(const DataPacket &dp) const -> bool {
        return (
            dp.packetType == this->packetType and
            dp.timestamp == this->timestamp and
            dp.keySize == this->keySize and
            dp.valueSize == this->valueSize and
            dp.key == this->key and
            dp.value == this->value
        );
    }

    auto getSize() const -> size_t {
        return sizeof(time_t) + 2*sizeof(size_t) + sizeof(PacketType) + keySize + valueSize;
    }
};
#endif