#include <gtest/gtest.h>
#include <store.h>

TEST(BasicStoreRetrieve, BasicStoreAndRetrieveINT) {
    Store<int,int> store("integers");
    for(int i = 0; i < 10; i++) {
        store.put(i, i);
    }
    

    for(int i = 0; i < 10; i++) {
        const auto val = store.get(i);
        EXPECT_EQ(val, i);
    }

    const auto val = store.get(100);
    EXPECT_EQ(val, 0);
}


TEST(BasicStoreRetrieve, BasicStoreAndRetrieveDOUBLE) {
    Store<int, double> store("doubles");
    for(int i = 0; i < 10; i++) {
        store.put(i, 1.0 * i /10);
    }
    

    for(int i = 0; i < 10; i++) {
        const auto val = store.get(i);
        EXPECT_EQ(val, 1.0*i / 10)  << i;
    }

    const auto val = store.get(100);
    EXPECT_EQ(val, 0);
}