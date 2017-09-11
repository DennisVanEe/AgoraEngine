#pragma once

#include <vector>
#include <string>
#include <math/float3.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/material.h>

#include "number_ops.hpp"
#include "error_codes.hpp"

namespace agora
{
    namespace model_imp
    {
        enum class ShadingType  { FLAT = 0, GOURAUD = 1, PHONG = 2, BLINN = 3, DEFAULT = 4 };
        enum class BlendingFunc { ADD = 0, ONE_MINUS_DST_ALPHA = 1 };
        enum class TextureType  { DIFFUSE, SPECULAR, AMBIENT, EMISSIVE, NORMALS, OTHER };
        // not sure how I will handle "other" at the moment.

        class  Material
        {
        public:
            Material() noexcept;

            ImporterError loadMaterial(const aiMaterial* aimat, const aiScene* scene, const std::string& rootDir);

        private:
            struct Texture
            {
                size_t          offset;      // into the texture file
                BlendingFunc    blendFunc;   // the blending function the texture uses
                float           blendFact;

                size_t          bufferSize;  // the size of the image buffer (number of bytes)
                const uByte*    imageBuffer; // pointer to the actual texture data
  
                Texture() {}
                Texture(size_t o, const uByte* ib, size_t bs, BlendingFunc bf) :
                    offset(o), blendFunc(bf), imageBuffer(ib), bufferSize(bs) {}
                
                ~Texture() { delete[] imageBuffer; }
            };

        private:
            math::Float3         m_diffuse;
            math::Float3         m_specular;
            math::Float3         m_ambient;
            math::Float3         m_emmissive;
            math::Float3         m_transparent;

            float                m_opacity;
            float                m_shininess;
            float                m_shininessStrength;

            ShadingType          m_shadingType;

            std::vector<Texture> m_textures;

            ImporterError loadTexture(const aiMaterial* aimat, const aiScene* scene, TextureType textType, const std::string& rootDir, bool mipmap);
        };
    }
}