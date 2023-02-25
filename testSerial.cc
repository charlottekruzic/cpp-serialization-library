#include "Serial.h"

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

/***********************************************************************************
 *                                  Functions
 ***********************************************************************************/

/**
 * Create a path for a temporary file
 */
fs::path createPathFile(std::string file_name)
{
    fs::path directory_path = fs::temp_directory_path();
    std::filesystem::path file_path = directory_path;
    file_path.append(file_name);
    return file_path;
}

/**
 * Delete a temporary file
 */
void deleteFile(const fs::path &file_path)
{
    if (fs::exists(file_path))
    {
        fs::remove(file_path);
    }
}

/***********************************************************************************
 *                                  Tests
 ***********************************************************************************/

/**
 * Write & Read tests
 */
TEST(writeReadTest, OneByte)
{
    fs::path name = createPathFile("test_write_read_1.bin");

    // Write to file
    {
        std::byte b{'a'};
        serial::OBinaryFile file(name);
        size_t bytes_written = file.write(&b, 1);
        ASSERT_EQ(bytes_written, 1u);
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    {
        std::byte read{};
        serial::IBinaryFile file(name);
        size_t bytes_read = file.read(&read, 1);
        ASSERT_EQ(bytes_read, 1u);
        ASSERT_EQ(static_cast<char>(read), 'a');
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    deleteFile(name);
}

TEST(writeReadTest, ManyBytes)
{
    fs::path name = createPathFile("test_write_read_2.bin");

    // Write to file
    {
        std::byte b[3] = {std::byte(1), std::byte(2), std::byte(3)};
        serial::OBinaryFile file(name);
        size_t bytes_written = file.write(b, 3);
        ASSERT_EQ(bytes_written, 3u);
    }
    ASSERT_EQ(fs::file_size(name), 3u);

    // Reading the file
    {
        std::byte read{};
        serial::IBinaryFile file(name);
        size_t bytes_read = file.read(&read, 1);
        ASSERT_EQ(bytes_read, 1u);
        ASSERT_EQ(1, static_cast<int>(read));

        bytes_read = file.read(&read, 1);
        ASSERT_EQ(bytes_read, 1u);
        ASSERT_EQ(2, static_cast<int>(read));

        bytes_read = file.read(&read, 1);
        ASSERT_EQ(bytes_read, 1u);
        ASSERT_EQ(3, static_cast<int>(read));
    }
    ASSERT_EQ(fs::file_size(name), 3u);

    deleteFile(name);
}

/**
 * Write & Mode tests
 */

TEST(writeModeTest, WriteAppend)
{
    fs::path name = createPathFile("test_write_1.bin");

    // Write to file
    {
        std::byte b{1};
        serial::OBinaryFile file(name);
        size_t bytes_written = file.write(&b, 1);
        ASSERT_EQ(bytes_written, 1u);
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    {
        std::byte b[3] = {std::byte(1), std::byte(2), std::byte(3)};
        serial::OBinaryFile file(name, serial::OBinaryFile::Mode::Append);
        size_t bytes_written = file.write(b, 3);
        ASSERT_EQ(bytes_written, 3u);
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    uint8_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(1, read1);
    ASSERT_EQ(1, read2);
    ASSERT_EQ(2, read3);
    ASSERT_EQ(3, read4);

    deleteFile(name);
}

TEST(writeModeTest, WriteTruncate)
{
    fs::path name = createPathFile("test_write_2.bin");

    // Write to file
    {
        std::byte b{1};
        serial::OBinaryFile file(name);
        size_t bytes_written = file.write(&b, 1);
        ASSERT_EQ(bytes_written, 1u);
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    {
        std::byte b[3] = {std::byte(1), std::byte(2), std::byte(3)};
        serial::OBinaryFile file(name, serial::OBinaryFile::Mode::Truncate);
        size_t bytes_written = file.write(b, 3);
        ASSERT_EQ(bytes_written, 3u);
    }
    ASSERT_EQ(fs::file_size(name), 3u);

    {
        std::byte b{4};
        serial::OBinaryFile file(name, serial::OBinaryFile::Mode::Truncate);
        size_t bytes_written = file.write(&b, 1);
        ASSERT_EQ(bytes_written, 1u);
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    uint8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(4, read);
    ASSERT_EQ(fs::file_size(name), 1u);

    deleteFile(name);
}

TEST(writeModeTest, WriteTruncateAndAppend)
{
    fs::path name = createPathFile("test_write_3.bin");

    // Write to file
    {
        std::byte b{1};
        serial::OBinaryFile file(name);
        size_t bytes_written = file.write(&b, 1);
        ASSERT_EQ(bytes_written, 1u);
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    {
        std::byte b[3] = {std::byte(1), std::byte(2), std::byte(3)};
        serial::OBinaryFile file(name, serial::OBinaryFile::Mode::Truncate);
        size_t bytes_written = file.write(b, 3);
        ASSERT_EQ(bytes_written, 3u);
    }
    ASSERT_EQ(fs::file_size(name), 3u);

    {
        std::byte b{4};
        serial::OBinaryFile file(name, serial::OBinaryFile::Mode::Append);
        size_t bytes_written = file.write(&b, 1);
        ASSERT_EQ(bytes_written, 1u);
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    uint8_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(1, read1);
    ASSERT_EQ(2, read2);
    ASSERT_EQ(3, read3);
    ASSERT_EQ(4, read4);
    ASSERT_EQ(fs::file_size(name), 4u);

    deleteFile(name);
}

/**
 * uint8_t tests
 */
TEST(uint8Test, Default)
{
    fs::path name = createPathFile("test_uint8_1.bin");

    // Write to file
    uint8_t write = 42;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    uint8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint8Test, Minimum)
{
    fs::path name = createPathFile("test_uint8_2.bin");

    // Write to file
    uint8_t write = 0;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    uint8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint8Test, Maximal)
{
    fs::path name = createPathFile("test_uint8_3.bin");

    // Write to file
    uint8_t write = 255;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    uint8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint8Test, Many)
{
    fs::path name = createPathFile("test_uint8_4.bin");

    // Write to file
    uint8_t write1 = 1;
    uint8_t write2 = 2;
    uint8_t write3 = 3;
    uint8_t write4 = 4;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    uint8_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

/**
 * int8_t tests
 */

TEST(int8Test, Negative)
{
    fs::path name = createPathFile("test_int8_1.bin");

    // Write to file
    int8_t write = -42;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int8Test, Positive)
{
    fs::path name = createPathFile("test_int8_2.bin");

    // Write to file
    int8_t write = 42;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int8Test, Minimum)
{
    fs::path name = createPathFile("test_int8_3.bin");

    // Write to file
    int8_t write = -128;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int8Test, Maximum)
{
    fs::path name = createPathFile("test_int8_4.bin");

    // Write to file
    int8_t write = 127;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int8Test, Null)
{
    fs::path name = createPathFile("test_int8_5.bin");

    // Write to file
    int8_t write = 0;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int8Test, Many)
{
    fs::path name = createPathFile("test_int8_6.bin");

    // Write to file
    int8_t write1 = 1;
    int8_t write2 = 2;
    int8_t write3 = 3;
    int8_t write4 = 4;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    int8_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

/**
 * uint16 tests
 */

TEST(uint16Test, Default)
{
    fs::path name = createPathFile("test_uint16_1.bin");

    // Write to file
    uint16_t write = 5000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 2u);

    // Reading the file
    uint16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint16Test, Maximum)
{
    fs::path name = createPathFile("test_uint16_2.bin");

    // Write to file
    uint16_t write = 65535;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 2u);

    // Reading the file
    uint16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint16Test, Minimum)
{
    fs::path name = createPathFile("test_uint16_3.bin");

    // Write to file
    uint16_t write = 0;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 2u);

    // Reading the file
    uint16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint16Test, Many)
{
    fs::path name = createPathFile("test_uint16_4.bin");

    // Write to file
    uint16_t write1 = 1;
    uint16_t write2 = 223;
    uint16_t write3 = 34242;
    uint16_t write4 = 43141;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    uint16_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(uint16Test, Endianness)
{
    fs::path name = createPathFile("test_uint16_5.bin");

    // Write to file
    uint16_t write1 = 42;
    {
        serial::OBinaryFile file(name);
        file << write1;
    }

    // Reading the file
    char b[2];
    std::ifstream f(name, std::ios::binary);
    f.read(b, 2);
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x2a);

    deleteFile(name);
}

/**
 * int16 tests
 */

TEST(int16Test, Negative)
{
    fs::path name = createPathFile("test_int16_1.bin");

    // Write to file
    int16_t write = -5000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 2u);

    // Reading the file
    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int16Test, Positive)
{
    fs::path name = createPathFile("test_int16_2.bin");

    // Write to file
    int16_t write = 5000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 2u);

    // Reading the file
    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int16Test, Minimum)
{
    fs::path name = createPathFile("test_int16_3.bin");

    // Write to file
    int16_t write = -32768;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 2u);

    // Reading the file
    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int16Test, Maximum)
{
    fs::path name = createPathFile("test_int16_4.bin");

    // Write to file
    int16_t write = 32767;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 2u);

    // Reading the file
    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int16Test, Many)
{
    fs::path name = createPathFile("test_int16_5.bin");

    // Write to file
    int16_t write1 = 1;
    int16_t write2 = 223;
    int16_t write3 = -3242;
    int16_t write4 = 43141;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    int16_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(int16Test, Endianness)
{
    fs::path name = createPathFile("test_int16_5.bin");

    // Write to file
    int16_t write1 = 42;
    {
        serial::OBinaryFile file(name);
        file << write1;
    }

    // Reading the file
    char b[2];
    std::ifstream f(name, std::ios::binary);
    f.read(b, 2);
    ASSERT_EQ(fs::file_size(name), 2u);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x2a);

    deleteFile(name);
}

/**
 * uint32 tests
 */

TEST(uint32Test, Default)
{
    fs::path name = createPathFile("test_uint32_1.bin");

    // Write to file
    uint32_t write = 70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    uint32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint32Test, Minimum)
{
    fs::path name = createPathFile("test_uint32_2.bin");

    // Write to file
    uint32_t write = 0;

    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    uint32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint32Test, Maximum)
{
    fs::path name = createPathFile("test_uint32_3.bin");

    // Write to file
    uint32_t write = 0xFFFFFFFF;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    uint32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint32Test, Many)
{
    fs::path name = createPathFile("test_uint32_4.bin");

    // Write to file
    uint32_t write1 = 1;
    uint32_t write2 = 0xFF13;
    uint32_t write3 = 1332;
    uint32_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 16u);

    // Reading the file
    uint32_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 16u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(uint32Test, Endianness)
{
    fs::path name = createPathFile("test_uint32_5.bin");

    // Write to file
    uint32_t write1 = 0x235F01;
    {
        serial::OBinaryFile file(name);
        file << write1;
    }

    // Reading the file
    char b[4];
    std::ifstream f(name, std::ios::binary);
    f.read(b, 4);
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x23);
    ASSERT_EQ(static_cast<uint8_t>(b[2]), 0x5F);
    ASSERT_EQ(static_cast<uint8_t>(b[3]), 0x01);

    deleteFile(name);
}

/**
 * int32 tests
 */

TEST(int32Test, Negative)
{
    fs::path name = createPathFile("test_int32_1.bin");

    // Write to file
    int32_t write = -70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int32Test, Positive)
{
    fs::path name = createPathFile("test_int32_2.bin");

    // Write to file
    int32_t write = 70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int32Test, Minimum)
{
    fs::path name = createPathFile("test_int32_3.bin");

    // Write to file
    int32_t write = 0X80000000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int32Test, Maximum)
{
    fs::path name = createPathFile("test_int32_4.bin");

    // Write to file
    int32_t write = 0X7FFFFFFF;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int32Test, Many)
{
    fs::path name = createPathFile("test_int32_5.bin");

    // Write to file
    int32_t write1 = 1;
    int32_t write2 = 0xFF1;
    int32_t write3 = 0x0FFF9;
    int32_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 16u);

    // Reading the file
    int32_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 16u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(int32Test, Endianness)
{
    fs::path name = createPathFile("test_int32_6.bin");

    // Write to file
    int32_t write1 = 0x235F01;
    {
        serial::OBinaryFile file(name);
        file << write1;
    }

    // Reading the file
    char b[4];
    std::ifstream f(name, std::ios::binary);
    f.read(b, 4);
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x23);
    ASSERT_EQ(static_cast<uint8_t>(b[2]), 0x5F);
    ASSERT_EQ(static_cast<uint8_t>(b[3]), 0x01);

    deleteFile(name);
}

/**
 * uint64 tests
 */

TEST(uint64Test, Default)
{
    fs::path name = createPathFile("test_uint64_1.bin");

    // Write to file
    uint64_t write = 70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    uint64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint64Test, Minimum)
{
    fs::path name = createPathFile("test_uint64_2.bin");

    // Write to file
    uint64_t write = 0;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    uint64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint64Test, Maximum)
{
    fs::path name = createPathFile("test_uint64_3.bin");

    // Write to file
    uint64_t write = 0xFFFFFFFFFFFFFFFF;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    uint64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(uint64Test, Many)
{
    fs::path name = createPathFile("test_uint64_4.bin");

    // Write to file
    uint64_t write1 = 1;
    uint64_t write2 = 0xFF13;
    uint64_t write3 = 0xFFF9;
    uint64_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 32u);

    // Reading the file
    uint64_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 32u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(uint64Test, Endianness)
{
    fs::path name = createPathFile("test_uint64_5.bin");

    // Write to file
    uint64_t write1 = 0x123456789;
    {
        serial::OBinaryFile file(name);
        file << write1;
    }

    // Reading the file
    char b[8];
    std::ifstream f(name, std::ios::binary);
    f.read(b, 8);
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[2]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[3]), 0x01);
    ASSERT_EQ(static_cast<uint8_t>(b[4]), 0x23);
    ASSERT_EQ(static_cast<uint8_t>(b[5]), 0x45);
    ASSERT_EQ(static_cast<uint8_t>(b[6]), 0x67);
    ASSERT_EQ(static_cast<uint8_t>(b[7]), 0x89);

    deleteFile(name);
}

/**
 * int64 tests
 */

TEST(int64Test, Negative)
{
    fs::path name = createPathFile("test_int64_1.bin");

    // Write to file
    int64_t write = -70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int64Test, Positive)
{
    fs::path name = createPathFile("test_int64_2.bin");

    // Write to file
    int64_t write = -70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int64Test, Minimum)
{
    fs::path name = createPathFile("test_int64_3.bin");

    // Write to file
    int64_t write = -70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int64Test, Maximum)
{
    fs::path name = createPathFile("test_int64_4.bin");

    // Write to file
    int64_t write = -70000;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(int64Test, Many)
{
    fs::path name = createPathFile("test_int64_5.bin");

    // Write to file
    int64_t write1 = -12;
    int64_t write2 = 0x8F123;
    int64_t write3 = 0x7FF9A;
    int64_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 32u);

    // Reading the file
    int64_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 32u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(int64Test, Endianness)
{
    fs::path name = createPathFile("test_int64_6.bin");

    // Write to file
    int64_t write1 = 0x123456789;
    {
        serial::OBinaryFile file(name);
        file << write1;
    }

    // Reading the file
    char b[8];
    std::ifstream f(name, std::ios::binary);
    f.read(b, 8);
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[2]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[3]), 0x01);
    ASSERT_EQ(static_cast<uint8_t>(b[4]), 0x23);
    ASSERT_EQ(static_cast<uint8_t>(b[5]), 0x45);
    ASSERT_EQ(static_cast<uint8_t>(b[6]), 0x67);
    ASSERT_EQ(static_cast<uint8_t>(b[7]), 0x89);

    deleteFile(name);
}

/**
 * char tests
 */

TEST(charTest, Default)
{
    fs::path name = createPathFile("test_char_1.bin");

    // Write to file
    char write = 'a';
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    char read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(charTest, newlineChar)
{
    fs::path name = createPathFile("test_char_2.bin");

    // Write to file
    char write = '\n';
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    char read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(charTest, tabChar)
{
    fs::path name = createPathFile("test_char_3.bin");

    // Write to file
    char write = '\t';
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    char read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(charTest, spaceChar)
{
    fs::path name = createPathFile("test_char_4.bin");

    // Write to file
    char write = ' ';
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    char read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(charTest, Many)
{
    fs::path name = createPathFile("test_char_5.bin");

    // Write to file
    char write1 = 'a';
    char write2 = 'p';
    char write3 = '\n';
    char write4 = '.';
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    char read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
    deleteFile(name);
}

/**
 * float tests
 */

TEST(floatTest, Negative)
{
    fs::path name = createPathFile("test_float_1.bin");

    // Write to file
    float write = -1.28;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    float read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(floatTest, Positive)
{
    fs::path name = createPathFile("test_float_2.bin");

    // Write to file
    float write = 12.234;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    float read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(floatTest, Minimum)
{
    fs::path name = createPathFile("test_float_3.bin");

    // Write to file
    float write = FLT_MIN;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    float read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(floatTest, Maximum)
{
    fs::path name = createPathFile("test_float_4.bin");

    // Write to file
    float write = FLT_MAX;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    float read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(floatTest, Many)
{
    fs::path name = createPathFile("test_float_5.bin");

    // Write to file
    float write1 = 1213.3143;
    float write2 = -0.10;
    float write3 = 123e-12;
    float write4 = 822;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 16u);

    // Reading the file
    float read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 16u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

/**
 * double tests
 */
TEST(doubleTest, Positive)
{
    fs::path name = createPathFile("test_double_1.bin");

    // Write to file
    double write = 7.23671;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    double read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(doubleTest, Negative)
{
    fs::path name = createPathFile("test_double_2.bin");

    // Write to file
    double write = -7.23671;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    double read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(doubleTest, Minimum)
{
    fs::path name = createPathFile("test_double_3.bin");

    // Write to file
    double write = -1.79769e+308;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    double read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(doubleTest, Maximum)
{
    fs::path name = createPathFile("test_double_4.bin");

    // Write to file
    double write = 1.79769e+308;
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 8u);

    // Reading the file
    double read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 8u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(doubleTest, Many)
{
    fs::path name = createPathFile("test_double_5.bin");

    // Write to file
    double write1 = -121312444221313223233.3143;
    double write2 = 0.10;
    double write3 = 1e-212;
    double write4 = 82212;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 32u);

    // Reading the file
    double read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 32u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

/**
 * bool tests
 */
TEST(boolTest, True)
{
    fs::path name = createPathFile("test_bool_1.bin");

    // Write to file
    bool write = true;

    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    bool read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(boolTest, False)
{
    fs::path name = createPathFile("test_bool_2.bin");

    // Write to file
    bool write = false;

    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 1u);

    // Reading the file
    bool read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(fs::file_size(name), 1u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(boolTest, Many)
{
    fs::path name = createPathFile("test_bool_3.bin");

    // Write to file
    bool write1 = true;
    bool write2 = true;
    bool write3 = false;
    bool write4 = true;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);

    // Reading the file
    bool read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(fs::file_size(name), 4u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

/**
 * string tests
 */
TEST(stringTest, Default)
{
    fs::path name = createPathFile("test_string_1.bin");

    // Write to file
    std::string write = "the string";
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    std::string read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(stringTest, Empty)
{
    fs::path name = createPathFile("test_string_2.bin");

    // Write to file
    std::string write = "      ";
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    std::string read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(stringTest, specialChar)
{
    fs::path name = createPathFile("test_string_3.bin");

    // Write to file
    std::string write = "hello\n\thow are you ?";
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    std::string read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(stringTest, Many)
{
    fs::path name = createPathFile("test_string_4.bin");

    // Write to file
    std::string write1 = "first\n";
    std::string write2 = "\tsecond";
    std::string write3 = "third string";
    std::string write4 = " last ";
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    // Reading the file
    std::string read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

/**
 * vector tests
 */
TEST(vectorTest, Integer)
{
    fs::path name = createPathFile("test_vector_1.bin");

    // Write to file
    std::vector<int32_t> write = {1, 2, 3, 4, 5};
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 28u);

    // Reading the file
    std::vector<int32_t> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(fs::file_size(name), 28u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(vectorTest, Character)
{
    fs::path name = createPathFile("test_vector_2.bin");

    // Write to file
    std::vector<char> write = {'a', 'b', 'c', 'd'};
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 12u);

    // Reading the file
    std::vector<char> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(fs::file_size(name), 12u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(vectorTest, Double)
{
    fs::path name = createPathFile("test_vector_3.bin");

    // Write to file
    std::vector<double> write = {1.3424, 4.343, 129274.34};
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 32u);

    // Reading the file
    std::vector<double> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(fs::file_size(name), 32u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(vectorTest, String)
{
    fs::path name = createPathFile("test_vector_4.bin");

    // Write to file
    std::vector<std::string> write = {"first", "second", "third"};
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    std::vector<std::string> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(vectorTest, Many)
{
    fs::path name = createPathFile("test_vector_5.bin");

    // Write to file
    std::vector<std::string> write1 = {"first", "second", "third"};
    std::vector<int16_t> write2 = {4, 5};
    std::vector<double> write3 = {6.0};
    std::vector<std::string> write4 = {"seven", "eight", "nine", "ten"};
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    // Reading the file
    std::vector<std::string> read1, read4;
    std::vector<int16_t> read2;
    std::vector<double> read3;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(vectorTest, Endianness)
{
    fs::path name = createPathFile("test_vector_6.bin");

    // Write to file
    std::vector<int16_t> write = {0x2F2, 0x239};
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    char size[8];
    std::ifstream f(name, std::ios::binary);
    f.read(size, 8);
    for (int i = 0; i < 7; i++)
    {
        ASSERT_EQ(static_cast<uint8_t>(size[i]), 0x00);
    }
    ASSERT_EQ(static_cast<uint8_t>(size[7]), 0x02);
    char b[4];
    f.read(b, 4);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x02);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0xF2);
    ASSERT_EQ(static_cast<uint8_t>(b[2]), 0x02);
    ASSERT_EQ(static_cast<uint8_t>(b[3]), 0x39);
    ASSERT_EQ(fs::file_size(name), 12u);

    deleteFile(name);
}

/**
 * array tests
 */

TEST(arrayTest, Integer)
{
    fs::path name = createPathFile("test_array_1.bin");

    // Write to file
    std::array<int8_t, 5> write = {1, 2, 3, 4, 5};
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 13u);

    // Reading the file
    std::array<int8_t, 5> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(fs::file_size(name), 13u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(arrayTest, Character)
{
    fs::path name = createPathFile("test_array_2.bin");

    // Write to file
    std::array<char, 5> write = {'a', 'b', 'c', 'd'};
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 13u);

    // Reading the file
    std::array<char, 5> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(fs::file_size(name), 13u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(arrayTest, Double)
{
    fs::path name = createPathFile("test_array_3.bin");

    // Write to file
    std::array<double, 3> write = {1.3424, 4.343, 129274.34};
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 32u);

    // Reading the file
    std::array<double, 3> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(fs::file_size(name), 32u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(arrayTest, String)
{
    fs::path name = createPathFile("test_array_4.bin");

    // Write to file
    std::array<std::string, 3> write = {"first", "second", "third"};
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    std::array<std::string, 3> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(arrayTest, Many)
{
    fs::path name = createPathFile("test_array_5.bin");

    // Write to file
    std::array<std::string, 3> write1 = {"first", "second", "third"};
    std::array<int16_t, 2> write2 = {4, 5};
    std::array<double, 1> write3 = {6.0};
    std::array<std::string, 4> write4 = {"seven", "eight", "nine", "ten"};
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    // Reading the file
    std::array<std::string, 3> read1;
    std::array<int16_t, 2> read2;
    std::array<double, 1> read3;
    std::array<std::string, 4> read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(arrayTest, Endianness)
{
    fs::path name = createPathFile("test_array_6.bin");

    // Write to file
    std::array<int32_t, 2> write = {0x2F223, 0x23944F};
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    char size[8];
    std::ifstream f(name, std::ios::binary);
    f.read(size, 8);
    for (int i = 0; i < 7; i++)
    {
        ASSERT_EQ(static_cast<uint8_t>(size[i]), 0x00);
    }
    ASSERT_EQ(static_cast<uint8_t>(size[7]), 0x02);
    char b[8];
    f.read(b, 8);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x02);
    ASSERT_EQ(static_cast<uint8_t>(b[2]), 0xF2);
    ASSERT_EQ(static_cast<uint8_t>(b[3]), 0x23);
    ASSERT_EQ(static_cast<uint8_t>(b[4]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[5]), 0x23);
    ASSERT_EQ(static_cast<uint8_t>(b[6]), 0x94);
    ASSERT_EQ(static_cast<uint8_t>(b[7]), 0x4F);
    ASSERT_EQ(fs::file_size(name), 16u);

    deleteFile(name);
}

/**
 * map tests
 */
TEST(mapTest, Default_1)
{
    fs::path name = createPathFile("test_map_1.bin");

    // Write to file
    std::map<std::string, int16_t> write = {{"one", 1}, {"two", 2}, {"three", 3}};
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    std::map<std::string, int16_t> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(mapTest, Default_2)
{
    fs::path name = createPathFile("test_map_2.bin");

    // Write to file
    std::map<float, int32_t> write = {{1.000, 12343}, {233432.3, 323}, {3230382.2, 123}};
    {
        serial::OBinaryFile file(name);
        file << write;
    }
    ASSERT_EQ(fs::file_size(name), 32u);

    // Reading the file
    std::map<float, int32_t> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }
    ASSERT_EQ(fs::file_size(name), 32u);
    ASSERT_EQ(write, read);

    deleteFile(name);
}

TEST(mapTest, Many)
{
    fs::path name = createPathFile("test_map_3.bin");

    // Write to file
    std::map<std::string, int32_t> write1 = {{"first", 12}, {"second", 123}, {"third", 1234}};
    std::map<int16_t, std::string> write2 = {{4, "four"}, {313, "five"}};
    std::map<double, float> write3 = {{6.0, 123124}};
    std::map<char, int32_t> write4 = {{'1', 12}, {'E', 123}, {' ', 1234}};
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    // Reading the file
    std::map<std::string, int32_t> read1;
    std::map<int16_t, std::string> read2;
    std::map<double, float> read3;
    std::map<char, int32_t> read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(mapTest, Endianness)
{
    fs::path name = createPathFile("test_map_4.bin");

    // Write to file
    std::map<int16_t, int32_t> write = {{0x3F, 0x129F}, {0xF4, 0x1234}};
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    // Reading the file
    char size[8];
    std::ifstream f(name, std::ios::binary);
    f.read(size, 8);
    for (int i = 0; i < 7; i++)
    {
        ASSERT_EQ(static_cast<uint8_t>(size[i]), 0x00);
    }
    ASSERT_EQ(static_cast<uint8_t>(size[7]), 0x02);
    char b[12];
    f.read(b, 12);
    ASSERT_EQ(static_cast<uint8_t>(b[0]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[1]), 0x3F);
    ASSERT_EQ(static_cast<uint8_t>(b[2]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[3]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[4]), 0x12);
    ASSERT_EQ(static_cast<uint8_t>(b[5]), 0x9F);
    ASSERT_EQ(static_cast<uint8_t>(b[6]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[7]), 0xF4);
    ASSERT_EQ(static_cast<uint8_t>(b[8]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[9]), 0x00);
    ASSERT_EQ(static_cast<uint8_t>(b[10]), 0x12);
    ASSERT_EQ(static_cast<uint8_t>(b[11]), 0x34);
    ASSERT_EQ(fs::file_size(name), 20u);

    deleteFile(name);
}

/**
 * mixed tests
 */
TEST(mixedTest, Types)
{
    fs::path name = createPathFile("test_mixed_1.bin");

    // Write to file
    int16_t write1 = 123;
    char write2 = 'e';
    float write3 = 1239e12;
    std::string write4 = "helloooo";
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    // Reading the file
    int16_t read1;
    char read2;
    float read3;
    std::string read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);

    deleteFile(name);
}

TEST(mixedTest, Container)
{
    fs::path name = createPathFile("test_mixed_2.bin");

    // Write to file
    std::vector<std::string> write1 = {"first", "second", "third"};
    std::map<int16_t, std::string> write2 = {{4, "four"}, {313, "five"}};
    std::array<std::string, 4> write3 = {"seven", "eight", "nine", "ten"};
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3;
    }

    // Reading the file
    std::vector<std::string> read1;
    std::map<int16_t, std::string> read2;
    std::array<std::string, 4> read3;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);

    deleteFile(name);
}

TEST(mixedTest, TypeAndContainer)
{
    fs::path name = createPathFile("test_mixed_3.bin");

    // Write to file
    double write1 = 1239e12;
    std::string write2 = "helloooo";
    std::vector<std::string> write3 = {"first", "second", "third"};
    int64_t write4 = 12323;
    std::map<int16_t, std::string> write5 = {{4, "four"}, {313, "five"}};
    std::array<std::string, 4> write6 = {"seven", "eight", "nine", "ten"};
    char write7 = 'e';
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4 << write5 << write6 << write7;
    }

    // Reading the file
    double read1;
    std::string read2;
    std::vector<std::string> read3;
    int64_t read4 = 12323;
    std::map<int16_t, std::string> read5;
    std::array<std::string, 4> read6;
    char read7;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4 >> read5 >> read6 >> read7;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
    ASSERT_EQ(write5, read5);
    ASSERT_EQ(write6, read6);
    ASSERT_EQ(write7, read7);

    deleteFile(name);
}

/**
 * move tests
 */
TEST(moveTest, OBinaryConstructor)
{
    fs::path name = createPathFile("test_move_1.bin");

    // Write to files
    int64_t write1 = 70000;
    int64_t write2 = 3;
    {
        serial::OBinaryFile f1(name);
        f1 << write1;
        serial::OBinaryFile f2 = std::move(f1);
        f2 << write2;
    }
    ASSERT_EQ(fs::file_size(name), 16u);

    // Reading the file
    int64_t read1, read2;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
    }
    ASSERT_EQ(fs::file_size(name), 16u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);

    deleteFile(name);
}

TEST(moveTest, OBinaryAssignmentOperator)
{
    fs::path name1 = createPathFile("test_move_2_1.bin");
    fs::path name2 = createPathFile("test_move_2_2.bin");

    // Write to files
    int64_t write1 = 70000;
    int64_t write2 = 3;
    int64_t write3 = 36;
    {
        serial::OBinaryFile f1(name1);
        f1 << write1;
        serial::OBinaryFile f2(name2);
        f2 << write3;
        f2 = std::move(f1);
        f2 << write2;
    }
    ASSERT_EQ(fs::file_size(name1), 16u);

    // Reading file
    int64_t read1, read2;
    {
        serial::IBinaryFile file(name1);
        file >> read1;
        file >> read2;
    }
    ASSERT_EQ(fs::file_size(name1), 16u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    deleteFile(name1);
    deleteFile(name2);
}

TEST(moveTest, IBinaryConstructor)
{
    fs::path name = createPathFile("test_move_3.bin");

    // Write to file
    int64_t write1 = 70000;
    int64_t write2 = 3;
    {
        serial::OBinaryFile f1(name);
        f1 << write1;
        f1 << write2;
    }
    ASSERT_EQ(fs::file_size(name), 16u);

    // Reading the files
    int64_t read1, read2;
    {
        serial::IBinaryFile file1(name);
        file1 >> read1;
        serial::IBinaryFile file2 = std::move(file1);
        file2 >> read2;
    }
    ASSERT_EQ(fs::file_size(name), 16u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);

    deleteFile(name);
}

TEST(moveTest, IBinaryAssignmentOperator)
{
    fs::path name1 = createPathFile("test_move_4_1.bin");
    fs::path name2 = createPathFile("test_move_4_2.bin");

    // Write to files
    int64_t write1 = 70000;
    int64_t write2 = 3;
    int64_t write3 = 36;
    {
        serial::OBinaryFile f1(name1);
        f1 << write1;
        f1 << write2;
        serial::OBinaryFile f2(name2);
        f2 << write3;
    }
    ASSERT_EQ(fs::file_size(name1), 16u);
    ASSERT_EQ(fs::file_size(name2), 8u);

    // Reading files
    int64_t read1, read2, read3;
    {
        serial::IBinaryFile file1(name1);
        file1 >> read1;
        serial::IBinaryFile file2(name2);
        file2 >> read3;
        file2 = std::move(file1);
        file2 >> read2;
    }
    ASSERT_EQ(fs::file_size(name1), 16u);
    ASSERT_EQ(fs::file_size(name2), 8u);
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);

    deleteFile(name1);
    deleteFile(name2);
}

/**
 * use test
 */
struct Foo
{
    int16_t i;
    double d;
    std::string s;
};

serial::OBinaryFile &operator<<(serial::OBinaryFile &file, const Foo &foo)
{
    return file << foo.i << foo.d << foo.s;
}
serial::IBinaryFile &operator>>(serial::IBinaryFile &file, Foo &foo)
{
    return file >> foo.i >> foo.d >> foo.s;
}

TEST(useTest, Default)
{
    fs::path name = createPathFile("test_use.bin");

    // Write to file
    Foo foo;
    foo.i = 42;
    foo.d = 69.0;
    foo.s = "Hello";
    {
        serial::OBinaryFile out(name);
        out << foo;
    }

    // Reading the file
    struct Foo copy;
    {
        serial::IBinaryFile in(name);
        in >> copy;
    }
    ASSERT_EQ(foo.i, copy.i);
    ASSERT_EQ(foo.d, copy.d);
    ASSERT_EQ(foo.s, copy.s);

    deleteFile(name);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
