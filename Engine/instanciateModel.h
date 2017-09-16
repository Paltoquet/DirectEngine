#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include "meshLoader.h"
#include "model.h"

#include "texture.h"
#include "textureArray.h"

using namespace DirectX;

class InstanciateModel: public Model
{

	
	struct InstanceType
	{
		XMFLOAT3 position;
	};

private:

	ID3D11Buffer* m_instanceBuffer;
	int m_instanceCount;

public:
	InstanciateModel();
	InstanciateModel(char* file);
	~InstanciateModel();

	int GetVertexCount();
	int GetInstanceCount();

private:
	bool InitializeBuffers(ID3D11Device*) override;
	void ShutdownBuffers() override;
	void RenderBuffers(ID3D11DeviceContext*) override;
};


