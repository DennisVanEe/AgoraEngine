#include "material.hpp"

#include <nvtt/nvtt.h>
#include <stbi/stb_image.h>

using namespace agora::math;
using namespace std;

agora::model_imp::Material::Material() noexcept :
    m_diffuse(0.f, 0.f, 0.f),
    m_specular(0.f, 0.f, 0.f),
    m_ambient(0.f, 0.f, 0.f),
    m_emmissive(0.f, 0.f, 0.f),
    m_transparent(0.f, 0.f, 0.f)
{
}

agora::model_imp::ImporterError agora::model_imp::Material::loadMaterial(const aiMaterial* aimat, const aiScene* scene, const std::string& rootDir)
{
    aiColor3D color;
    aimat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    m_diffuse = Float3(color.r, color.g, color.b);

    aimat->Get(AI_MATKEY_COLOR_SPECULAR, color);
    m_specular = Float3(color.r, color.g, color.b);

    aimat->Get(AI_MATKEY_COLOR_AMBIENT, color);
    m_ambient = Float3(color.r, color.g, color.b);

    aimat->Get(AI_MATKEY_COLOR_EMISSIVE, color);
    m_emmissive = Float3(color.r, color.g, color.b);

    aimat->Get(AI_MATKEY_COLOR_TRANSPARENT, color);
    m_transparent = Float3(color.r, color.g, color.b);

    aimat->Get(AI_MATKEY_OPACITY, m_opacity);
    aimat->Get(AI_MATKEY_SHININESS, m_shininess);
    aimat->Get(AI_MATKEY_SHININESS_STRENGTH, m_shininessStrength);
}

agora::model_imp::ImporterError agora::model_imp::Material::loadTexture(const aiMaterial* aimat, const aiScene* scene, TextureType textType, const std::string& rootDir, bool mipmap)
{
    aiTextureType aitextType;
    switch (textType)
    {
    case TextureType::DIFFUSE:
        aitextType = aiTextureType_DIFFUSE;
        break;
    case TextureType::SPECULAR:
        aitextType = aiTextureType_SPECULAR;
        break;
    case TextureType::AMBIENT:
        aitextType = aiTextureType_AMBIENT;
        break;
    case TextureType::EMISSIVE:
        aitextType = aiTextureType_EMISSIVE;
        break;
    case TextureType::NORMALS:
        aitextType = aiTextureType_NORMALS;
        break;
    default:
        assert(false); // this would be an internal error in the code itself
    }


    size_t numText = aimat->GetTextureCount(aitextType);

    for (size_t i = 0; i < numText; i++)
    {
        // get the texture info:
        aiString path;
        float blendFact;
        aiTextureOp blendFunc;
        aimat->GetTexture(aitextType, i, &path, nullptr, nullptr, &blendFact, &blendFunc, nullptr);

        // embedded in the file itself
        if (path.C_Str()[0] == '*') { return ImporterError::EMBEDDED_TEXTURES_NOT_SUPPORTED; }
       
        // load the texture from a file:
        string textureDir = rootDir + path.C_Str();
        int width, height, nChannels;       
        void* pixels = stbi_load(textureDir.c_str(), &width, &height, &nChannels, 0);
        if (pixels == nullptr) { return ImporterError::FAILED_TO_LOAD_TEXTURE; }

        nvtt::InputOptions inputOps;
        inputOps.setTextureLayout(nvtt::TextureType_2D, width, height);
        inputOps.setMipmapData(pixels, width, height);
        inputOps.setMipmapGeneration(mipmap);

        if (nChannels == 4)
        {
            inputOps.setAlphaMode(nvtt::AlphaMode_Transparency);
        }

        if (textType == TextureType::NORMALS)
        {
            inputOps.setNormalMap(true);
        }

        // Set the compression information:
        //---------------------------------------
        nvtt::CompressionOptions compOps;
        switch (nChannels)
        {
        case 1: // if there is only 1 channel
            compOps.setFormat(nvtt::Format_BC4); // RGTC1
            break;
        case 2: // usually this means it's a normal map
            compOps.setFormat(nvtt::Format_BC4); // RGTC2
            break;
        case 3:
            compOps.setFormat(nvtt::Format_BC1); // DXT1
            break;
        case 4:
            compOps.setFormat(nvtt::Format_BC3); // DXT5
            break;
        default:
            assert(false);
        }
        compOps.setQuality(nvtt::Quality_Production); // this will be done offline anyways
    }

    return ImporterError::SUCCESS;
}
