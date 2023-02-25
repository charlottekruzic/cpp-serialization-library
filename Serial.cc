#include "Serial.h"

namespace serial
{

    /***********************************************************************************
     *                                  OBinaryFile
     ***********************************************************************************/

    /**
     * @brief Constructor
     *
     * Opens the file for writing or throws a `std::runtime_error` in case of
     * error.
     */
    OBinaryFile::OBinaryFile(const std::string &filename, Mode mode)
    {
        const char *opening_mode = (mode == Mode::Append ? "a" : "w");
        m_file = (fopen(filename.c_str(), opening_mode));
        if (m_file == NULL)
        {
            throw std::runtime_error("Error while opening the file!");
        }
    }

    /**
     * @brief Move constructor
     */
    OBinaryFile::OBinaryFile(OBinaryFile &&other) noexcept
    : m_file(std::exchange(other.m_file, nullptr))
    {
    }

    /**
     * @brief Move assignment
     */
    OBinaryFile &OBinaryFile::operator=(OBinaryFile &&other) noexcept
    {
        std::swap(m_file, other.m_file);
        return *this;
    }

    /**
     * @brief Closes the file
     */
    OBinaryFile::~OBinaryFile()
    {
        if (m_file == nullptr){return;}
        int ret = fclose(m_file);
        if (ret == EOF)
        {
            throw std::runtime_error("Error while closing the file!\n");
        }
    }

    /**
     * @brief Write `size` bytes pointed by `data` in the file
     *
     * Returns the number of bytes actually written
     */
    std::size_t OBinaryFile::write(const std::byte *data, std::size_t size)
    {
        return fwrite(data, sizeof(std::byte), size, m_file);
    }

    /***********************************************************************************
     *                                  IBinaryFile
     ***********************************************************************************/

    /**
     * @brief Constructor
     *
     * Opens the file for writing or throws a `std::runtime_error` in case of
     * error.
     */
    IBinaryFile::IBinaryFile(const std::string &filename)
    : m_file(fopen(filename.c_str(), "r"))
    {
        if (m_file == NULL)
        {
            throw std::runtime_error("Error while opening the file!");
        }
    }

    /**
     * @brief Move constructor
     */
    IBinaryFile::IBinaryFile(IBinaryFile &&other) noexcept
    : m_file(std::exchange(other.m_file, nullptr))
    {
    }

    /**
     * @brief Move assignment
     */
    IBinaryFile &IBinaryFile::operator=(IBinaryFile &&other) noexcept
    {
        std::swap(m_file, other.m_file);
        return *this;
    }

    /**
     * @brief Closes the file
     */
    IBinaryFile::~IBinaryFile()
    {
        if (m_file == nullptr){return;}
        int ret = fclose(m_file);
        if (ret == EOF)
        {
            throw std::runtime_error("Error while closing the file!\n");
        }
    }

    /**
     * @brief Read `size` bytes from the file and store them in the buffer
     * pointed by `data`.
     *
     * Returns the number of bytes actually read.
     */
    std::size_t IBinaryFile::read(std::byte *data, std::size_t size)
    {
        return fread(data, sizeof(std::byte), size, m_file);
    }

    /***********************************************************************************
     *                            Serialization operators
     ***********************************************************************************/

    OBinaryFile &operator<<(OBinaryFile &file, uint8_t x)
    {
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int8_t x)
    {
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, uint16_t x)
    {
        std::byte b[2];
        // Big endian serialization
        b[0] = static_cast<std::byte>(x >> 8);
        b[1] = static_cast<std::byte>(x);
        file.write(b, 2);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int16_t x)
    {
        std::byte b[2];
        // Big endian serialization
        b[0] = static_cast<std::byte>(x >> 8);
        b[1] = static_cast<std::byte>(x);
        file.write(b, 2);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, uint32_t x)
    {
        std::byte b[4];
        // Big endian serialization
        for (int i = 0; i < 4; ++i)
        {
            b[i] = static_cast<std::byte>(x >> ((3 - i) * 8));
        }
        file.write(b, 4);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int32_t x)
    {
        std::byte b[4];
        // Big endian serialization
        for (int i = 0; i < 4; ++i)
        {
            b[i] = static_cast<std::byte>(x >> ((3 - i) * 8));
        }
        file.write(b, 4);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, uint64_t x)
    {
        std::byte b[8];
        // Big endian serialization
        for (int i = 0; i < 8; ++i)
        {
            b[i] = static_cast<std::byte>(x >> ((7 - i) * 8));
        }
        file.write(b, 8);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, int64_t x)
    {
        std::byte b[8];
        // Big endian serialization
        for (int i = 0; i < 8; ++i)
        {
            b[i] = static_cast<std::byte>(x >> ((7 - i) * 8));
        }
        file.write(b, 8);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, char x)
    {
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, float x)
    {
        std::byte b[4];
        std::memcpy(b, &x, 4);
        file.write(b, 4);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, double x)
    {
        std::byte b[8];
        std::memcpy(b, &x, 8);
        file.write(b, 8);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, bool x)
    {
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

    OBinaryFile &operator<<(OBinaryFile &file, const std::string &x)
    {
        file << x.size();
        for (char letter : x)
        {
            file << letter;
        }
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int8_t &x)
    {
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<int8_t>(read);
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint8_t &x)
    {
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<uint8_t>(read);
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int16_t &x)
    {
        std::byte read[2];
        file.read(read, 2);
        // Big endian deserialization
        x = static_cast<int16_t>(read[0]) << 8 |
            static_cast<int16_t>(read[1]);
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint16_t &x)
    {
        std::byte read[2];
        file.read(read, 2);
        // Big endian deserialization
        x = static_cast<uint16_t>(read[0]) << 8 |
            static_cast<uint16_t>(read[1]);
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int32_t &x)
    {
        std::byte read[4];
        file.read(read, 4);
        // Big endian deserialization
        x = 0;
        for (int i = 0; i < 4; ++i)
        {
            x |= static_cast<int32_t>(read[i]) << ((3 - i) * 8);
        }
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint32_t &x)
    {
        std::byte read[4];
        file.read(read, 4);
        // Big endian deserialization
        x = 0;
        for (int i = 0; i < 4; ++i)
        {
            x |= static_cast<uint32_t>(read[i]) << ((3 - i) * 8);
        }
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, int64_t &x)
    {
        std::byte read[8];
        file.read(read, 8);
        // Big endian deserialization
        x = 0;
        for (int i = 0; i < 8; ++i)
        {
            x |= static_cast<int64_t>(read[i]) << ((7 - i) * 8);
        }
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, uint64_t &x)
    {
        std::byte read[8];
        file.read(read, 8);
        // Big endian deserialization
        x = 0;
        for (int i = 0; i < 8; ++i)
        {
            x |= static_cast<uint64_t>(read[i]) << ((7 - i) * 8);
        }
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, char &x)
    {
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<char>(read);
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, float &x)
    {
        std::byte read[4];
        file.read(read, 4);
        std::memcpy(&x, read, sizeof(float));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, double &x)
    {
        std::byte read[8];
        file.read(read, 8);
        std::memcpy(&x, read, sizeof(double));
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, bool &x)
    {
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<bool>(read);
        return file;
    }

    IBinaryFile &operator>>(IBinaryFile &file, std::string &x)
    {
        size_t size_string;
        file >> size_string;
        for (size_t i = 0; i < size_string; i++)
        {
            char c;
            file >> c;
            x.push_back(c);
        }
        return file;
    }
}