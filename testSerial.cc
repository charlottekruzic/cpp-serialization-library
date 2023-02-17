#include "Serial.h"

#include <gtest/gtest.h>

//fylesystem


TEST(SerialWriteTest, Default) {
    serial::OBinaryFile file("./test_write.txt");
    const std::byte b{42};
    file.write(&b,1);
}

TEST(SerialReadTest, Default) {
    serial::IBinaryFile file("./test_write.txt");
    std::byte b{};
    file.read(&b, 1);
    std::cout << "read : " << static_cast <int>(b) << '\n';

}



int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
