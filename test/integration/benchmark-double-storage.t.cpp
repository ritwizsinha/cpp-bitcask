#include <gtest/gtest.h>
// #include <store.h>
// #include <options.h>
// #include <chrono>

// using std::chrono::high_resolution_clock;
// using std::chrono::duration_cast;

// TEST(BasicStoreRetrieve, BenchmarkFileSize1000) {
//     bitcask::Options op;
//     op.fileSize = 1000;
//     auto start = high_resolution_clock::now();

//     Store<int, double> store("benchmarkfilesize1000", op);
//     // for(int i = 0; i < 10000; i++) {
//     //     store.put(i, 1.0 * i /10);
//     // }
    

//     for(int i = 0; i < 10000; i++) {
//         const auto val = store.get(i);
//         EXPECT_EQ(val, 1.0*i / 10)  << i;
//     }


//     auto end = high_resolution_clock::now();

//     auto duration = duration_cast<std::chrono::nanoseconds>(end - start);

//     std::cout << "Time Taken: " << duration.count() * 0.000001<< "milliseconds" <<std::endl;


// }
