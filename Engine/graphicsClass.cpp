#include "stdafx.h"
#include "graphicsClass.h"
#include <string>


GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Frustum = 0;
	m_ModelList = 0;
	m_Model = 0;
	m_Triangle = 0;
	m_MultiTextureModel = 0;
	m_Bitmap = 0;
	m_ColorShader = 0;
	m_TesselateShader = 0;
	m_ParticleSystem = 0;
	m_ParticleSystem = 0;
	m_TextureShader = 0;
	m_RenderTexture = 0;
	m_test = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	XMMATRIX baseViewMatrix;
	bool result;


	// Create the Direct3D object.
	m_Direct3D = new D3DClass();
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera();
	if (!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new Text();
	if (!m_Text)
	{
		return false;
	}
	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 1.5f, -1.0f);
	//m_Camera->SetPosition(0.0f, 0.0f, -5.0f);
	// Create the model object.
	m_Model = new Model();
	if (!m_Model)
	{
		return false;
	}

	//result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/images/stone.tga", Model::TextureType::DDS);
	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/images/floor.DDS", Texture::TextureType::DDS);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_MultiTextureModel = new Model(*m_Model);
	/*m_MultiTextureModel = new Model();
	if (!m_Model)
	{
		return false;
	}

	//result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/images/stone.tga", Model::TextureType::DDS);
	result = m_MultiTextureModel->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/images/floor.DDS", Texture::TextureType::DDS);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	*/
	m_MultiTextureModel->addTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/images/stone01.DDS", Texture::TextureType::DDS);
	m_MultiTextureModel->addTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/images/dirt01.DDS", Texture::TextureType::DDS);

	// Create the bitmap object.
	m_Bitmap = new BitmapModel();
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, "data/images/stone.tga", 50, 50);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	m_Light = new Light();
	if (!m_Light)
	{
		return false;
	}

	m_LightShader = new LightShader();
	if (!m_LightShader)
	{
		return false;
	}
	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	m_TesselateShader = new TesselateShader();
	if (!m_TesselateShader)
	{
		return false;
	}

	result = m_TesselateShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the particle shader object.
	m_TextureAndColorShader = new TextureAndColorShader();
	if (!m_TextureAndColorShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_TextureAndColorShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystem();
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_Direct3D->GetDevice(), L"data/images/star.DDS");
	if (!result)
	{
		return false;
	}

	m_Triangle = new Triangle();
	if (!m_Triangle)
	{
		return false;
	}

	//result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/images/stone.tga", Model::TextureType::DDS);
	result = m_Triangle->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	//Initialize the light shader object.
	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	//m_test = new MultiTextureShader();
	m_test = new ClipPlaneShader();
	if (!m_test)
	{
		return false;
	}

	// Initialize the multitexture shader object.
	result = ((ClipPlaneShader*)m_test)->Initialize(m_Direct3D->GetDevice(), hwnd);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
		return false;
	}

	
	// Create the texture shader object.
	m_TextureShader = new TextureShader();
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the render to texture object.
	m_RenderTexture = new RenderTexture();
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	m_ModelList = new ModelList();
	if (!m_ModelList)
	{
		return false;
	}

	// Initialize the model list object.
	result = m_ModelList->Initialize(25);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
		return false;
	}
	m_Frustum = new Frustum();
	if (!m_Frustum)
	{
		return false;
	}

	return true;

	/*
	// Initialize the model object.
	result = m_Model->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	return false;
	}
	
	// Create the color shader object.
	m_ColorShader = new Shader();
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}
	*/

	return true;
}

bool GraphicsClass::Frame(int mouseX, int mouseY)
{
	bool result;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.1f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Run the frame processing for the particle system.
	m_ParticleSystem->Frame(0.33, m_Direct3D->GetDeviceContext());

	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -3.0f);

	// Render the graphics scene.
	result = RenderToTexture(rotation);
	if (!result)
	{
		return false;
	}
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	m_Direct3D->EndScene();
	return true;
}


bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	int modelCount, renderCount, index;
	float positionX, positionY, positionZ, radius;
	XMFLOAT4 color, pos;
	XMVECTOR transformed;
	bool renderModel, result;

	XMFLOAT4 clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.5f);


	// Clear the buffers to begin the scene.

	m_Direct3D->BeginScene(0.f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);
	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();
	// Initialize the count of models that have been rendered.
	renderCount = 0;


	XMMATRIX rot = DirectX::XMMatrixRotationY(XMConvertToRadians(rotation));
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.

	m_Model->Render(m_Direct3D->GetDeviceContext());

	for (index = 0; index < modelCount; index++)
	{
		// Get the position and color of the sphere model at this index.
		m_ModelList->GetData(index, positionX, positionY, positionZ, color);
		// Set the radius of the sphere to 1.0 since this is already known.
		radius = 1.0f;


		//XMMATRIX translation = DirectX::XMMatrixTranslation(positionX, positionY, positionZ);
		pos = XMFLOAT4(positionX, positionY, positionZ, 1);
		transformed = XMLoadFloat4(&pos);
		transformed = XMVector4Transform(transformed,  viewMatrix * rot);
		XMStoreFloat4(&pos, transformed);

		// Check if the sphere model is in the view frustum.
		//renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ, radius);
		renderModel = m_Frustum->CheckSphere(pos.x, pos.y, pos.z, radius);
		// If it can be seen then render it, if not skip this model and check the next sphere.
		if (renderModel)
		{
			// Move the model to the location it should be rendered at.

			XMMATRIX translation = DirectX::XMMatrixTranslation(positionX, positionY, positionZ);
			//D3DXMatrixTranslation(&worldMatrix, positionX, positionY, positionZ);
			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			//m_Model->Render(m_Direct3D->GetDeviceContext());

			// Render the model using the light shader.
			result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix * rot * translation, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), color, m_Camera->GetPosition(),
				m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
				
			
			// Reset to the original world matrix.
			m_Direct3D->GetWorldMatrix(worldMatrix);

			// Since this model was rendered then increase the count for this frame.
			renderCount++;
		}
	}

	/*m_Triangle->Render(m_Direct3D->GetDeviceContext());

	m_TesselateShader->Render(m_Direct3D->GetDeviceContext(), m_Triangle->GetIndexCount(),  worldMatrix, viewMatrix, projectionMatrix, 3.0f);*/

	m_Model->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the color shader.

	result = ((ClipPlaneShader*)m_test)->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), rot * worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(),
		clipPlane);

	result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, rot * viewMatrix, projectionMatrix, m_Model->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	//m_MultiTextureModel->Render(m_Direct3D->GetDeviceContext());
	//result = (m_test->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		//m_MultiTextureModel->getTextures());

	if (!result)
	{
		return false;
	}
	m_Direct3D->TurnOnAlphaBlending();

	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_TextureAndColorShader->Render(m_Direct3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ParticleSystem->GetTexture());
	if (!result)
	{
		return false;
	}

	m_Direct3D->TurnOffAlphaBlending();

	m_Direct3D->TurnZBufferOff();
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_Direct3D->GetDeviceContext(), 100, 100);
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_RenderTexture->GetShaderResourceView());
	//m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());

	m_Direct3D->TurnOnAlphaBlending();
	
	string msg = "Object number: " + std::to_string(renderCount);
	m_Text->display(msg.c_str(), m_Direct3D->GetDeviceContext());
	// Render the text strings.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	m_Direct3D->TurnOffAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	//m_Direct3D->EndScene();
	return true;
}

bool GraphicsClass::RenderToTexture(float rotation)
{
	bool result  = true;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext(), m_Direct3D->GetDepthStencilView());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), m_Direct3D->GetDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

	return true;
}

void GraphicsClass::Shutdown()
{

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	if (m_test)
	{
		m_test->Shutdown();
		delete m_test;
		m_test = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if (m_TesselateShader)
	{
		m_TesselateShader->Shutdown();
		delete m_TesselateShader;
		m_TesselateShader = 0;
	}

	// Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if (m_TextureAndColorShader)
	{
		m_TextureAndColorShader->Shutdown();
		delete m_TextureAndColorShader;
		m_TextureAndColorShader = 0;
	}

	if (m_Triangle)
	{
		m_Triangle->Shutdown();
		delete m_Triangle;
		m_Triangle = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the model list object.
	if (m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
	return;
}