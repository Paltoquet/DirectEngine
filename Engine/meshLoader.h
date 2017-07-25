#pragma once

#include <d3d11.h>
#include <vector>
#include <directxmath.h>
#include <iostream>
#include <fstream>
#include <memory>

using namespace DirectX;

class MeshLoader
{
public:

	typedef struct
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	} VertexTextureType;

	typedef struct
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	}FaceType;


	MeshLoader();
	MeshLoader(std::string filename);
	~MeshLoader();

	bool loadMesh();
	VertexTextureType* getVertices();
	int getNbFaces();
	int getNbVertices();


private:
	void loadDataStructure();

private:
		std::string m_filename;
		std::string m_parserLoger;
		std::vector<XMFLOAT3> m_position;
		std::vector<XMFLOAT2> m_texture;
		std::vector<XMFLOAT3> m_normal;
		std::vector<FaceType> m_faces;
		std::vector<VertexTextureType> m_vertices;

};

