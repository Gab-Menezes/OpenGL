#include "LoadModel.h"
#include "VertexBufferAttLayout.h"
#include "Renderer.h"

//-----------------MESH-----------------

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, std::vector<std::shared_ptr<Texture>>&& textures, const std::string& mat, const std::string& diff, const std::string& spec, const std::string& shin, float shininess) :
	m_Vertices(std::move(vertices)),
	m_Indices(std::move(indices)),
	m_Textures(std::move(textures)),
	m_MaterialName(mat),
	m_DiffuseName(diff),
	m_SpecularName(spec),
	m_ShininessName(shin),
	m_Shininess(shininess)
{
	SetupMesh();
}

void Mesh::Draw(ShaderProgram & shader)
{
	int diffuseNr = 1;
	int specularNr = 1;

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		std::string number;
		std::string name = m_Textures[i]->GetType();
		if (name == m_DiffuseName)
			number = std::to_string(diffuseNr++);
		else if (name == m_SpecularName)
			number = std::to_string(specularNr++);

		m_Textures[i]->Bind(i);
		shader.setUniform1i(m_MaterialName + name + number, i);
	}
	if (m_Shininess != -1.0f)
	{
		shader.setUniform1f(m_MaterialName + m_ShininessName, m_Shininess);
	}

	Renderer render;
	render.Draw(shader, *m_VAO, *m_EBO);
	m_VAO->Unbind();
}

void Mesh::SetupMesh()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VAO->Bind();

	m_VBO = std::make_unique<VertexBuffer>(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));
	m_VBO->Bind();
	VertexBufferAttLayout layout;
	layout.Push<float>(3);//vertices
	layout.Push<float>(3);//normals
	layout.Push<float>(2);//tex coord
	m_VAO->AddAtt(*m_VBO, layout);

	m_EBO = std::make_unique<IndexBuffer>(&m_Indices[0], m_Indices.size());
	m_EBO->Bind();

	m_VAO->Unbind();
}


//-----------------MODEL-----------------

Model::Model(const std::string & path, const std::string& mat, const std::string& diff, const std::string& spec, const std::string & shin) : 
	m_MaterialName(mat + "."),
	m_DiffuseName(diff),
	m_SpecularName(spec),
	m_ShininessName(shin)

{
	Load(path);
}

void Model::Draw(ShaderProgram & shader)
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i].Draw(shader);
	}
}

void Model::Load(const std::string & path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR ASSIMP: " << importer.GetErrorString() << std::endl;
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));

	m_Meshes.reserve(scene->mNumMeshes);

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	vertices.reserve(mesh->mNumVertices);
	std::vector<unsigned int> indices;
	std::vector<std::shared_ptr<Texture>> textures;

	//vertex
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Positition = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(std::move(vertex));
	}

	//indices
	unsigned int count = 0;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		count += mesh->mFaces[i].mNumIndices;
	}
	indices.reserve(count);
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	float shininess = -1.0f;
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<std::shared_ptr<Texture>> diffuseMap = LoadMaterialTextures(material, aiTextureType_DIFFUSE, m_DiffuseName);
		std::vector<std::shared_ptr<Texture>> specularMap = LoadMaterialTextures(material, aiTextureType_SPECULAR, m_SpecularName);

		textures.reserve(diffuseMap.capacity() + specularMap.capacity());
		if (textures.capacity() > 0)
		{
			textures.insert(textures.end(), std::make_move_iterator(diffuseMap.begin()), std::make_move_iterator(diffuseMap.end()));
			textures.insert(textures.end(), std::make_move_iterator(specularMap.begin()), std::make_move_iterator(specularMap.end()));
		}

		material->Get(AI_MATKEY_SHININESS, shininess);
	}

	m_Meshes.emplace_back(std::move(vertices), std::move(indices), std::move(textures), m_MaterialName, m_DiffuseName, m_SpecularName, m_ShininessName, shininess);
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial * mat, aiTextureType type, const std::string & typeName)
{
	std::vector<std::shared_ptr<Texture>> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		std::string path = m_Directory + '/' + str.C_Str();
		for (unsigned int j = 0; j < m_TexturesLoaded.size(); j++)
		{
			if (m_TexturesLoaded[j]->GetPath().data() == path.data())
			{
				textures.push_back(m_TexturesLoaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			m_TexturesLoaded.emplace_back(std::make_shared<Texture>(path, false, false, typeName));
			textures.push_back(m_TexturesLoaded.back());
		}
	}

	return textures;
}
