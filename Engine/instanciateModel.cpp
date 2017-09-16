#include "stdafx.h"
#include "instanciateModel.h"


InstanciateModel::InstanciateModel()
{
	Model();
	m_instanceBuffer = 0;

}

InstanciateModel::InstanciateModel(char* file):
	Model(file)
{
	m_instanceBuffer = 0;
}

bool InstanciateModel::InitializeBuffers(ID3D11Device* device)
{
	HRESULT result;

	if (!Model::InitializeBuffers(device)) {
		return false;
	}

	InstanceType* instances;
	D3D11_BUFFER_DESC instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA instanceData;

	m_instanceCount = 4;
	// Create the instance array.
	instances = new InstanceType[m_instanceCount];
	if (!instances)
	{
		return false;
	}

	instances[0].position = XMFLOAT3(-1.5f, -1.5f, 5.0f);
	instances[1].position = XMFLOAT3(-1.5f, 1.5f, 5.0f);
	instances[2].position = XMFLOAT3(1.5f, -1.5f, 5.0f);
	instances[3].position = XMFLOAT3(1.5f, 1.5f, 5.0f);

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.
	delete instances;
	instances = 0;

	return true;
}

void InstanciateModel::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(VertexTextureType);
	strides[1] = sizeof(InstanceType);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}
void InstanciateModel::ShutdownBuffers()
{
	Model::ShutdownBuffers();
	// Release the instance buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}
}

int InstanciateModel::GetVertexCount()
{
	return m_vertexCount;
}


int InstanciateModel::GetInstanceCount()
{
	return m_instanceCount;
}

InstanciateModel::~InstanciateModel()
{
}
