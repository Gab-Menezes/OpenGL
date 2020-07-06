#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include <memory>

//material
struct Material
{
	glm::vec3 Ambient, Diffuse, Specular;
	float Shininess;

	std::string AmbName = "Ambient", DiffName = "Diffuse", SpecName = "Specular", ShinName = "Shininess";
};

struct MaterialMap
{
	std::unique_ptr<Texture> DiffMap;
	std::unique_ptr<Texture> SpecMap;
	int DiffuseIndex;
	int SpecularIndex;
	float Shininess;

	std::string DiffName = "Diffuse", SpecName = "Specular", ShinName = "Shininess";
};

//light
struct BaseLight
{
	void SetLightVecs()
	{
		Ambient = Color * AmbientStrength;
		Diffuse = Color * DiffuseStrength;
		Specular = Color * SpecularStrength;
	}
	
	glm::vec3 AmbientStrength, DiffuseStrength, SpecularStrength;
	glm::vec3 Ambient, Diffuse, Specular;
	glm::vec3 Color;

	std::string AmbName = "Ambient", DiffName = "Diffuse", SpecName = "Specular";
};

struct Light : public BaseLight
{
	glm::vec3 Pos;

	std::string PosName = "Pos";
};

struct LightDirectional : public BaseLight
{
	glm::vec3 Direction;

	std::string DirName = "Direction";
};

struct LightPoint : public BaseLight
{
	glm::vec3 Pos;
	float Constante, Linear, Quadratic;

	std::string PosName = "Pos", ConstName = "Kc", LinName = "Kl", QuadName = "Kq";
};

struct LightSpotlight : public LightPoint
{
	glm::vec3 Direction;
	float InnerCutOff, OutCutOff;

	std::string DirName = "LightDir", InnerName = "CutOff", OutName = "OutCutOff";
};