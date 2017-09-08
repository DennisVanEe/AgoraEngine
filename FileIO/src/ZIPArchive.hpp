#pragma once

#include <ios>
#include <zzip\zzip.h>
#include <Types.hpp>

namespace agora
{
	class ZIPArchive
	{
	public:
		class File
		{
        public:
            enum Pos { BEGIN = SEEK_SET, CURR = SEEK_CUR, END = SEEK_END };

		public:
            bool isCurrentNull() const;

            bool readBytes(aByte* data, int bytes, int* bytes_read) const;
            bool readBytes(aByte* data, int bytes) const;
            bool readFile(aByte* data, int chunk_size, int* bytes_read, int max_read = -1) const;

            bool seek(int offset, Pos whence) const;

		private:
            friend class ZIPArchive;
            File(ZZIP_FILE* file);
            void closeFile();

			ZZIP_FILE* m_zzipFile;
		};

	public:
        ZIPArchive();
		~ZIPArchive();

        ZIPArchive(const ZIPArchive&) = delete;
        void operator=(const ZIPArchive&) = delete;

        ZIPArchive(ZIPArchive&& stream);
        ZIPArchive& operator=(ZIPArchive&& stream);

		bool open(const char* dir);
		void close();
		bool isOpen() const;

        File getFile(const char* dir);
        void returnFile(File file);

	private:
		ZZIP_DIR* m_zzipDir;
	};
}