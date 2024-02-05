#ifndef BITCASK_SLICE_H
#define BITCASK_SLICE_H
#include <string>
#include <stdexcept>
#include <ostream>
#include <cstring>

using std::size_t;
using std::string;
using std::ostream;

struct Slice {
    Slice(): data(0), len(0), isSelfAllocated(false) {};
    Slice(int &datum) : isSelfAllocated(true) {
        len = sizeof(int);
        data = new char[len];
        memcpy(data, &datum, len);
    }
    Slice(double &datum): isSelfAllocated(true) {
        len = sizeof(double);
        data = new char[len];
        memcpy(data, &datum, len);
    }
    Slice(string &s): isSelfAllocated(true) {
        len = s.size();
        data = new char[len];
        memcpy(data, s.data(), len);
    }

    // Slice(int &datum): data(reinterpret_cast<char*>(&datum)), len(sizeof(int)), isSelfAllocated(false) {}
    // Slice(double &datum): data(reinterpret_cast<char*>(&datum)), len(sizeof(double)), isSelfAllocated(false) {}
    Slice(char *ptr, int len): data(ptr), len(len), isSelfAllocated(true) {}
    ~Slice() {
        delete data;
    }
    auto operator=(const Slice& other) -> void {
        this->len = other.len;
        this->data = new char[this->len];
        memcpy(this->data, other.data, this->len);
        this->isSelfAllocated = other.isSelfAllocated;
    }

    Slice(const Slice& other) {
        this->len = other.len;
        this->data = new char[this->len];
        memcpy(this->data, other.data, this->len);
        this->isSelfAllocated = other.isSelfAllocated;
    }

    auto ComputeHash() const -> size_t {
        size_t hashValue = 0;
        for(size_t i = 0; i < len; i++) {
            hashValue ^= static_cast<std::size_t>(data[i]) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        }

        return hashValue;
    }

    struct HashFunction {
        std::size_t operator()(const Slice& sl) const {
            return sl.ComputeHash();
        }
    };

    auto getSize() const -> size_t {
        return len;
    }
    
    auto dataPtr() const  -> char* {
        return data;
    }

    auto operator[](size_t index) const -> char {
        if (index >= len) {
            throw std::runtime_error("Cannot index a slice past the size");
        }

        return data[index];
    }

    auto operator==(const Slice &key) const -> bool {
        if (key.getSize() != this->len) return false;

        return !memcmp(key.dataPtr(), this->data, this->len);
    }

    friend auto operator<<(ostream &os, const Slice &sl) -> ostream& {
        if (sl.len == sizeof(int)) {
            os << *(int*)(sl.data);
        } else if (sl.len == sizeof(double)) {
            os << *(double*)(sl.data);
        } else {
            os.write(sl.dataPtr(), sl.len);
        }

        return os;
    }

    template<typename T>
    auto convert(T &result) -> void {
        memcpy(&result, data, len);
    }

    char * data;
    size_t len;
    bool isSelfAllocated;
};
#endif