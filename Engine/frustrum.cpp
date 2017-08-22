#include "stdafx.h"
#include "frustrum.h"

//http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/

Frustum::Frustum()
{
}


Frustum::Frustum(const Frustum& other)
{
}


Frustum::~Frustum()
{
}


float planeDotProduct(XMFLOAT4* plane, float x, float y, float z)
{
	int i;
	float val;
	XMVECTOR v, tmp, r;

	v = XMLoadFloat4(&XMFLOAT4(x, y, z, 1));
	tmp = XMLoadFloat4(plane);
	r = XMVector4Dot(tmp, v);
	XMStoreFloat(&val, r);
	return val;
}

void Frustum::ConstructFrustum(float screenDepth, XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	float zMinimum, r;
	XMMATRIX matrix;
	XMVECTOR n;
	float l;
	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix._43 / projectionMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r * zMinimum;


	// Create the frustum matrix from the view matrix and updated projection matrix.
	matrix = XMMatrixMultiply(viewMatrix, projectionMatrix);

	// Calculate near plane of frustum.
	/*
	m_planes[0].x = (matrix._14 + matrix._13) / l;
	m_planes[0].y = (matrix._24 + matrix._23) / l;
	m_planes[0].z = (matrix._34 + matrix._33) / l;
	m_planes[0].w = (matrix._44 + matrix._43) / l;
	//D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);
	*/

	n = XMLoadFloat4(&XMFLOAT4(matrix._14 + matrix._13, matrix._24 + matrix._23, matrix._34 + matrix._33, matrix._44 + matrix._43));
	XMStoreFloat4(&m_planes[0], XMVector4Length(n));

	// Calculate far plane of frustum.
	n = XMLoadFloat4(&XMFLOAT4(matrix._14 - matrix._13, matrix._24 - matrix._23, matrix._34 - matrix._33, matrix._44 - matrix._43));
	XMStoreFloat4(&m_planes[1], XMVector4Length(n));

	// Calculate left plane of frustum.
	n = XMLoadFloat4(&XMFLOAT4(matrix._14 + matrix._11, matrix._24 + matrix._21, matrix._34 + matrix._31, matrix._44 + matrix._41));
	XMStoreFloat4(&m_planes[2], XMVector4Length(n));

	// Calculate right plane of frustum.
	n = XMLoadFloat4(&XMFLOAT4(matrix._14 - matrix._11, matrix._24 - matrix._21, matrix._34 - matrix._31, matrix._44 - matrix._41));
	XMStoreFloat4(&m_planes[3], XMVector4Length(n));

	// Calculate top plane of frustum.
	n = XMLoadFloat4(&XMFLOAT4(matrix._14 + matrix._12, matrix._24 + matrix._22, matrix._34 + matrix._32, matrix._44 + matrix._42));
	XMStoreFloat4(&m_planes[4], XMVector4Length(n));


	// Calculate bottom plane of frustum.
	n = XMLoadFloat4(&XMFLOAT4(matrix._14 - matrix._12, matrix._24 - matrix._22, matrix._34 - matrix._32, matrix._44 - matrix._42));
	XMStoreFloat4(&m_planes[5], XMVector4Length(n));

	return;
}

bool Frustum::CheckPoint(float x, float y, float z)
{
	int i;
	float val;
	XMVECTOR v, tmp, r;

	v = XMLoadFloat4(&XMFLOAT4(x, y, z, 1));

	// Check if the point is inside all six planes of the view frustum.
	for (i = 0; i<6; i++)
	{
		tmp = XMLoadFloat4(&m_planes[i]);
		r = XMVector4Dot(tmp, v);
		XMStoreFloat(&val, r);
		if(val < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i<6; i++)
	{
		if (planeDotProduct(&m_planes[i],(xCenter - radius), (yCenter - radius), (zCenter - radius)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + radius), (yCenter - radius), (zCenter - radius)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter - radius), (yCenter + radius), (zCenter - radius)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + radius), (yCenter + radius), (zCenter - radius)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter - radius), (yCenter - radius), (zCenter + radius)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + radius), (yCenter - radius), (zCenter + radius)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter - radius), (yCenter + radius), (zCenter + radius)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + radius), (yCenter + radius), (zCenter + radius)) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool Frustum::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i<6; i++)
	{
		//compute distance http://www.lighthouse3d.com/tutorials/maths/plane/ from a point to the plane
		float d = planeDotProduct(&m_planes[i], xCenter, yCenter, zCenter);
		float p = radius;
		bool r = d < -radius;
		if (d < -radius)
		{
			int l = i;
			return false;
		}
	}

	return true;
}

bool Frustum::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;


	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i<6; i++)
	{
		if (planeDotProduct(&m_planes[i],(xCenter - xSize), (yCenter - ySize), (zCenter - zSize)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + xSize), (yCenter - ySize), (zCenter - zSize)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter - xSize), (yCenter + ySize), (zCenter - zSize)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter - xSize), (yCenter - ySize), (zCenter + zSize)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + xSize), (yCenter + ySize), (zCenter - zSize)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + xSize), (yCenter - ySize), (zCenter + zSize)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter - xSize), (yCenter + ySize), (zCenter + zSize)) >= 0.0f)
		{
			continue;
		}

		if (planeDotProduct(&m_planes[i],(xCenter + xSize), (yCenter + ySize), (zCenter + zSize)) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}