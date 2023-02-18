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
        return fwrite (data , sizeof(char), size, m_file);
    }


    OBinaryFile &operator<<(OBinaryFile &file, uint8_t x){
        std::cout << " ----- Type uint8_t ----- " << '\n';
        std::byte b = std::byte(x);
        size_t w = file.write(&b, sizeof(x));
        std::cout << "written : " << static_cast <int>(w) << '\n';
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int8_t x){
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint16_t x){
        std::byte b = std::byte(x);
        file.write(&b, 2);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int16_t x){
        std::byte b = std::byte(x);
        file.write(&b, 2);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint32_t x){
        std::byte b = std::byte(x);
        file.write(&b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int32_t x){
        std::byte b = std::byte(x);
        file.write(&b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, uint64_t x){
        std::byte b = std::byte(x);
        file.write(&b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, int64_t x){
        std::byte b = std::byte(x);
        file.write(&b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, char x){
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, float x){
        std::byte b = std::byte(x);
        file.write(&b, 4);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, double x){
        std::byte b = std::byte(x);
        file.write(&b, 8);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, bool x){
        std::byte b = std::byte(x);
        file.write(&b, 1);
        return file;
    }

	OBinaryFile &operator<<(OBinaryFile &file, const std::string &x){
        size_t size = x.size();
        std::byte size_b = std::byte(size);
        file.write(&size_b, sizeof(size));

        for (auto& letter : x) {
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
        return fread(data , sizeof(char), size, m_file);
    }



}
