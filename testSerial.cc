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
    ASSERT_EQ(write, static_cast<uint8_t>(read));  
}

TEST(SerialSerializationTest, int8)
{                                                   //faire avec >>
    int8_t write = -42;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_int8.bin");
        file << write;
    }

    std::byte read{};
    {
        serial::IBinaryFile file("test_int8.bin");
        size_t bytes_read = file.read(&read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    ASSERT_EQ(write, static_cast<int8_t>(read));  
}

TEST(SerialSerializationTest, uint16)
{                                                   //faire avec >>
    uint16_t write = 5000;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_uint16.bin");
        file << write;
    }

    std::byte read[2];
    {
        serial::IBinaryFile file("test_uint16.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    uint16_t int_read;
    std::memcpy(&int_read, read, sizeof(uint16_t));
    ASSERT_EQ(write, int_read);
}

TEST(SerialSerializationTest, int16)
{                                                   //faire avec >>
    int16_t write = -5000;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_int16.bin");
        file << write;
    }

    std::byte read[2];
    {
        serial::IBinaryFile file("test_int16.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    int16_t int_read;
    std::memcpy(&int_read, read, sizeof(int16_t));
    ASSERT_EQ(write, int_read);
}

TEST(SerialSerializationTest, uint32)
{                                                   //faire avec >>
    uint32_t write = 70000;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_uint32_t.bin");
        file << write;
    }

    std::byte read[4];
    {
        serial::IBinaryFile file("test_uint32_t.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    uint32_t int_read;
    std::memcpy(&int_read, read, sizeof(uint32_t));
    ASSERT_EQ(write, int_read);
}

TEST(SerialSerializationTest, int32)
{                                                   //faire avec >>
    int32_t write = -70000;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_int32_t.bin");
        file << write;
    }

    std::byte read[4];
    {
        serial::IBinaryFile file("test_int32_t.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    int32_t int_read;
    std::memcpy(&int_read, read, sizeof(int32_t));
    ASSERT_EQ(write, int_read);
}

TEST(SerialSerializationTest, uint64)
{                                                   //faire avec >>
    uint64_t write = 70000;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_uint64_t.bin");
        file << write;
    }

    std::byte read[8];
    {
        serial::IBinaryFile file("test_uint64_t.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    uint64_t int_read;
    std::memcpy(&int_read, read, sizeof(uint64_t));
    ASSERT_EQ(write, int_read);
}

TEST(SerialSerializationTest, int64)
{                                                   //faire avec >>
    int64_t write = -70000;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_int64_t.bin");
        file << write;
    }

    std::byte read[8];
    {
        serial::IBinaryFile file("test_int64_t.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    int64_t int_read;
    std::memcpy(&int_read, read, sizeof(int64_t));
    ASSERT_EQ(write, int_read);
}

TEST(SerialSerializationTest, character)
{                                                   //faire avec >>
    char write = 'a';
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_char.bin");
        file << write;
    }

    std::byte read{};
    {
        serial::IBinaryFile file("test_char.bin");
        size_t bytes_read = file.read(&read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    ASSERT_EQ(write, static_cast<char>(read));
}

TEST(SerialSerializationTest, float_)
{                                                   //faire avec >>
    float write = 1.0e-45f;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_float.bin");
        file << write;
    }

    std::byte read[4];
    {
        serial::IBinaryFile file("test_float.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    float float_read;
    std::memcpy(&float_read, read, sizeof(float));
    ASSERT_EQ(write, float_read);
}

TEST(SerialSerializationTest, double_)
{                                                   //faire avec >>
    double write = 7.23671;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_double.bin");
        file << write;
    }

    std::byte read[8];
    {
        serial::IBinaryFile file("test_double.bin");
        uint bytes_read = file.read(read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    double double_read;
    std::memcpy(&double_read, read, sizeof(double));
    ASSERT_EQ(write, double_read);
}

TEST(SerialSerializationTest, boolean)
{                                                   //faire avec >>
    bool write = true;
    size_t s_write = sizeof(write);
    {
        serial::OBinaryFile file("test_bool.bin");
        file << write;
    }

    std::byte read{};
    {
        serial::IBinaryFile file("test_bool.bin");
        size_t bytes_read = file.read(&read, s_write);
        ASSERT_EQ(bytes_read, s_write);
    }
    ASSERT_EQ(write, static_cast<bool>(read));
}

TEST(SerialSerializationTest, string)
{                                                   //faire avec >>
    std::string write = "the string";
    size_t s_write = write.size();
    size_t size = sizeof(s_write);

    {
        serial::OBinaryFile file("test_string.bin");
        file << write;
    }

    std::byte read_size[size];
    std::string string_read;
    {
        serial::IBinaryFile file("test_string.bin");

        file.read(read_size, size);

        size_t s_read = 0;
        std::memcpy(&s_read, &read_size, size);

        std::byte read_string[s_read];
        uint bytes_read = file.read(read_string, s_read);
        for (const auto& byte : read_string) {
            char c = static_cast<char>(byte);
            string_read += c;
        }
        ASSERT_EQ(bytes_read, s_read);
    }

    ASSERT_EQ(write, string_read);
}

/*
OBinaryFile &operator<<(OBinaryFile &file, const std::vector<T> &x)
OBinaryFile &operator<<(OBinaryFile &file, const std::array<T, N> &x)
OBinaryFile &operator<<(OBinaryFile &file, const std::map<K, V> &x)
OBinaryFile &operator<<(OBinaryFile &file, const std::set<T> &x)
*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    // deleteFilesTests();
}
