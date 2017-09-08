#include "ZIPArchive.hpp"
#include <cassert>
#include <iostream>

agora::ZIPArchive::ZIPArchive() :
	m_zzipDir(nullptr)
{
}

agora::ZIPArchive::~ZIPArchive()
{
	zzip_dir_close(m_zzipDir);
}

agora::ZIPArchive::ZIPArchive(ZIPArchive&& stream)
{
	assert(this != &stream); // if this occurs, it is a bug on the client side

	m_zzipDir = stream.m_zzipDir;
	stream.m_zzipDir = nullptr;
}

agora::ZIPArchive& agora::ZIPArchive::operator=(ZIPArchive&& stream)
{
	assert(this != &stream);

	m_zzipDir = stream.m_zzipDir;
	stream.m_zzipDir = nullptr;
	return *this;
}

bool agora::ZIPArchive::open(const char* dir)
{
	zzip_error_t errorCode;
	ZZIP_DIR* zzipDir = zzip_dir_open(dir, &errorCode);

	if (!zzipDir)
	{
		zzip_char_t* errStr = zzip_strerror(errorCode);
		// TODO: handle this error in writing
        return false;
	}

	m_zzipDir = zzipDir;
    return true;
}

void agora::ZIPArchive::close()
{
    assert(m_zzipDir != nullptr);

	zzip_dir_close(m_zzipDir); // documentation unclear on effect if m_zzipDir is null
	m_zzipDir = nullptr;
}

bool agora::ZIPArchive::isOpen() const
{
	return m_zzipDir != nullptr;
}

agora::ZIPArchive::File agora::ZIPArchive::getFile(const char* dir)
{
    assert(m_zzipDir != nullptr);

    return File(zzip_file_open(m_zzipDir, dir, 0));
}

void agora::ZIPArchive::returnFile(File file)
{
    file.closeFile();
}

//
// ZFStream Implementations
//

bool agora::ZIPArchive::File::isCurrentNull() const
{
    return m_zzipFile == nullptr;
}

agora::ZIPArchive::File::File(ZZIP_FILE* file) :
    m_zzipFile(file)
{
}

void agora::ZIPArchive::File::closeFile()
{
    zzip_file_close(m_zzipFile);
}

bool agora::ZIPArchive::File::readBytes(aByte* data, int bytes, int* bytes_read) const
{
    assert(m_zzipFile != nullptr);
    assert(bytes_read != nullptr);
    assert(bytes > 0);

    *bytes_read = zzip_read(m_zzipFile, data, bytes);
    return *bytes_read == bytes;
}

bool agora::ZIPArchive::File::readBytes(aByte* data, int bytes) const
{
    assert(m_zzipFile != nullptr);
    assert(bytes > 0);

    int bytes_read = zzip_read(m_zzipFile, data, bytes);
    return bytes_read < bytes;
}

bool agora::ZIPArchive::File::readFile(aByte* data, int chunk_size, int* bytes_read, int max_read) const
{
    assert(m_zzipFile != nullptr);
    assert(bytes_read != nullptr);

    *bytes_read = 0; // zero-bytes written

    // if no size check is needed, then don't check for it
    int currRead = 0;

    if (max_read < 0)
    {
        // returns number of bytes read (and if eof is encountered, not that)
        while (0 < (currRead = zzip_read(m_zzipFile, data, chunk_size)))
        {
            (*bytes_read) += currRead;
            data += chunk_size;
        }
        return true;
    }
    else
    {
        aByte temp_buffer;

        // in case a very large chunk size was chosen
        if (chunk_size > max_read)
        {
            *bytes_read = zzip_read(m_zzipFile, data, max_read);
            if (0 < zzip_read(m_zzipFile, &temp_buffer, 1)) // check if there is a byte after the end
            {
                return false;
            }
            return true;
        }
        else
        {
            while (0 < (currRead = zzip_read(m_zzipFile, data, chunk_size)))
            {
                (*bytes_read) += currRead;
                data += chunk_size;

                int bytes_to_end = max_read - *bytes_read;
                if (chunk_size > bytes_to_end) // if we can only read less than the given chunks
                {
                    *bytes_read += zzip_read(m_zzipFile, data, bytes_to_end);
                    if (0 < zzip_read(m_zzipFile, &temp_buffer, 1)) // check if there is a byte after the end
                    {
                        return false;
                    }
                    return true;
                }
            }
        }
    }

    return true;
}

bool agora::ZIPArchive::File::seek(int offset, Pos whence) const
{
    assert(m_zzipFile != nullptr);

    return !(zzip_seek(m_zzipFile, offset, whence) < offset);
}