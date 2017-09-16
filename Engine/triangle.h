#pragma once


#include "model.h"


class Triangle : public Model
{

private:
	struct VertexColorType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
public:
	Triangle();
	~Triangle();

protected:
	virtual bool InitializeBuffers(ID3D11Device*) override;
	virtual void RenderBuffers(ID3D11DeviceContext*) override;
};

