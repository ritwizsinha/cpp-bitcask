#include <gtest/gtest.h>
#include <filesystem>
#include "fileOrchestrator.h"
#include "options.h"


namespace fs = std::filesystem;

TEST(FILEORCHESTRATOR, TEST_DIR_DELETION) {
    bitcask::Options ops;
    ops.removeDir = true;
    const string dirname = "fileOrchtests";
    {
        FileOrchestrator f(dirname, ops);
        EXPECT_EQ(f.getAllFiles().size(), 0);
        EXPECT_EQ(f.getActiveFileId(), "");
        EXPECT_FALSE(f.getActiveStream().is_open());
    }

    for(const auto &entry: fs::directory_iterator(".")) {
        if (fs::is_regular_file(entry)) {
            EXPECT_FALSE(entry.path().filename().string().find(dirname) == 0);
        }
    }
}

TEST(FILEORCHESTRATOR, TEST_DIR_EXISTENCE) {
    bitcask::Options ops;
    ops.removeDir = false;
    const string dirname = "fileOrchtests";
    {
        FileOrchestrator f(dirname, ops);
        f.addNewFile();
        f.addNewFile();
        EXPECT_TRUE(f.getActiveStream().is_open());
        EXPECT_EQ(f.getAllFiles().size(), 2);
    }

    int cnt = 0;
    for(const auto &entry: fs::directory_iterator(".")) {
        if (fs::is_regular_file(entry)) {
            if (entry.path().filename().string().find(dirname) == 0) cnt++;
        }
    }

    EXPECT_EQ(cnt, 2);
    for(const auto &entry: fs::directory_iterator(".")) {
        if (fs::is_regular_file(entry)) {
            if (entry.path().filename().string().find(dirname) == 0) fs::remove_all(entry.path());
        }
    }

}