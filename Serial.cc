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

    //OBinaryFile::OBinaryFile(OBinaryFile &&other);
    //OBinaryFile::OBinaryFile &operator=(OBinaryFile &&other);



    /**
     * @brief Write `size` bytes pointed by `data` in the file
     *
     * Returns the number of bytes actually written
     */
    std::size_t OBinaryFile::write(const std::byte *data, std::size_t size){
        return fwrite (data , sizeof(std::byte), size, m_file);
    }


    OBinaryFile &operator<<(OBinaryFile &file, uint8_t x){
        std::cout << " ----- Type uint8_t ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, sizeof(x));
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int8_t x){
        std::cout << " ----- Type int8_t ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint16_t x){
        std::cout << " ----- Type uint16_t ----- " << '\n';
        std::byte b[2];
        std::memcpy(b, &x, 2);
        file.write(b, 2);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int16_t x){
        std::cout << " ----- Type int16_t ----- " << '\n';
        std::byte b[2];
        std::memcpy(b, &x, 2);
        file.write(b, 2);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint32_t x){
        std::cout << " ----- Type uint32_t ----- " << '\n';
        std::byte b[4];
        std::memcpy(b, &x, 4);
        file.write(b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int32_t x){
        std::cout << " ----- Type int32_t ----- " << '\n';
        std::byte b[4];
        std::memcpy(b, &x, 4);
        file.write(b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint64_t x){
        std::cout << " ----- Type uint64_t ----- " << '\n';
        std::byte b[8];
        std::memcpy(b, &x, 8);
        file.write(b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int64_t x){
        std::cout << " ----- Type int64_t ----- " << '\n';
        std::byte b[8];
        std::memcpy(b, &x, 8);
        file.write(b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, char x){
        std::cout << " ----- Type char ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, float x){
        std::cout << " ----- Type float ----- " << '\n';
        std::byte b[4];
        std::memcpy(b, &x, 4);
        file.write(b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, double x){
        std::cout << " ----- Type double ----- " << '\n';
        std::byte b[8];
        std::memcpy(b, &x, 8);
        file.write(b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, bool x){
        std::cout << " ----- Type bool ----- " << '\n';
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, const std::string &x){
        std::cout << " ----- Type string ----- " << '\n';
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
}
