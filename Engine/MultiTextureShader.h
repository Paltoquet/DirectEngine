#pragma once
#ifndef _MULTITEXTURESHADERCLASS_H_
#define _MULTITEXTURESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include "shader.h"
#include <fstream>
using namespace std;

class MultiTextureShader : public Shader
{
public:
	MultiTextureShader();
	~MultiTextureShader();

public:
	bool Initialize(ID3D11Device*, HWND) override;
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**);

protected:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*) override;
	void ShutdownShader() override;

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**);
	void RenderShader(ID3D11DeviceContext*, int) override;

private:
	ID3D11SamplerState* m_sampleState;
};

#endif

