#pragma once

#include <string>
#include <zzip\zzip.h>
#include <cassert>

#include <Types.hpp>

namespace agora
{
	enum FilePos {BEGIN = SEEK_SET, CURR = SEEK_CUR, END = SEEK_END};

	class FileGroup
	{
	public:
		FileGroup();
		~FileGroup();

		bool loadGroup(const std::string& dir);
		bool loadGroup(const char* dir);
		bool loadFile(const std::string& dir);
		bool loadFile(const char* dir);

		inline bool fileLoaded() const;
		inline void closeFile();

		/**
		* Reads the number of bytes specified if a file was loaded. If a file was not loaded
		* it return false. If file was not closed, each call reads next bytes. If eof is reached,
		* further reads will return false
		* @param data pointer to where the data is to be written.
		* @param bytes the number of bytes of data to be written.
		* @param bytes_read the number of bytes that have actually been written (always modified).
		* @return true if the correct number of bytes were written, false if less bytes were written
		*/
		bool readBytes(aByte* data, int bytes, int* bytes_read) const;
		bool readBytes(aByte* data, int bytes) const;
		/**
		* Reads the entire file if it was loaded. If a file was not loaded it returns false. If the 
		* process was successful (entire file was read) later reads will return false.
		* @param data pointer to where the data is to be written.
		* @param chunk_size the number of bytes to be processed at a time (might impact performance, not result integirty).
		* @param bytes_read the number of bytes that have actually been written (always modified).
		* @param max_read the maximum number of bytes to be read. Do not include if no restriction exists.
		* @return true if the whole file was read and under the max_read parameter (if provided), and false otherwise.
		*/
		bool readFile(aByte* data, int chunk_size, int* bytes_read , int max_read = -1) const;
		/**
		* Move to a different location in the file by the given by the C defines: SEEK_SET, SEEK_CURR, and SEEK_END
		* @param offset amount to traverse
		* @param whence the location to start from.
		* @return true was successful within the limits, false otherwise
		*/
		bool seek(int offset, FilePos whence) const;

		inline int getCurrPos() const;

	private:
		ZZIP_DIR* m_zip;
		ZZIP_FILE* m_file;
	};
}


// inline definitions:

bool agora::FileGroup::fileLoaded() const
{
	return m_file != nullptr;
}

void agora::FileGroup::closeFile()
{
	if (m_file != nullptr)
		zzip_file_close(m_file); // close the file
}

int agora::FileGroup::getCurrPos() const
{
	assert(m_file != nullptr);

	return zzip_tell(m_file);
}