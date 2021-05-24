#pragma once

#include <vector>
#include <string>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "Helper/Mesh.hh"
#include "Graphics/Shader.hh"
#include "Graphics/Texture.hh"
#include "Graphics/FontFace.hh"

class AssetManager
{
    FT_Library freetypeLib;

    std::vector<Mesh*> meshes;
    std::vector<Shader*> shaders;
    std::vector<Texture*> textures;
    std::vector<FontFace*> fonts;
    
    bool error;
    
public:
    AssetManager();
    ~AssetManager();

    Mesh* LoadObjMesh(std::string);
    Shader* LoadShader(std::string file);
    Shader* LoadShader(std::string vsfile, std::string fsfile);
    Texture* LoadTexture(std::string);
    FontFace* LoadFont(std::string);

    bool DidError();

    // void Free(Mesh*);
};