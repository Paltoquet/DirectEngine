#include "stdafx.h"
#include "textureArray.h"


TextureArray::TextureArray()
{
	m_ressources = nullptr;
	m_count = 0;
}

bool TextureArray::Initialize(ID3D11Device* device, WCHAR** filename, int count)
{
	HRESULT result;
	m_ressources = (ID3D11ShaderResourceView**)realloc(m_ressources, count * sizeof(ID3D11ShaderResourceView*));

	for (int i = 0; i < count; i++) {
		std::shared_ptr<Texture> tex = std::make_shared<Texture>();
		result &= tex->InitializeDDS(device, filename[i]);
		m_textures.push_back(tex);
		m_ressources[i] = tex->GetTexture();
	}

	m_count = count;
	return result;
}

bool TextureArray::addTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, Texture::TextureType t_type)
{
	bool result = true;

	// Create the texture object.
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	if (!texture.get())
	{
		return false;
	}

	// Initialize the texture object
	if (t_type == Texture::TextureType::TGA) {
		result = texture->Initialize(device, deviceContext, filename);
	}

	else if (t_type == Texture::TextureType::DDS) {
		const size_t size = strlen(filename) + 1;
		wchar_t* wText = new wchar_t[size];
		mbstowcs(wText, filename, size);
		result = texture->InitializeDDS(device, wText);
	}

	if (result) {
		m_textures.push_back(texture);
		m_count++;
		m_ressources = (ID3D11ShaderResourceView**)realloc(m_ressources, m_count * sizeof(ID3D11ShaderResourceView*));
		for (int i = 0; i < m_count; i++) {
			m_ressources[i] = m_textures[i]->GetTexture();
		}
	}

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
		result.push_back(t->GetTexture());
	}
	return result;
}

ID3D11ShaderResourceView** TextureArray::getRessources()
{
	return m_ressources;
}

TextureArray::~TextureArray()
{
}
