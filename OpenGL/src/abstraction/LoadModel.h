#pragma once
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include <memory>


struct Vertex
{
	glm::vec3 Positition;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, std::vector<std::shared_ptr<Texture>>&& textures, const std::string& mat, const std::string& diff, const std::string& spec, const std::string& shin, float shininess);

	void Draw(ShaderProgram& shader);

private:
	void SetupMesh();

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<std::shared_ptr<Texture>> m_Textures;
	float m_Shininess;

	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_EBO;

	std::string m_MaterialName = "", m_DiffuseName, m_SpecularName, m_ShininessName;
};

class Model
{
public:
	Model(const std::string& path, const std::string& mat, const std::string& diff = "Texture_Diffuse", const std::string& spec = "Texture_Specular", const std::string& shin = "Shininess");

	void Draw(ShaderProgram& shader);

private:
	std::string m_MaterialName, m_DiffuseName, m_SpecularName, m_ShininessName;
	std::string m_Directory;
	std::vector<Mesh> m_Meshes;
	std::vector<std::shared_ptr<Texture>> m_TexturesLoaded;

	void Load(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};