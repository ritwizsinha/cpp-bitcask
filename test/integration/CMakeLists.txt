# Test executable
add_executable(bitcask-test
datapacket-store.t.cpp
basic-store-retrieve.t.cpp
file-orch.t.cpp
)

target_compile_options(bitcask-test PUBLIC -g)

# Link libraries if needed
target_link_libraries(bitcask-test PRIVATE
 bitcask
 gtest
 gtest_main
 pthread)

# Optional: Set the output directories for executables
set_target_properties(bitcask-test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_test(NAME bitcask-test COMMAND bitcask-test)