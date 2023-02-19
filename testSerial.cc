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
{
    uint8_t write = 42;
    {
        serial::OBinaryFile file("test_uint8.bin");
        file << write;
    }

    uint8_t read;
    {
        serial::IBinaryFile file("test_uint8.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

TEST(SerialSerializationTest, int8)
{
    int8_t write = -42;
    {
        serial::OBinaryFile file("test_int8.bin");
        file << write;
    }

    int8_t read;
    {
        serial::IBinaryFile file("test_int8.bin");
        file >> read;
    }
    ASSERT_EQ(write, read);
}

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

TEST(SerialSerializationTest, uint32)
{ // faire avec >>
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

TEST(SerialSerializationTest, int32)
{ // faire avec >>
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
    size_t s_write = write.size();
    size_t size = sizeof(s_write);

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
{ // faire avec >>
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
{ // faire avec >>
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
{ // faire avec >>
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
