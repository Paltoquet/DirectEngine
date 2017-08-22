#ifndef _FRUSTUMCLASS_H_
#define _FRUSTUMCLASS_H_



#define _XM_NO_INTRINSICS_//must before #include <DirectXMath.h>

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class Frustum
{
public:
	Frustum();
	Frustum(const Frustum&);
	~Frustum();

	void ConstructFrustum(float, XMMATRIX, XMMATRIX);

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);

private:
	XMFLOAT4 m_planes[6];
};

#endif

