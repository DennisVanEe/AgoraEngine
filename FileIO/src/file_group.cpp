#include "file_group.hpp"

ee::FileGroup::FileGroup() :
	m_zip(nullptr),
	m_file(nullptr)
{
}

ee::FileGroup::~FileGroup()
{
	zzip_dir_close(m_zip);
}

bool ee::FileGroup::loadGroup(const char* dir)
{
	assert(m_zip == nullptr);

	zzip_error_t errCode;
	ZZIP_DIR* zip = zzip_dir_open(dir, &errCode);

	if (!zip)
	{
		// TODO: error handling (maybe with the log)
		zzip_char_t* errStr = zzip_strerror(errCode);
		return false;
	}
	m_zip = zip;
	return true;
}

bool ee::FileGroup::loadGroup(const std::string& dir)
{
	return loadGroup(dir.c_str());
}

bool ee::FileGroup::loadFile(const char* dir)
{
	assert(m_zip != nullptr);

	closeFile();

	m_file = zzip_file_open(m_zip, dir, 0);
	if (!m_file)
	{
						  // TODO: error handling (maybe with the log)
		return false;
	}

	return true;
}

bool ee::FileGroup::loadFile(const std::string& dir)
{
	return loadFile(dir.c_str());
}

bool ee::FileGroup::readBytes(uByte* data, int bytes, int* bytes_read) const
{
	EE_ASSERT(m_file != nullptr);
	EE_ASSERT(bytes_read != nullptr);
	EE_ASSERT(bytes > 0);

	*bytes_read = zzip_read(m_file, data, bytes);
	if (*bytes_read < bytes)
		return false;

	return true;
}

bool ee::FileGroup::readBytes(uByte* data, int bytes) const
{
	EE_ASSERT(m_file != nullptr);
	EE_ASSERT(bytes > 0);

	int bytes_read = zzip_read(m_file, data, bytes);
	if (bytes_read < bytes)
		return false;

	return true;
}

bool ee::FileGroup::readFile(uByte* data, int chunk_size, int* bytes_read, int max_read) const
{
	EE_ASSERT(m_file != nullptr);
	EE_ASSERT(bytes_read != nullptr);

	*bytes_read = 0; // zero-bytes written

	// if no size check is needed, then don't check for it
	int currRead = 0;
	bool success = false;

	if (max_read < 0)
	{
		// returns number of bytes read (and if eof is encountered, not that)
		while (0 < (currRead = zzip_read(m_file, data, chunk_size)))
		{
			(*bytes_read) += currRead;
			data += chunk_size;
		}
		success = true;
	}
	else
	{
		uByte temp_buffer;

		// in case a very large chunk size was chosen
		if (chunk_size > max_read)
		{
			*bytes_read = zzip_read(m_file, data, max_read);
			if (0 < zzip_read(m_file, &temp_buffer, 1)) // check if there is a byte after the end
				success = false;
			else
				success = true;
		}
		else
		{
			success = true; // default is true unless it reads wrong byte
			while (0 < (currRead = zzip_read(m_file, data, chunk_size)))
			{
				(*bytes_read) += currRead;
				data += chunk_size;

				int bytes_to_end = max_read - *bytes_read;
				if (chunk_size > bytes_to_end) // if we can only read less than the given chunks
				{
					*bytes_read += zzip_read(m_file, data, bytes_to_end);
					if (0 < zzip_read(m_file, &temp_buffer, 1)) // check if there is a byte after the end
						success = false;
					else
						success = true;

					break;
				}
			}
		}
	}

	return success;
}

bool ee::FileGroup::seek(int offset, FilePos whence) const
{
	EE_ASSERT(m_file != nullptr);

	if (zzip_seek(m_file, offset, whence) < offset)
		return false;
	return true;
}