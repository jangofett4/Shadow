#include "AssetManager.hh"
#include "Helper/StringHelper.hh"
#include "freetype/freetype.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <lodepng.h>

AssetManager::AssetManager() : meshes(), shaders(), textures(), fonts()
{
    auto ftError = FT_Init_FreeType(&freetypeLib);
    if (ftError)
    {
        std::cout << "[AssetManager] Unable to initialize FreeType2 library!" << std::endl;
        error = true;
        return;
    }
}

AssetManager::~AssetManager()
{
    std::cout << "[AssetManager] Destroying " << meshes.size() << " meshes..." << std::endl;
    for (auto it = meshes.begin(); it != meshes.end(); it++)
        delete *it;

    std::cout << "[AssetManager] Destroying " << shaders.size() << " shaders..." << std::endl;
    for (auto it = shaders.begin(); it != shaders.end(); it++)
        delete *it;

    std::cout << "[AssetManager] Destroying " << textures.size() << " textures..." << std::endl;
    for (auto it = textures.begin(); it != textures.end(); it++)
        delete *it;

    std::cout << "[AssetManager] Destroying " << fonts.size() << " fonts..." << std::endl;
    for (auto it = fonts.begin(); it != fonts.end(); it++)
        delete *it;

    FT_Done_FreeType(freetypeLib);
}

Mesh* AssetManager::LoadObjMesh(std::string file)
{
    auto mesh = new Mesh();
    std::ifstream stream;
    stream.open(file);
    if (!stream.good())
    {
        std::cout << "[AssetManager] Error: Unable to open mesh file: " << file << std::endl;
        return nullptr;
    }

    std::vector<vec3> tmpVertex, tmpNormal;
    std::vector<vec2> tmpUV;
    
    std::string cmd;
    std::string line;
    while (std::getline(stream, line))
    {
        // trim(line);
        if (line.empty()) // empty line, skip
            continue;

        std::istringstream iss(line);
        iss >> cmd;

        if (cmd == "#") // comment line, skip
            continue;
        if (cmd == "v") // vertex
        {
            float x, y, z;
            iss >> x >> y >> z;
            tmpVertex.push_back(vec3(x, y, z));
        }
        else if (cmd == "vt")
        {
            float x, y;
            iss >> x >> y;
            tmpUV.push_back(vec2(x, y));
        }
        else if (cmd == "vn")
        {
            float x, y, z;
            iss >> x >> y >> z;
            tmpNormal.push_back(vec3(x, y, z));
        }
        else if (cmd == "f") // face (aka index)
        {
            char c;
            int i0, i1, i2;
            int t0, t1, t2;
            int n0, n1, n2;
            // TODO: I know this looks bad with that 'c' parameter
            // I dont know how to do stuff like scanf
            // also VN is not used
            iss >> i0 >> c >> t0 >> c >> n0;
            iss >> i1 >> c >> t1 >> c >> n1;
            iss >> i2 >> c >> t2 >> c >> n2;
            i0 = abs(i0); i1 = abs(i1); i2 = abs(i2);
            t0 = abs(t0); t1 = abs(t1); t2 = abs(t2);
            n0 = abs(n0); n1 = abs(n1); n2 = abs(n2);
            // Vertices
            mesh->Vertices.push_back(tmpVertex[i0 - 1]);
            mesh->Vertices.push_back(tmpVertex[i1 - 1]);
            mesh->Vertices.push_back(tmpVertex[i2 - 1]);

            if (t0 > 0 && t1 > 0 && t2 > 0)
            {
                // Texture coordinates
                mesh->UVs.push_back(tmpUV[t0 - 1]);
                mesh->UVs.push_back(tmpUV[t1 - 1]);
                mesh->UVs.push_back(tmpUV[t2 - 1]);
            }

            /*
            if (n0 < 0 || n1 < 0 || n2 < 0)
                continue;
            // Normals
            mesh->Normals.push_back(tmpNormal[n0 - 1]);
            mesh->Normals.push_back(tmpNormal[n1 - 1]);
            mesh->Normals.push_back(tmpNormal[n2 - 1]);
            */
        }
    }
    stream.close();

    meshes.push_back(mesh);
    return mesh;
}

Shader* AssetManager::LoadShader(std::string file)
{
    std::ifstream ifsvs;
    ifsvs.open(file + ".vs.glsl");
    if (!ifsvs.good())
    {
        std::cout << "[AssetManager] Error: Unable to open shader vertex shader file: " << file << ".vs.glsl" << std::endl;
        return nullptr;
    }

    std::ifstream ifsfs;
    ifsfs.open(file + ".fs.glsl");
    if (!ifsfs.good())
    {
        std::cout << "[AssetManager] Error: Unable to open shader fragment shader file: " << file << ".fs.glsl" << std::endl;
        return nullptr;
    }

    std::stringstream ssvs;
    ssvs << ifsvs.rdbuf();
    ifsvs.close();

    std::stringstream ssfs;
    ssfs << ifsfs.rdbuf();
    ifsfs.close();

    auto vs = ssvs.str();
    auto fs = ssfs.str();

    auto shader = new Shader(vs, fs);
    shaders.push_back(shader);
    return shader;
}

Texture* AssetManager::LoadTexture(std::string file)
{
    std::vector<uint8_t> png;
    std::vector<uint8_t> pixels;
    unsigned w, h;
    
    auto error = lodepng::load_file(png, file);
    if (error)
        return nullptr;
    
    error = lodepng::decode(pixels, w, h, png);
    if (error)
        return nullptr;
    
    // sending data pointer is safe, constructor will immediately upload the texture to GPU
    // texture data on RAM can and SHOULD be freed
    auto texture = new Texture(w, h, pixels.data());
    textures.push_back(texture);
    return texture;
}

FontFace* AssetManager::LoadFont(std::string file)
{
    FT_Face rawFontFace;
    auto error = FT_New_Face(freetypeLib, file.c_str(), 0, &rawFontFace);
    if (error)
    {
        std::cout << "[AssetManager] Unable to load truetype font: " << FT_Error_String(error) << std::endl;
        return nullptr;
    }

    auto fontFace = new FontFace(rawFontFace);
    fonts.push_back(fontFace);
    return fontFace;
}

bool AssetManager::DidError()
{
    return error;
}