#ifndef _TEXTUREARRAYCLASS_H_
#define _TEXTUREARRAYCLASS_H_

#include "texture.h"
#include <memory>
#include <vector>
class TextureArray
{
public:
	TextureArray();
	~TextureArray();

	bool Initialize(ID3D11Device*, WCHAR**, int);
	void Shutdown();

	std::vector<ID3D11ShaderResourceView*> GetTextureArray();

private:
	std::vector<std::shared_ptr<Texture>> m_textures;
	int m_count;
};

#endif
