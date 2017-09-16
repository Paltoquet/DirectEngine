#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <directxmath.h>
#include "meshLoader.h"

#include "texture.h"
#include "textureArray.h"

using namespace DirectX;

class Model
{

public:
	struct VertexTextureType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	bool m_tesselate;
	Texture* m_Texture;
	TextureArray m_textures;
	MeshLoader m_loader;

public:
	Model();
	Model(char* file);
	Model(const Model&);
	~Model();
	bool Initialize(ID3D11Device*);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, Texture::TextureType t_type = Texture::TextureType::TGA);
	void addTexture(ID3D11Device*, ID3D11DeviceContext*, char*, Texture::TextureType t_type = Texture::TextureType::TGA);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void setTesselate(bool);

	int GetIndexCount();
	Texture* getTextureWrapper() const;
	ID3D11ShaderResourceView* GetTexture() const;
	ID3D11ShaderResourceView** getTextures();
	ID3D11Buffer* getVertexBuffer() const;
	ID3D11Buffer* getIndexBuffer() const;

protected:
	virtual bool InitializeBuffers(ID3D11Device*);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext*);
	virtual bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*, Texture::TextureType t_type = Texture::TextureType::TGA);
	virtual void ReleaseTexture();
};

#endif

