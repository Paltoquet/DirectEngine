#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "d3dclass.h"
#include "camera.h"
#include "model.h"
#include "bitmapmodel.h"
#include "shader.h"
#include "textureshader.h"

#include "lightshader.h"
#include "light.h"

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
	bool Frame();

private:
	D3DClass* m_Direct3D;
	Camera* m_Camera;
	Model* m_Model;
	BitmapModel* m_Bitmap;
	Shader* m_ColorShader;
	TextureShader* m_TextureShader;
	LightShader* m_LightShader;
	Light* m_Light;
	Text* m_Text;

	bool Render(float rot = 0);

};

#endif