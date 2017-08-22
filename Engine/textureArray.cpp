#include "stdafx.h"
#include "textureArray.h"


TextureArray::TextureArray()
{
}

bool TextureArray::Initialize(ID3D11Device* device, WCHAR** filename, int count)
{
	HRESULT result;

	for (int i = 0; i < count; i++) {
		std::shared_ptr<Texture> tex = std::make_shared<Texture>();
		result &= tex->InitializeDDS(device, filename[i]);
		m_textures.push_back(std::make_shared<Texture>());
	}
	m_count = count;
	return result;
}

void TextureArray::Shutdown()
{
	for (auto t : m_textures) {
		t->Shutdown();
	}

	return;
}

std::vector<ID3D11ShaderResourceView*> TextureArray::GetTextureArray()
{
	std::vector<ID3D11ShaderResourceView*> result;
	for (auto t : m_textures) {
		result.push_back(t->GetTexture);
	}
	return result;
}

TextureArray::~TextureArray()
{
}
