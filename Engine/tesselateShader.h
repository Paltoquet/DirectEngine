#pragma once

#include "shader.h"


class TesselateShader : public Shader
{

private:
	struct TessellationBufferType
	{
		float tessellationAmount;
		XMFLOAT3 padding;
	};

public:
	TesselateShader();
	TesselateShader(const TesselateShader&);
	~TesselateShader();

private:
	ID3D11HullShader* m_hullShader;
	ID3D11DomainShader* m_domainShader;
	ID3D11Buffer* m_tessellationBuffer;

public:
	bool Initialize(ID3D11Device*, HWND) override;
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, float);

protected:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*, WCHAR*, WCHAR*);
	void ShutdownShader() override;

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, float);
	void RenderShader(ID3D11DeviceContext*, int) override;

};
