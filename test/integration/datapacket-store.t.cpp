#include <gtest/gtest.h>
#include <fstream>
#include "datapacket.h"
#include "slice.h"

using std::ofstream;
using std::ifstream;
TEST(DataPacketTests, WriteDataPacketSSToStream) {
    ofstream f("data.txt", std::ios::binary);
    string key = "hello", value = "bye";
    auto keySlice = Slice(key);
    auto valueSlice = Slice(value);
    DataPacket dp(0, keySlice, valueSlice, PacketType::UPDATE);

    f << dp;
    f.close();

    ifstream f2("data.txt", std::ios::binary);
    DataPacket dp2;

    f2>> dp2;

    EXPECT_TRUE(dp == dp2) << dp << std::endl << dp2;

    f2.close();
}

TEST(DataPacketTests, WriteDataPacketSIToStream) {
    ofstream f("data.txt", std::ios::binary);
    string key = "hello";
    int value = 2;
    auto keySlice = Slice(key);
    auto valueSlice = Slice(value);
    DataPacket dp(0, keySlice, valueSlice, PacketType::UPDATE);

    f << dp;
    f.close();

    ifstream f2("data.txt", std::ios::binary);
    DataPacket dp2;

    f2 >> dp2;

    EXPECT_TRUE(dp == dp2) << dp << std::endl << dp2;

    f2.close();
}

TEST(DataPacketTests, WriteDataPacketSDToStream) {
    ofstream f("data.txt", std::ios::binary);
    string key = "hello";
    double value = 4.53993;
    auto keySlice = Slice(key);
    auto valueSlice = Slice(value);
    DataPacket dp(0, keySlice, valueSlice, PacketType::UPDATE);

    f << dp;
    f.close();

    ifstream f2("data.txt", std::ios::binary);
    DataPacket dp2;

    f2>> dp2;

    EXPECT_TRUE(dp == dp2) << dp << std::endl << dp2;

    f2.close();
}

TEST(DataPacketTests, WriteDataPacketDeleteTypeToStream) {
    ofstream f("data.txt", std::ios::binary);
    string key = "hello";
    auto keySlice = Slice(key);
    auto valueSlice = Slice();
    DataPacket dp(0, keySlice, valueSlice, PacketType::DELETE);

    f << dp;
    f.close();

    ifstream f2("data.txt", std::ios::binary);
    DataPacket dp2;

    f2>> dp2;

    EXPECT_TRUE(dp == dp2) << dp << std::endl << dp2;

    f2.close();
}


TEST(DataPacketTests, WriteDataPacketIIToStream) {
    ofstream f("data.txt", std::ios::binary);
    int key = 1;
    int value = 2;
    auto keySlice = Slice(key);
    auto valueSlice = Slice(value);

    DataPacket dp(0, keySlice, valueSlice, PacketType::DELETE);
    f << dp;
    f.close();

    ifstream f2("data.txt", std::ios::binary);
    DataPacket dp2;

    f2>> dp2;

    EXPECT_TRUE(dp == dp2) << dp << std::endl << dp2;

    f2.close();
}

TEST(DataPacketTests, WriteDataPacketDDToStream) {
    ofstream f("data.txt", std::ios::binary);
    double key = 1.2323;
    double value = 2.24234;
    auto keySlice = Slice(key);
    auto valueSlice = Slice(value);

    DataPacket dp(0, keySlice, valueSlice, PacketType::DELETE);
    f << dp;
    f.close();

    ifstream f2("data.txt", std::ios::binary);
    DataPacket dp2;

    f2>>dp2;

    EXPECT_TRUE(dp == dp2) << dp << std::endl << dp2;

    f2.close();
}