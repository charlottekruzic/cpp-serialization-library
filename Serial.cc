#include "Serial.h"

namespace serial{
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
    : m_filename(filename)
    {
        const char* opening_mode = (mode==Mode::Append ? "a" : "w");
        m_file = (fopen(filename.c_str(),opening_mode));
        if (m_file == NULL) {
            throw std::runtime_error("Error while opening the file!");
        }
    }

    OBinaryFile::OBinaryFile(OBinaryFile &&other) noexcept{
       /* m_filename=other.m_filename;
        m_file=other.m_file;

        std::byte b[1024];*/
        

        

    }

    OBinaryFile& OBinaryFile::operator=(OBinaryFile &&other) noexcept{
        
        return *this;
    }


    /**
     * @brief Closes the file
     */
	OBinaryFile::~OBinaryFile(){
        int ret = fclose(m_file);
        if (ret == EOF) { 
            fprintf(stderr, "Error while closing the file!\n");
            throw std::runtime_error("Error while opening %s!\n");
        }
    }

    



    /**
     * @brief Write `size` bytes pointed by `data` in the file
     *
     * Returns the number of bytes actually written
     */
    std::size_t OBinaryFile::write(const std::byte *data, std::size_t size){
        return fwrite (data , sizeof(std::byte), size, m_file);
    }


    OBinaryFile &operator<<(OBinaryFile &file, uint8_t x){
        //std::cout << " ----- Type uint8_t ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, sizeof(x));
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int8_t x){
        //std::cout << " ----- Type int8_t ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint16_t x){
        //std::cout << " ----- Type uint16_t ----- " << '\n';
        std::byte b[2];
        b[0] = static_cast<std::byte>((x >> 8) & 0xFF);
        b[1] = static_cast<std::byte>(x & 0xFF);
        file.write(b, 2);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int16_t x){
        //std::cout << " ----- Type int16_t ----- " << '\n';
        std::byte b[2];
        b[0] = static_cast<std::byte>((x >> 8) & 0xFF);
        b[1] = static_cast<std::byte>(x & 0xFF);
        file.write(b, 2);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint32_t x){
        //std::cout << " ----- Type uint32_t ----- " << '\n';
        std::byte b[4];
        b[0] = static_cast<std::byte>((x >> 24) & 0xFF);
        b[1] = static_cast<std::byte>((x >> 16) & 0xFF);
        b[2] = static_cast<std::byte>((x >> 8) & 0xFF);
        b[3] = static_cast<std::byte>(x & 0xFF);
        file.write(b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int32_t x){
        //std::cout << " ----- Type int32_t ----- " << '\n';
        std::byte b[4];
        b[0] = static_cast<std::byte>((x >> 24) & 0xFF);
        b[1] = static_cast<std::byte>((x >> 16) & 0xFF);
        b[2] = static_cast<std::byte>((x >> 8) & 0xFF);
        b[3] = static_cast<std::byte>(x & 0xFF);
        file.write(b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint64_t x){
        //std::cout << " ----- Type uint64_t ----- " << '\n';
        std::byte b[8];
        b[0] = static_cast<std::byte>((x >> 56) & 0xFF);
        b[1] = static_cast<std::byte>((x >> 48) & 0xFF);
        b[2] = static_cast<std::byte>((x >> 40) & 0xFF);
        b[3] = static_cast<std::byte>((x >> 32) & 0xFF);
        b[4] = static_cast<std::byte>((x >> 24) & 0xFF);
        b[5] = static_cast<std::byte>((x >> 16) & 0xFF);
        b[6] = static_cast<std::byte>((x >> 8) & 0xFF);
        b[7] = static_cast<std::byte>(x & 0xFF);
        file.write(b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int64_t x){
        //std::cout << " ----- Type int64_t ----- " << '\n';
        std::byte b[8];
        b[0] = static_cast<std::byte>((x >> 56) & 0xFF);
        b[1] = static_cast<std::byte>((x >> 48) & 0xFF);
        b[2] = static_cast<std::byte>((x >> 40) & 0xFF);
        b[3] = static_cast<std::byte>((x >> 32) & 0xFF);
        b[4] = static_cast<std::byte>((x >> 24) & 0xFF);
        b[5] = static_cast<std::byte>((x >> 16) & 0xFF);
        b[6] = static_cast<std::byte>((x >> 8) & 0xFF);
        b[7] = static_cast<std::byte>(x & 0xFF);
        file.write(b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, char x){
        //std::cout << " ----- Type char ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, float x){
        //std::cout << " ----- Type float ----- " << '\n';
        std::byte b[4];
        std::memcpy(b, &x, 4);
        file.write(b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, double x){
        //std::cout << " ----- Type double ----- " << '\n';
        std::byte b[8];
        std::memcpy(b, &x, 8);
        file.write(b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, bool x){
        //std::cout << " ----- Type bool ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, const std::string &x){
        //std::cout << " ----- Type string ----- " << '\n';
        size_t size = x.size();  
        file<<size;
        for (char letter : x) {
            file<<letter;
        }
        return file;
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
    : m_filename(filename)
    , m_file(fopen(filename.c_str(),"r"))
    {
        if (m_file == NULL) {
            throw std::runtime_error("Error while opening the file!");
        }
    }

   /* IBinaryFile::IBinaryFile(IBinaryFile &&other) noexcept{
        

    }

    IBinaryFile& IBinaryFile::operator=(IBinaryFile &&other) noexcept{
        
    }*/


    /**
     * @brief Closes the file
     */
	IBinaryFile::~IBinaryFile(){
        int ret = fclose(m_file);
        if (ret == EOF) { 
            fprintf(stderr, "Error while closing the file!\n");
            throw std::runtime_error("Error while opening %s!\n");
        }

    }

    /**
     * @brief Read `size` bytes from the file and store them in the buffer
     * pointed by `data`.
     *
     * Returns the number of bytes actually read.
     */
    std::size_t IBinaryFile::read(std::byte *data, std::size_t size){
        return fread(data , sizeof(std::byte), size, m_file);
    }




    IBinaryFile &operator>>(IBinaryFile &file, int8_t &x){
        //std::cout << " +++++ Type int8_t +++++ " << '\n';
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<int8_t>(read);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, uint8_t &x){
        //std::cout << " +++++ Type uint8_t +++++ " << '\n';
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<uint8_t>(read);
        return file;       
    }

	IBinaryFile &operator>>(IBinaryFile &file, int16_t &x){
        //std::cout << " +++++ Type int16_t +++++ " << '\n';
        std::byte read[2];
        file.read(read, 2);
        x = static_cast<int16_t>(read[0]) << 8 |
        static_cast<int16_t>(read[1]);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, uint16_t &x){
        //std::cout << " +++++ Type uint16_t +++++ " << '\n';
        std::byte read[2];
        file.read(read, 2);
        x = static_cast<uint16_t>(read[0]) << 8 |
        static_cast<uint16_t>(read[1]);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, int32_t &x){
        //std::cout << " +++++ Type int32_t +++++ " << '\n';
        std::byte read[4];
        file.read(read, 4);
        x = static_cast<int32_t>(read[0]) << 24 |
        static_cast<int32_t>(read[1]) << 16 |
        static_cast<int32_t>(read[2]) << 8 |
        static_cast<int32_t>(read[3]);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, uint32_t &x){
        //std::cout << " +++++ Type uint32_t +++++ " << '\n';
        std::byte read[4];
        file.read(read, 4);
        x = static_cast<uint32_t>(read[0]) << 24 |
        static_cast<uint32_t>(read[1]) << 16 |
        static_cast<uint32_t>(read[2]) << 8 |
        static_cast<uint32_t>(read[3]);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, int64_t &x){
        //std::cout << " +++++ Type int64_t +++++ " << '\n';
        std::byte read[8];
        file.read(read, 8);
        x = static_cast<int64_t>(read[0]) << 56 |
        static_cast<int64_t>(read[1]) << 48 |
        static_cast<int64_t>(read[2]) << 40 |
        static_cast<int64_t>(read[3]) << 32 |
        static_cast<int64_t>(read[4]) << 24 |
        static_cast<int64_t>(read[5]) << 16 |
        static_cast<int64_t>(read[6]) << 8 |
        static_cast<int64_t>(read[7]);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, uint64_t &x){
        //std::cout << " +++++ Type uint64_t +++++ " << '\n';
        std::byte read[8];
        file.read(read, 8);
        x = static_cast<uint64_t>(read[0]) << 56 |
        static_cast<uint64_t>(read[1]) << 48 |
        static_cast<uint64_t>(read[2]) << 40 |
        static_cast<uint64_t>(read[3]) << 32 |
        static_cast<uint64_t>(read[4]) << 24 |
        static_cast<uint64_t>(read[5]) << 16 |
        static_cast<uint64_t>(read[6]) << 8 |
        static_cast<uint64_t>(read[7]);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, char &x){
        //std::cout << " +++++ Type char +++++ " << '\n';
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<char>(read);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, float &x){
        //std::cout << " +++++ Type float +++++ " << '\n';
        std::byte read[4];
        file.read(read, 4);
        std::memcpy(&x, read, sizeof(float));
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, double &x){
        //std::cout << " +++++ Type double +++++ " << '\n';
        std::byte read[8];
        file.read(read, 8);
        std::memcpy(&x, read, sizeof(double));
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, bool &x){
        //std::cout << " +++++ Type bool +++++ " << '\n';
        std::byte read{};
        file.read(&read, 1);
        x = static_cast<bool>(read);
        return file;
    }

	IBinaryFile &operator>>(IBinaryFile &file, std::string &x){
        //std::cout << " +++++ Type string +++++ " << '\n';
        size_t size_string;
        file >> size_string;

        for (size_t i = 0; i < size_string; i++) {
            char c;
            file >> c;
            x.push_back(c);
        }
        return file;
    }
}
