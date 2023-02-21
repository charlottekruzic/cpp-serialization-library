#include "Serial.h"

#include <gtest/gtest.h>
//#include <filesystem>
#include <fstream>

//namespace fs = std::filesystem;

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
}

/**
 * uint8_t
*/
TEST(uint8Test, Default)
{
    uint8_t write = 42;
    {
        serial::OBinaryFile file("test_uint8_1.bin");
        file << write;
    }

    uint8_t read;
    {
        serial::IBinaryFile file("test_uint8_1.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint8Test, Minimum)
{
    uint8_t write = 0;
    {
        serial::OBinaryFile file("test_uint8_2.bin");
        file << write;
    }

    uint8_t read;
    {
        serial::IBinaryFile file("test_uint8_2.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint8Test, Maximal)
{
    uint8_t write = 255;
    {
        serial::OBinaryFile file("test_uint8_3.bin");
        file << write;
    }

    uint8_t read;
    {
        serial::IBinaryFile file("test_uint8_3.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(uint8Test, Many)
{
    uint8_t write1 = 1;
    uint8_t write2 = 2;
    uint8_t write3 = 3;
    uint8_t write4 = 4;
    {
        serial::OBinaryFile file("test_uint8_4.bin");
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
        serial::IBinaryFile file("test_uint8_4.bin");
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
    int8_t write = -42;
    {
        serial::OBinaryFile file("test_int8_1.bin");
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file("test_int8_1.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Positive)
{
    int8_t write = 42;
    {
        serial::OBinaryFile file("test_int8_2.bin");
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file("test_int8_2.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Minimum)
{
    int8_t write = -128;
    {
        serial::OBinaryFile file("test_int8_3.bin");
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file("test_int8_3.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Maximum)
{
    int8_t write = 127;
    {
        serial::OBinaryFile file("test_int8_4.bin");
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file("test_int8_4.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(int8Test, Null)
{
    int8_t write = 0;
    {
        serial::OBinaryFile file("test_int8_5.bin");
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file("test_int8_5.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}



/**
 * uint16
*/

TEST(SerialSerializationTest, uint16)
{
    uint16_t write = 5000;
    
    {
        serial::OBinaryFile file("test_uint16.bin");
        file << write;
    }

    uint16_t read;
    {
        serial::IBinaryFile file("test_uint16.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

/**
 * int16
*/

TEST(SerialSerializationTest, int16)
{
    int16_t write = -5000;
    
    {
        serial::OBinaryFile file("test_int16.bin");
        file << write;
    }

    int16_t read;
    {
        serial::IBinaryFile file("test_int16.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

/**
 * uint32
*/

TEST(SerialSerializationTest, uint32)
{
    uint32_t write = 70000;
    
    {
        serial::OBinaryFile file("test_uint32_t.bin");
        file << write;
    }

    uint32_t read;
    {
        serial::IBinaryFile file("test_uint32_t.bin");
        file >> read;
    }
    
    ASSERT_EQ(write, read);
}

/**
 * int32
*/

TEST(SerialSerializationTest, int32)
{
    int32_t write = -70000;
    
    {
        serial::OBinaryFile file("test_int32_t.bin");
        file << write;
    }

    int32_t read;
    {
        serial::IBinaryFile file("test_int32_t.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

/**
 * uint64
*/

TEST(SerialSerializationTest, uint64)
{
    uint64_t write = 70000;
    
    {
        serial::OBinaryFile file("test_uint64_t.bin");
        file << write;
    }

    uint64_t read;
    {
        serial::IBinaryFile file("test_uint64_t.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(SerialSerializationTest, int64)
{
    int64_t write = -70000;
    
    {
        serial::OBinaryFile file("test_int64_t.bin");
        file << write;
    }

    int64_t read;
    {
        serial::IBinaryFile file("test_int64_t.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(SerialSerializationTest, character)
{
    char write = 'a';
    
    {
        serial::OBinaryFile file("test_char.bin");
        file << write;
    }

    char read;
    {
        serial::IBinaryFile file("test_char.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(SerialSerializationTest, float_)
{
    float write = 1.0e-45f;
    
    {
        serial::OBinaryFile file("test_float.bin");
        file << write;
    }

    float read;
    {
        serial::IBinaryFile file("test_float.bin");
        file >> read;
    }
    
    ASSERT_EQ(write, read);
}

TEST(SerialSerializationTest, double_)
{
    double write = 7.23671;
    
    {
        serial::OBinaryFile file("test_double.bin");
        file << write;
    }

    double read;
    {
        serial::IBinaryFile file("test_double.bin");
        file >> read;
    }
    
    ASSERT_EQ(write, read);
}

TEST(SerialSerializationTest, boolean)
{
    bool write = true;
    
    {
        serial::OBinaryFile file("test_bool.bin");
        file << write;
    }

    bool read;
    {
        serial::IBinaryFile file("test_bool.bin");
        file >> read;
    }
    
    ASSERT_EQ(write, read);
}

TEST(SerialSerializationTest, string)
{
    std::string write = "the string";
    write.size();

    {
        serial::OBinaryFile file("test_string.bin");
        file << write;
    }

    std::string read;
    {
        serial::IBinaryFile file("test_string.bin");
        file >> read;
    }

    ASSERT_EQ(write, read);
}


TEST(SerialSerializationTest, vector_int)
{
    std::vector<int> write_vec = {1, 2, 3, 4, 5};

    {
        serial::OBinaryFile file("test_vector.bin");
        file << write_vec;
    }

    std::vector<int> read_vec;
    {
        serial::IBinaryFile file_read("test_vector.bin");
        file_read >> read_vec;
    }

    ASSERT_EQ(write_vec, read_vec);
}

TEST(SerialSerializationTest, vector_char)
{
    std::vector<char> write_vec = {'a', 'b', 'c', 'd'};

    {
        serial::OBinaryFile file("test_vector.bin");
        file << write_vec;
    }

    std::vector<char> read_vec;
    {
        serial::IBinaryFile file_read("test_vector.bin");
        file_read >> read_vec;
    }

    ASSERT_EQ(write_vec, read_vec);
}

TEST(SerialSerializationTest, vector_double)
{
    std::vector<double> write_vec = {1.3424, 4.343, 129274.34};

    {
        serial::OBinaryFile file("test_vector.bin");
        file << write_vec;
    }

    std::vector<double> read_vec;
    {
        serial::IBinaryFile file_read("test_vector.bin");
        file_read >> read_vec;
    }

    ASSERT_EQ(write_vec, read_vec);
}

TEST(SerialSerializationTest, array_)
{
     std::array<int, 5> write_array = {1, 2, 3, 4, 5};

    {
        serial::OBinaryFile file("test_array.bin");
        file << write_array;
    }

    std::array<int, 5> read_array;
    {
        serial::IBinaryFile file_read("test_array.bin");
        file_read >> read_array;
    }

    ASSERT_EQ(write_array, read_array);
}

TEST(SerialSerializationTest, map_)
{
    std::map<std::string, int> write_map = {
        {"foo", 42},
        {"bar", 1337},
        {"baz", 69}
    };

    {
        serial::OBinaryFile file("test_map.bin");
        file << write_map;
    }

    std::map<std::string, int> read_map;
    {
        serial::IBinaryFile file_read("test_map.bin");
        file_read >> read_map;
    }

    ASSERT_EQ(write_map, read_map);
}


/*
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
