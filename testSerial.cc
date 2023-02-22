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
        file << write1 << write2 << write3 << write4;
    }

    uint8_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
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
        file << write1 << write2 << write3 << write4;
    }

    int8_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
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
        file << write1 << write2 << write3 << write4;
    }

    uint16_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
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
        file << write1 << write2 << write3 << write4;
    }

    int16_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
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
        file << write1 << write2 << write3 << write4;
    }

    uint32_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
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
        file << write1 << write2 << write3 << write4;
    }

    int32_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
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
        file << write1 << write2 << write3 << write4;
    }

    uint64_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
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
        file << write1 << write2 << write3 << write4;
    }

    int64_t read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * char
 */

TEST(charTest, Default)
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

TEST(charTest, newlineChar)
{
    fs::path name = createFile("test_char_1.bin");
    char write = '\n';

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

TEST(charTest, tabChar)
{
    fs::path name = createFile("test_char_2.bin");
    char write = '\t';

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

TEST(charTest, spaceChar)
{
    fs::path name = createFile("test_char_3.bin");
    char write = ' ';

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

TEST(charTest, Many)
{
    fs::path name = createFile("test_char_4.bin");
    char write1 = 'a';
    char write2 = 'p';
    char write3 = '\n';
    char write4 = '.';
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    char read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * float
 */

TEST(floatTest, Negative)
{
    fs::path name = createFile("test_float_1.bin");
    float write = -1.28;

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

TEST(floatTest, Positive)
{
    fs::path name = createFile("test_float_2.bin");
    float write = 12.234;

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

TEST(floatTest, Minimum)
{
    fs::path name = createFile("test_float_3.bin");
    float write = FLT_MIN;

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

TEST(floatTest, Maximum)
{
    fs::path name = createFile("test_float_4.bin");
    float write = FLT_MAX;

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

TEST(floatTest, Many)
{
    fs::path name = createFile("test_float_5.bin");
    float write1 = 1213.3143;
    float write2 = -0.10;
    float write3 = 123e-12;
    float write4 = 822;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    float read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * double
 */
TEST(doubleTest, Positive)
{
    fs::path name = createFile("test_double_1.bin");
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

TEST(doubleTest, Negative)
{
    fs::path name = createFile("test_double_2.bin");
    double write = -7.23671;

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

TEST(doubleTest, Minimum)
{
    fs::path name = createFile("test_double_3.bin");
    double write = -1.79769e+308;

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

TEST(doubleTest, Maximum)
{
    fs::path name = createFile("test_double_4.bin");
    double write = 1.79769e+308;

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

TEST(doubleTest, Many)
{
    fs::path name = createFile("test_double_5.bin");
    double write1 = -121312444221313223233.3143;
    double write2 = 0.10;
    double write3 = 1e-212;
    double write4 = 82212;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    double read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * bool
 */
TEST(boolTest, True)
{
    fs::path name = createFile("test_bool_1.bin");
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

TEST(boolTest, False)
{
    fs::path name = createFile("test_bool_1.bin");
    bool write = false;

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

TEST(boolTest, Many)
{
    fs::path name = createFile("test_double_5.bin");
    bool write1 = true;
    bool write2 = true;
    bool write3 = false;
    bool write4 = true;
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    bool read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * string
 */
TEST(stringTest, Default)
{
    fs::path name = createFile("test_string_1.bin");
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

TEST(stringTest, Empty)
{
    fs::path name = createFile("test_string_2.bin");
    std::string write = "      ";
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

TEST(stringTest, specialChar)
{
    fs::path name = createFile("test_string_3.bin");
    std::string write = "hello\n\thow are you ?";
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

TEST(stringTest, Many)
{
    fs::path name = createFile("test_string_4.bin");
    std::string write1 = "first\n";
    std::string write2 = "\tsecond";
    std::string write3 = "third string";
    std::string write4 = " last ";
    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

    std::string read1, read2, read3, read4;
    {
        serial::IBinaryFile file(name);
        file >> read1 >> read2 >> read3 >> read4;
    }
    ASSERT_EQ(write1, read1);
    ASSERT_EQ(write2, read2);
    ASSERT_EQ(write3, read3);
    ASSERT_EQ(write4, read4);
}

/**
 * vector
 */
TEST(vectorTest, Integer)
{
    fs::path name = createFile("test_vector_1.bin");
    std::vector<int32_t> write = {1, 2, 3, 4, 5};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::vector<int32_t> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(vectorTest, Character)
{
    fs::path name = createFile("test_vector_2.bin");
    std::vector<char> write = {'a', 'b', 'c', 'd'};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::vector<char> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(vectorTest, Double)
{
    fs::path name = createFile("test_vector_3.bin");
    std::vector<double> write = {1.3424, 4.343, 129274.34};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::vector<double> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(vectorTest, String)
{
    fs::path name = createFile("test_vector_4.bin");
    std::vector<std::string> write = {"first", "second", "third"};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::vector<std::string> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(vectorTest, Many)
{
    fs::path name = createFile("test_vector_5.bin");
    std::vector<std::string> write1 = {"first", "second", "third"};
    std::vector<int16_t> write2 = {4, 5};
    std::vector<double> write3 = {6.0};
    std::vector<std::string> write4 = {"seven", "eight", "nine", "ten"};

    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

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
}

/**
 * array
 */

TEST(arrayTest, Integer)
{
    fs::path name = createFile("test_array_1.bin");
    std::array<int, 5> write = {1, 2, 3, 4, 5};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::array<int, 5> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(arrayTest, Character)
{
    fs::path name = createFile("test_array_2.bin");
    std::array<char, 5> write = {'a', 'b', 'c', 'd'};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::array<char, 5> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(arrayTest, Double)
{
    fs::path name = createFile("test_array_3.bin");
    std::array<double, 3> write = {1.3424, 4.343, 129274.34};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::array<double, 3> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(arrayTest, String)
{
    fs::path name = createFile("test_array_4.bin");
    std::array<std::string, 3> write = {"first", "second", "third"};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::array<std::string, 3> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(arrayTest, Many)
{
    fs::path name = createFile("test_array_5.bin");
    std::array<std::string, 3> write1 = {"first", "second", "third"};
    std::array<int16_t, 2> write2 = {4, 5};
    std::array<double, 1> write3 = {6.0};
    std::array<std::string, 4> write4 = {"seven", "eight", "nine", "ten"};

    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

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
}

/**
 * map
 */
TEST(mapTest, Default_1)
{
    fs::path name = createFile("test_map_1.bin");
    std::map<std::string, int16_t> write = {{"one", 1}, {"two", 2}, {"three", 3}};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::map<std::string, int16_t> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(mapTest, Default_2)
{
    fs::path name = createFile("test_map_2.bin");
    std::map<float, int32_t> write = {{1.000, 12343}, {233432.3, 323}, {3230382.2, 123}};

    {
        serial::OBinaryFile file(name);
        file << write;
    }

    std::map<float, int32_t> read;
    {
        serial::IBinaryFile file_read(name);
        file_read >> read;
    }

    ASSERT_EQ(write, read);
}

TEST(mapTest, Many)
{
    fs::path name = createFile("test_map_3.bin");
    std::map<std::string, int32_t> write1 = {{"first", 12}, {"second", 123}, {"third", 1234}};
    std::map<int16_t, std::string> write2 = {{4, "four"}, {313, "five"}};
    std::map<double, float> write3 = {{6.0, 123124}};
    std::map<char, int32_t> write4 = {{'1', 12}, {'E', 123}, {' ', 1234}};

    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

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
}

/**
 * mixed int string...
 */
TEST(mixedTest, Types)
{
    fs::path name = createFile("test_mixed_1.bin");
    int16_t write1 = 123;
    char write2 = 'e';
    float write3 = 1239e12;
    ;
    std::string write4 = "helloooo";

    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3 << write4;
    }

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
}

TEST(mixedTest, Container)
{
    fs::path name = createFile("test_mixed_2.bin");
    std::vector<std::string> write1 = {"first", "second", "third"};
    std::map<int16_t, std::string> write2 = {{4, "four"}, {313, "five"}};
    std::array<std::string, 4> write3 = {"seven", "eight", "nine", "ten"};

    {
        serial::OBinaryFile file(name);
        file << write1 << write2 << write3;
    }

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
}

TEST(mixedTest, TypeAndContainer)
{
    fs::path name = createFile("test_mixed_3.bin");
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
}

/**
 * move
 */
/*TEST(moveTest, Default)
{
    serial::OBinaryFile f1("file.bin");
    serial::OBinaryFile f2 = std::move(f1); // Call the Constructor not the assignment operator
    serial::OBinaryFile f3("file2.bin");
    f3 = std::move(f2); // assignment operator



    fs::path name1 = createFile("test_move_1_1.bin");
    fs::path name2 = createFile("test_move_1_2.bin");

    int64_t write = 70000;

    {
        serial::OBinaryFile f1(name1);
        serial::OBinaryFile f2 = std::move(f1);
        f2 << write;
        
    }

    int64_t read;
    {
        serial::IBinaryFile file(name1);
        file >> read;
    }
    ASSERT_EQ(write, read);
}*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
