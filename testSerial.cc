#include "Serial.h"

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

fs::path createFile(std::string file_name)
{
    fs::path directory_path = fs::temp_directory_path();

    std::filesystem::path file_path = directory_path;
    file_path.append(file_name);

    return file_path;
}

/**
 * uint8_t
 */
TEST(uint8Test, Default)
{
    fs::path name = createFile("test_uint8_1.bin");
    uint8_t write = 42;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint8Test, Minimum)
{
    fs::path name = createFile("test_uint8_2.bin");
    uint8_t write = 0;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint8Test, Maximal)
{
    fs::path name = createFile("test_uint8_3.bin");
    uint8_t write = 255;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint8Test, Many)
{
    fs::path name = createFile("test_uint8_4.bin");
    uint8_t write1 = 1;
    uint8_t write2 = 2;
    uint8_t write3 = 3;
    uint8_t write4 = 4;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    uint8_t read1;
    uint8_t read2;
    uint8_t read3;
    uint8_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * int8_t
 */

TEST(int8Test, Negative)
{
    fs::path name = createFile("test_int8_1.bin");
    int8_t write = -42;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Positive)
{
    fs::path name = createFile("test_int8_2.bin");
    int8_t write = 42;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Minimum)
{
    fs::path name = createFile("test_int8_3.bin");
    int8_t write = -128;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Maximum)
{
    fs::path name = createFile("test_int8_4.bin");
    int8_t write = 127;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Null)
{
    fs::path name = createFile("test_int8_5.bin");
    int8_t write = 0;
    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Many)
{
    fs::path name = createFile("test_int8_6.bin");
    int8_t write1 = 1;
    int8_t write2 = 2;
    int8_t write3 = 3;
    int8_t write4 = 4;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    int8_t read1;
    int8_t read2;
    int8_t read3;
    int8_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * uint16
 */

TEST(uint16Test, Default)
{
    fs::path name = createFile("test_uint16_1.bin");
    uint16_t write = 5000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint16Test, Maximum)
{
    fs::path name = createFile("test_uint16_2.bin");
    uint16_t write = 65535;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint16Test, Minimum)
{
    fs::path name = createFile("test_uint16_3.bin");
    uint16_t write = 0;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint16Test, Many)
{
    fs::path name = createFile("test_uint16_4.bin");
    uint16_t write1 = 1;
    uint16_t write2 = 223;
    uint16_t write3 = 34242;
    uint16_t write4 = 43141;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    uint16_t read1;
    uint16_t read2;
    uint16_t read3;
    uint16_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * int16
 */

TEST(int16Test, Negative)
{
    fs::path name = createFile("test_int16_1.bin");
    int16_t write = -5000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int16Test, Positive)
{
    fs::path name = createFile("test_int16_2.bin");
    int16_t write = 5000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int16Test, Minimum)
{
    fs::path name = createFile("test_int16_3.bin");
    int16_t write = -32768;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int16Test, Maximum)
{
    fs::path name = createFile("test_int16_4.bin");
    int16_t write = 32767;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int16_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int16Test, Many)
{
    fs::path name = createFile("test_int16_5.bin");
    int16_t write1 = 1;
    int16_t write2 = 223;
    int16_t write3 = -3242;
    int16_t write4 = 43141;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    int16_t read1;
    int16_t read2;
    int16_t read3;
    int16_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * uint32
 */

TEST(uint32Test, Default)
{
    fs::path name = createFile("test_uint32_1.bin");
    uint32_t write = 70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(uint32Test, Minimum)
{
    fs::path name = createFile("test_uint32_2.bin");
    uint32_t write = 0;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(uint32Test, Maximum)
{
    fs::path name = createFile("test_uint32_3.bin");
    uint32_t write = 0xFFFFFFFF;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(uint32Test, Many)
{
    fs::path name = createFile("test_uint32_4.bin");
    uint32_t write1 = 1;
    uint32_t write2 = 0xFF13;
    uint32_t write3 = 1332;
    uint32_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    uint32_t read1;
    uint32_t read2;
    uint32_t read3;
    uint32_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * int32
 */

TEST(int32Test, Negative)
{
    fs::path name = createFile("test_int32_1.bin");
    int32_t write = -70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int32Test, Positive)
{
    fs::path name = createFile("test_int32_2.bin");
    int32_t write = 70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int32Test, Minimum)
{
    fs::path name = createFile("test_int32_3.bin");
    int32_t write = 0X80000000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int32Test, Maximum)
{
    fs::path name = createFile("test_int32_4.bin");
    int32_t write = 0X7FFFFFFF;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int32_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int32Test, Many)
{
    fs::path name = createFile("test_int32_5.bin");
    int32_t write1 = 1;
    int32_t write2 = 0xFF1;
    int32_t write3 = 0x0FFF9;
    int32_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    int32_t read1;
    int32_t read2;
    int32_t read3;
    int32_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * uint64
 */

TEST(uint64Test, Default)
{
    fs::path name = createFile("test_uint64_1.bin");
    uint64_t write = 70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint64Test, Minimum)
{
    fs::path name = createFile("test_uint64_2.bin");
    uint64_t write = 0;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint64Test, Maximum)
{
    fs::path name = createFile("test_uint64_3.bin");
    uint64_t write = 0xFFFFFFFFFFFFFFFF;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    uint64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint64Test, Many)
{
    fs::path name = createFile("test_uint64_4.bin");
    uint64_t write1 = 1;
    uint64_t write2 = 0xFF13;
    uint64_t write3 = 0xFFF9;
    uint64_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    uint64_t read1;
    uint64_t read2;
    uint64_t read3;
    uint64_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * int64
 */

TEST(int64Test, Negative)
{
    fs::path name = createFile("test_int64_1.bin");
    int64_t write = -70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int64Test, Positive)
{
    fs::path name = createFile("test_int64_2.bin");
    int64_t write = -70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int64Test, Minimum)
{
    fs::path name = createFile("test_int64_3.bin");
    int64_t write = -70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int64Test, Maximum)
{
    fs::path name = createFile("test_int64_4.bin");
    int64_t write = -70000;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    int64_t read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int64Test, Many)
{
    fs::path name = createFile("test_int64_5.bin");
    int64_t write1 = -12;
    int64_t write2 = 0x8F123;
    int64_t write3 = 0x7FF9A;
    int64_t write4 = 2343921;
    {
        serial::OBinaryFile file(name);
        file << write1;
        file << write2;
        file << write3;
        file << write4;
    }

    int64_t read1;
    int64_t read2;
    int64_t read3;
    int64_t read4;
    {
        serial::IBinaryFile file(name);
        file >> read1;
        file >> read2;
        file >> read3;
        file >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * char
 */

TEST(charTest, character)
{
    fs::path name = createFile("test_char.bin");
    char write = 'a';

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    char read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }
    ASSERT_EQ(write, read);
}

/**
 * float
 */

TEST(floatTest, float_)
{
    fs::path name = createFile("test_float.bin");
    float write = 1.0e-45f;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    float read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }

    ASSERT_EQ(write, read);
}

/**
 * double
 */
TEST(doubleTest, double_)
{
    fs::path name = createFile("test_double.bin");
    double write = 7.23671;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    double read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }

    ASSERT_EQ(write, read);
}

/**
 * bool
 */
TEST(boolTest, boolean)
{
    fs::path name = createFile("test_bool.bin");
    bool write = true;

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    bool read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }

    ASSERT_EQ(write, read);
}

/**
 * string
 */
TEST(stringTest, string)
{
    fs::path name = createFile("test_string.bin");
    std::string write = "the string";
    write.size();

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::string read;
    {
        serial::IBinaryFile file(name);
        file >> read;
    }

    ASSERT_EQ(write, read);
}

/**
 * vector
 */
TEST(vectorTest, vector_int)
{
    fs::path name = createFile("test_vector_1.bin");
    std::vector<int> write_vec = {1, 2, 3, 4, 5};

    {
        serial::OBinaryFile file(name);
        file << write_vec;
    }

    std::vector<int> read_vec;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read_vec;
    }

    ASSERT_EQ(write_vec, read_vec);
}

TEST(vectorTest, vector_char)
{
    fs::path name = createFile("test_vector_2.bin");
    std::vector<char> write_vec = {'a', 'b', 'c', 'd'};

    {
        serial::OBinaryFile file(name);
        file << write_vec;
    }

    std::vector<char> read_vec;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read_vec;
    }

    ASSERT_EQ(write_vec, read_vec);
}

TEST(vectorTest, vector_double)
{
    fs::path name = createFile("test_vector_3.bin");
    std::vector<double> write_vec = {1.3424, 4.343, 129274.34};

    {
        serial::OBinaryFile file(name);
        file << write_vec;
    }

    std::vector<double> read_vec;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read_vec;
    }

    ASSERT_EQ(write_vec, read_vec);
}

/**
 * array
 */
TEST(arrayTest, array_)
{
    fs::path name = createFile("test_array.bin");
    std::array<int, 5> write_array = {1, 2, 3, 4, 5};

    {
        serial::OBinaryFile file(name);
        file << write_array;
    }

    std::array<int, 5> read_array;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read_array;
    }

    ASSERT_EQ(write_array, read_array);
}

/**
 * map
 */
TEST(mapTest, map_)
{
    fs::path name = createFile("test_map.bin");
    std::map<std::string, int> write_map = {
        {"foo", 42},
        {"bar", 1337},
        {"baz", 69}};

    {
        serial::OBinaryFile file(name);
        file << write_map;
    }

    std::map<std::string, int> read_map;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read_map;
    }

    ASSERT_EQ(write_map, read_map);
}

/**
 * deplacement
 */

/**
 * mixed int string...
 */

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    // deleteFilesTests();
}
