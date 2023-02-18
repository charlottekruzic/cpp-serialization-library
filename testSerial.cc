#include "Serial.h"

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST(SerialWriteTest, Default)
{
    serial::OBinaryFile file("test_write.bin");
    const std::byte b{42};
    size_t bytes_written = file.write(&b, 1);
    ASSERT_EQ(bytes_written, 1u);
}

TEST(SerialReadTest, Default)
{
    serial::IBinaryFile file("test_write.bin");
    std::byte b{};
    size_t bytes_read = file.read(&b, 1);
    ASSERT_EQ(bytes_read, 1u);
    ASSERT_EQ(42, static_cast<int>(b));
    // std::cout << "read : " << static_cast <int>(b) << '\n';
}

TEST(SerialSerializationTest, uint8)
{                                                   //faire avec >>
    uint8_t write = 42;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_uint8.bin");
        file << write;
    }

    std::byte read{};
    {
        serial::IBinaryFile file("test_uint8.bin");
        size_t bytes_read = file.read(&read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    ASSERT_EQ(write, static_cast<int>(read));  
}

/*
    OBinaryFile &operator<<(OBinaryFile &file, int8_t x);
    OBinaryFile &operator<<(OBinaryFile &file, uint16_t x);
    OBinaryFile &operator<<(OBinaryFile &file, int16_t x);
    OBinaryFile &operator<<(OBinaryFile &file, uint32_t x);
    OBinaryFile &operator<<(OBinaryFile &file, int32_t x);
    OBinaryFile &operator<<(OBinaryFile &file, uint64_t x);
    OBinaryFile &operator<<(OBinaryFile &file, int64_t x);
    OBinaryFile &operator<<(OBinaryFile &file, char x);
    OBinaryFile &operator<<(OBinaryFile &file, float x);
    OBinaryFile &operator<<(OBinaryFile &file, double x);
    OBinaryFile &operator<<(OBinaryFile &file, bool x);
    OBinaryFile &operator<<(OBinaryFile &file, const std::string &x);

*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    // deleteFilesTests();
}
