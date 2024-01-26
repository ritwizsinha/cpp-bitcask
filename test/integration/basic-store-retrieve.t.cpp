#include <gtest/gtest.h>
#include <bitcask.h>

TEST(BasicStoreRetrieve, BasicStoreAndRetrieve) {
    for(int i = 0; i < 10; i++) {
        bitcask::put(i, i);
    }
    

    for(int i = 0; i < 10; i++) {
        const auto val = bitcask::get<int, int>(i);
        EXPECT_EQ(val, i);
    }

    const auto val = bitcask::get<int, int>(100);
    EXPECT_EQ(val, 0);
}