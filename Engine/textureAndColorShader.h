#pragma once

#include "textureShader.h"


class TextureAndColorShader: public TextureShader
{
public:
	TextureAndColorShader();
	~TextureAndColorShader();

	bool Initialize(ID3D11Device*, HWND) override;

protected: 
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*) override;
};

