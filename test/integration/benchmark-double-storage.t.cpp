#include <gtest/gtest.h>
#include <store.h>
#include <options.h>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

TEST(BasicStoreRetrieve, BenchmarkFileSize1000) {
    bitcask::Options op;
    op.fileSize = 1000000;
    auto start = high_resolution_clock::now();

    Store store("benchmarkfilesize1000", op);
    for(int i = 0; i < 1000000; i++) {
        auto val =  1.0 * i /10;
        store.put(i, val);
    }
    

    for(int i = 0; i < 100000; i++) {
        Slice x;
        auto y = store.get(i, x);
        auto result = 1.0*i / 10;
        EXPECT_EQ(x, Slice(result))  << i;
    }


    auto end = high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Time Taken: " << duration.count() * 0.000001<< "milliseconds" <<std::endl;


}
