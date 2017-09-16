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
	bool addTexture(ID3D11Device*, ID3D11DeviceContext*, char*, Texture::TextureType t_type = Texture::TextureType::TGA);
	std::vector<ID3D11ShaderResourceView*> GetTextureArray();
	ID3D11ShaderResourceView** getRessources();

private:
	std::vector<std::shared_ptr<Texture>> m_textures;
	ID3D11ShaderResourceView** m_ressources;
	int m_count;
};

#endif
