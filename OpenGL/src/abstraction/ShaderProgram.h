#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <Glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Materials.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class ShaderProgram
{
public:
	ShaderProgram(const std::string& filepath);
	~ShaderProgram();

	void Bind() const;
	void Unbind() const;

	//Vectors
	//INT
	void setUniform1i(const std::string& name, int value);
	void setUniform2i(const std::string& name, int v0, int v1);
	void setUniform3i(const std::string& name, int v0, int v1, int v2);
	void setUniform4i(const std::string& name, int v0, int v1, int v2, int v3);

	//FLOAT
	void setUniform1f(const std::string& name, float value);
	void setUniform2f(const std::string& name, float v0, float v1);

	void setUniform3f(const std::string& name, float v0, float v1, float v2);
	void setUniform3f(const std::string& name, float v[3]);
	void setUniform3f(const std::string& name, const glm::vec3& vec3);

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform4f(const std::string& name, const glm::vec4& vec4);
	void setUniform4f(const std::string& name, float v[4]);

	//Matrix
	//MAT4
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

	//Materials
	//MATERIAL
	template<typename T>
	void setUniformMaterial(const std::string& name, const T& material)
	{
		static_assert(false);
	}

	template<>
	void setUniformMaterial<Material>(const std::string& name, const Material& material)
	{
		glUniform3fv(GetUniformLocation(name + "." + material.AmbName), 1, glm::value_ptr(material.Ambient));
		glUniform3fv(GetUniformLocation(name + "." + material.DiffName), 1, glm::value_ptr(material.Diffuse));
		glUniform3fv(GetUniformLocation(name + "." + material.SpecName), 1, glm::value_ptr(material.Specular));
		glUniform1f(GetUniformLocation(name + "." + material.ShinName), material.Shininess);
	}

	template<>
	void setUniformMaterial<MaterialMap>(const std::string& name, const MaterialMap& material)
	{
		material.DiffMap->Bind(material.DiffuseIndex);
		glUniform1i(GetUniformLocation(name + "." + material.DiffName), material.DiffuseIndex);
		material.SpecMap->Bind(material.SpecularIndex);
		glUniform1i(GetUniformLocation(name + "." + material.SpecName), material.SpecularIndex);
		glUniform1f(GetUniformLocation(name + "." + material.ShinName), material.Shininess);
	}

	//LIGHT
	template<typename T>
	void setUniformLight(const std::string& name, const T& light)
	{
		static_assert(false);
	}

	template<>
	void setUniformLight<Light>(const std::string& name, const Light& light)
	{
		setUniformBaseLight(name, light);
		glUniform3fv(GetUniformLocation(name + "." + light.PosName), 1, glm::value_ptr(light.Pos));
	}

	template<>
	void setUniformLight<LightDirectional>(const std::string& name, const LightDirectional& light)
	{
		setUniformBaseLight(name, light);
		glUniform3fv(GetUniformLocation(name + "." + light.DirName), 1, glm::value_ptr(light.Direction));
	}

	template<>
	void setUniformLight<LightPoint>(const std::string& name, const LightPoint& light)
	{
		setUniformBaseLight(name, light);
		glUniform3fv(GetUniformLocation(name + "." + light.PosName), 1, glm::value_ptr(light.Pos));
		glUniform1f(GetUniformLocation(name + "." + light.ConstName), light.Constante);
		glUniform1f(GetUniformLocation(name + "." + light.LinName), light.Linear);
		glUniform1f(GetUniformLocation(name + "." + light.QuadName), light.Quadratic);
	}

	template<>
	void setUniformLight<LightSpotlight>(const std::string& name, const LightSpotlight& light)
	{
		setUniformBaseLight(name, light);
		glUniform3fv(GetUniformLocation(name + "." + light.PosName), 1, glm::value_ptr(light.Pos));
		glUniform3fv(GetUniformLocation(name + "." + light.DirName), 1, glm::value_ptr(light.Direction));
		glUniform1f(GetUniformLocation(name + "." + light.ConstName), light.Constante);
		glUniform1f(GetUniformLocation(name + "." + light.LinName), light.Linear);
		glUniform1f(GetUniformLocation(name + "." + light.QuadName), light.Quadratic);
		glUniform1f(GetUniformLocation(name + "." + light.InnerName), light.InnerCutOff);
		glUniform1f(GetUniformLocation(name + "." + light.OutName), light.OutCutOff);
	}

private:
	void setUniformBaseLight(const std::string& name, const BaseLight& light);

private:
	std::string m_FilePath;
	unsigned int m_ShaderProgram;

	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);

	unsigned int CreateProgram(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
};