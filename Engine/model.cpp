#include "stdafx.h"
#include "model.h"


Model::Model():
	m_textures()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_loader = MeshLoader("ressources/woman.obj");
	m_tesselate = false;
}

Model::Model(char* file)
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_loader = MeshLoader(file);
}

Model::Model(const Model& other)
{
	m_vertexBuffer = other.getVertexBuffer();
	m_indexBuffer = other.getIndexBuffer();
	m_Texture = other.getTextureWrapper();
}

bool Model::InitializeBuffers(ID3D11Device* device)
{
	//VertexType* vertices;
	VertexTextureType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_loader.loadMesh();
	m_vertexCount = m_loader.getNbVertices();
	m_indexCount  = m_loader.getNbVertices();

	// Set the number of vertices in the vertex array.
	//m_vertexCount = 4;

	// Set the number of indices in the index array.
	//m_indexCount = 4;

	// Create the vertex array.
	vertices = new VertexTextureType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	m_loader.loadMesh();
	MeshLoader::VertexTextureType* vertexArray = m_loader.getVertices();

	for (int i = 0; i < m_vertexCount; i++) {
		vertices[i].position = vertexArray[i].position;
		vertices[i].texture  = vertexArray[i].texture;
		vertices[i].normal   = vertexArray[i].normal;
		indices[i] = i;
	}

	/*
	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	//vertices[0].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
	vertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[1].position = XMFLOAT3(-1.0f, 1.0f, 0.0f);  // Top left.
	vertices[1].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	vertices[1].texture = XMFLOAT2(0.0f, 0.0f);
	vertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[2].position = XMFLOAT3(1.0f, 1.0f, 0.0f);  // top right.
	//vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	vertices[2].texture = XMFLOAT2(1.0f, 0.0f);
	vertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[3].position = XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[3].texture = XMFLOAT2(1.0f, 1.0f);
	vertices[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 3;  // Bottom right.
	indices[3] = 2;  // Bottom right.
	*/

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.ByteWidth = sizeof(VertexTextureType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	//stride = sizeof(VertexType);
	stride = sizeof(VertexTextureType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	if (m_tesselate) {
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
	}
	else{
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	}

	return;
}

ID3D11ShaderResourceView* Model::GetTexture() const
{
	return m_Texture->GetTexture();
}
ID3D11ShaderResourceView** Model::getTextures()
{
	return m_textures.getRessources();
}
void Model::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}
void Model::Render(ID3D11DeviceContext* device)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(device);

	return;
}

bool Model::Initialize(ID3D11Device* device)
{
	bool result;


	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

bool Model::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, Texture::TextureType t_type)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}
	// Load the texture for this model.
	result = LoadTexture(device, deviceContext, textureFilename, t_type);
	if (!result)
	{
		return false;
	}

	return true;
}

bool Model::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, Texture::TextureType t_type)
{
	bool result = true;

	// Create the texture object.
	m_Texture = new Texture();
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object
	if (t_type == Texture::TextureType::TGA) {
		result = m_Texture->Initialize(device, deviceContext, filename);
	}
	
	else if (t_type == Texture::TextureType::DDS) {
		const size_t size = strlen(filename) + 1;
		wchar_t* wText = new wchar_t[size];
		mbstowcs(wText, filename, size);
		result = m_Texture->InitializeDDS(device, wText);
	}
	
	return result;
}

void Model::setTesselate(bool shouldTesselate)
{
	m_tesselate = shouldTesselate;
}

void Model::addTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, Texture::TextureType t_type)
{
	m_textures.addTexture(device, deviceContext, filename, t_type);
}

ID3D11Buffer* Model::getVertexBuffer() const
{
	return m_vertexBuffer;
}

ID3D11Buffer* Model::getIndexBuffer() const 
{
	return m_indexBuffer;
}

Texture* Model::getTextureWrapper() const
{
	return m_Texture;
}

void Model::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
	
	m_textures.Shutdown();
	return;
}

void Model::Shutdown()
{
	// Release the vertex and index buffers.
	ReleaseTexture();
	ShutdownBuffers();

	return;
}

int Model::GetIndexCount()
{
	return m_indexCount;
}


Model::~Model()

{
}