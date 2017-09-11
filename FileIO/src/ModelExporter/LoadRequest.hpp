#pragma once

#include <string>
#include <assimp/postprocess.h>

namespace agora
{
	namespace model_imp
	{
		// validation of mesh is done automatically
		enum LoadFlags
		{
			Gen_Normals			= aiProcess_GenNormals, // calculates tangents of the models
			Gen_SmoothNormals   = aiProcess_GenSmoothNormals, // removes vertices that are repeated
			Gen_Tangents	    = aiProcess_CalcTangentSpace, // converts faces that aren't triangles into triangles
			Pre_TransformVert   = aiProcess_PreTransformVertices
		};

        enum class TextComp
        {
            NONE,
            DXT1,
            DXT3,
            DXT5
        };

		// used to store information needed when importing a model.
		struct ImportRequest
		{
			std::string directory;
			unsigned loadFlags;
            TextComp textComp;

			inline ImportRequest(std::string dir, unsigned lFlags, TextComp tComp);
		};
	}
}

agora::model_imp::ImportRequest::ImportRequest(std::string dir, unsigned lFlags, TextComp tComp) :
	directory(dir),
    textComp(tComp)
{
	// Remove the some of the items already just in case.
	const unsigned defaultFlag = ((((aiProcessPreset_TargetRealtime_MaxQuality
		^ aiProcess_GenNormals)
		^ aiProcess_GenSmoothNormals)
		^ aiProcess_CalcTangentSpace)
		^ aiProcess_PreTransformVertices);

	loadFlags = defaultFlag | lFlags;
}