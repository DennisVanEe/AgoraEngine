#include "importer.hpp"

#include <math/float3.hpp>
#include <math/float2.hpp>

using namespace std;

agora::model_imp::ImporterError agora::model_imp::ModelImporter::beginImportingModels()
{
	if (m_requestList.size() == 0) { return ImporterError::REQUEST_QUEUE_EMPTY; }

	unsigned numThreads = std::thread::hardware_concurrency() == 0 ? 1 : numThreads;

	std::size_t procPerThread;
	if (m_requestList.size() <= numThreads)
	{
		procPerThread = 1;
		numThreads = m_requestList.size();
	}
	else
	{
		procPerThread = m_requestList.size() / numThreads;
	}

	m_threads.reserve(numThreads);
	size_t pos = 0;
	try
	{
		for (size_t i = 0; i < numThreads - 1; i++, pos += procPerThread)
		{
			m_threads.push_back(thread(&ModelImporter::singleThreadImport, this, pos, procPerThread));
		}
		m_threads.emplace_back(thread(&ModelImporter::singleThreadImport, this, pos, m_requestList.size() - 1));
	}
	catch (...)
	{
		return ImporterError::FAILED_TO_CONSTRUCT_THREADS;
	}

	try
	{
		for (auto& currThread : m_threads)
		{
			currThread.join();
		}
	}
	catch (...)
	{
		return ImporterError::FAILED_TO_JOIN_THREADS;
	}

    return m_impErr;
}

std::string agora::model_imp::ModelImporter::getErrorStr() const
{
    return m_impErrStr;
}

void agora::model_imp::ModelImporter::singleThreadImport(size_t startIndex, size_t numRequests)
{
    // create the importer
    Assimp::Importer importer;

    for (std::size_t i = startIndex; i < startIndex + numRequests; i++)
    {
        ImportRequest& req = m_requestList[i];

        const aiScene* scene = importer.ReadFile(req.directory, req.loadFlags);

        if (m_impErr != ImporterError::SUCCESS) { return; }
        if (scene == nullptr)
        {
            setError(ImporterError::FAILED_TO_PARSE_FILE, importer.GetErrorString());
            return;
        }


    }
}

bool agora::model_imp::ModelImporter::processMesh(Mesh* o_mesh, const aiMesh* aimesh, unsigned loadFlag)
{
    using namespace agora::math;

    vector<Float3> t_positions;
    vector<Float3> t_normals;
    vector<unsigned> t_indices;

    vector<Float3> t_tangents;
    vector<Float3> t_bitangents;

    vector<Float3> t_uvcoords3;
    vector<Float2> t_uvcoords2;

    vector<Float4> t_vertColor;

    // gen normals if necessary:
    bool genNormals = loadFlag & ~LoadFlags::Gen_Normals || loadFlag & ~LoadFlags::Gen_SmoothNormals;
    bool genTangents = loadFlag & ~LoadFlags::Gen_Tangents;

    for (size_t i = 0; i < aimesh->mNumVertices; i++)
    {
        t_positions.push_back(Float3(aimesh->mVertices[i][0], aimesh->mVertices[i][1], aimesh->mVertices[i][2]));
        if (genNormals)
        {
            t_normals.push_back(Float3(aimesh->mNormals[i][0], aimesh->mNormals[i][1], aimesh->mNormals[i][2]));
        }

        if (genTangents)
        {
            t_tangents.push_back(Float3(aimesh->mTangents[i].x, aimesh->mTangents[i].y, aimesh->mTangents[i].z));
            t_bitangents.push_back(Float3(aimesh->mBitangents[i][0], aimesh->mBitangents[i][1], aimesh->mBitangents[i][2]));
        }

        // for now I only support one set of UV components
        if (aimesh->mTextureCoords[0])
        {
            if (aimesh->mNumUVComponents[0] == 2)
            {
                t_uvcoords2.push_back(Float2(aimesh->mTextureCoords[0][i].x, aimesh->mTextureCoords[0][i].y));
            }
            else if (aimesh->mNumUVComponents[0] == 3)
            {
                t_uvcoords3.push_back(Float3(aimesh->mTextureCoords[0][i].x, aimesh->mTextureCoords[0][i].y, aimesh->mTextureCoords[0][i].z));
            }
        }

        if (aimesh->mColors[0])
        {
            t_vertColor.push_back(Float4(aimesh->mColors[0][i].r, aimesh->mColors[0][i].g, aimesh->mColors[0][i].b, aimesh->mColors[0][i].a));
        }
    }

    for (size_t i = 0; i < aimesh->mNumFaces; i++)
    {
        aiFace& face = aimesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            t_indices.push_back(face.mIndices[j]);
        }
    }

    o_mesh->addPositions(move(t_positions));
    o_mesh->addNormals(move(t_normals));
    o_mesh->addIndices(move(t_indices));

    o_mesh->addTangents(t_tangents);
    o_mesh->addBitangents(t_bitangents);

    o_mesh->addUVWCoords(t_uvcoords3);
    o_mesh->addUVCoords(t_uvcoords2);

    o_mesh->addVertColor(t_vertColor);

    return true;
}