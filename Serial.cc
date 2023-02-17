#include "Serial.h"

namespace serial{
    
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

    /**
     * @brief Write `size` bytes pointed by `data` in the file
     *
     * Returns the number of bytes actually written
     */
    std::size_t OBinaryFile::write(const std::byte *data, std::size_t size){
        return fwrite (data , sizeof(char), size, m_file);
    }










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
