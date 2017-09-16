#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "d3dclass.h"
#include "camera.h"
#include "model.h"
#include "triangle.h"
#include "bitmapmodel.h"
#include "shader.h"
#include "textureshader.h"
#include "modelList.h"
#include "frustrum.h"

#include "lightshader.h"
#include "tesselateShader.h"
#include "textureAndColorShader.h"
#include "particleSystem.h"
#include "light.h"

#include "MultiTextureShader.h"
#include "clipplaneshader.h"
#include "renderTexture.h"
#include "text.h"




/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int mouseX, int mouseY);

private:
	D3DClass* m_Direct3D;
	Camera* m_Camera;
	Frustum* m_Frustum;
	ModelList* m_ModelList;
	Model* m_Model;
	Model* m_MultiTextureModel;
	Triangle* m_Triangle;
	BitmapModel* m_Bitmap;
	Shader* m_ColorShader;
	TextureShader* m_TextureShader;
	LightShader* m_LightShader;

	TesselateShader* m_TesselateShader;
	TextureAndColorShader* m_TextureAndColorShader;

	ParticleSystem* m_ParticleSystem;

	Light* m_Light;
	Text* m_Text;
	RenderTexture* m_RenderTexture;
	Shader* m_test;


	bool Render(float rot = 0);
	bool RenderToTexture(float rot = 0);
};

#endif