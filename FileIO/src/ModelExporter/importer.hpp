#pragma once

#include <vector>
#include <string>
#include <thread>
#include <mutex>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#include "LoadRequest.hpp"
#include "ErrorCodes.hpp"
#include "mesh.hpp"

namespace agora
{
	namespace model_imp
	{
		class ModelImporter
		{
		public:
			static ModelImporter&   initImporter();

			// returns zero if there was an error
			inline unsigned         addRequest(std::string dir, unsigned loadFlags, TextComp textComp);

			ImporterError           beginImportingModels();
            std::string             getErrorStr() const;

		private:
			ModelImporter();

			std::vector<ImportRequest>      m_requestList;
			std::vector<std::thread>        m_threads;

			std::mutex                      m_impErrMutex;
			ImporterError                   m_impErr;
			std::mutex                      m_impErrStrMutex;
			std::string                     m_impErrStr;

            // component setting:
            bool                            processMesh(Mesh* o_mesh, const aiMesh* aimesh, unsigned loadFlag);

            void                            singleThreadImport(size_t startIndex, size_t numRequests);
            inline void                     setError(ImporterError error, const char* msg);
            inline void                     setError(ImporterError error);

		public:
			                ModelImporter(ModelImporter&) = delete;
			void            operator=(ModelImporter&) = delete;
		};
	}
}

// inline definitions 

unsigned agora::model_imp::ModelImporter::addRequest(std::string dir, unsigned loadFlags, TextComp textComp)
{
	m_requestList.push_back(ImportRequest(dir, loadFlags, textComp));
}

void agora::model_imp::ModelImporter::setError(ImporterError error, const char* msg)
{
    m_impErrMutex.lock();
    m_impErr = error;
    m_impErrMutex.unlock();

    m_impErrStrMutex.lock();
    m_impErrStr.assign(msg);
    m_impErrStrMutex.unlock();
}

void agora::model_imp::ModelImporter::setError(ImporterError error)
{
    m_impErrMutex.lock();
    m_impErr = error;
    m_impErrMutex.unlock();
}