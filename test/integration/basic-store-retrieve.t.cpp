#include <gtest/gtest.h>
#include <store.h>
#include <options.h>


// TEST(BasicStoreAndRetrieve, PUTGET1ITEM) {
//     bitcask::Options op;
//     op.removeDir = true;

//     Store store("integers1", op);
//     int key = 3;
//     int value =5;

//     store.put(key, value);
//     Slice value2;
//     store.get(key, value2);

//     EXPECT_EQ(Slice(value), value2);
// }

TEST(BasicStoreRetrieve, BasicStoreAndRetrieveINT) {
    bitcask::Options op;
    op.removeDir = true;

    Store store("integers", op);
    for(int i = 0; i < 10; i++) {
        store.put(i, i);
    }
    

    for(int i = 0; i < 3; i++) {
        Slice result;
        store.get(i, result);
        EXPECT_EQ(result, Slice(i));
    }

}


// TEST(BasicStoreRetrieve, BasicStoreAndRetrieveDOUBLE) {
//     bitcask::Options op;
//     op.removeDir = false;

//     Store store("doubles", op);
//     for(int i = 0; i < 10; i++) {
//         double val = 1.0 * i / 10;
//         store.put(i, val);
//     }
    

//     for(int i = 0; i < 10; i++) {
//         double val;
//         store.get(i, val);
//         EXPECT_EQ(val, 1.0*i / 10)  << i;
//     }

//     // const auto val = store.get(100);
//     // EXPECT_EQ(val, 0);
// }