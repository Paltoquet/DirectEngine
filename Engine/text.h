#pragma once

#include "font.h"
#include "fontshader.h"
class Text
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};
public:
	Text();
	Text(const Text&);
	~Text();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, XMMATRIX);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, XMMATRIX, XMMATRIX);
	bool SetMousePosition(int, int, ID3D11DeviceContext*);
	bool display(const char* msg, ID3D11DeviceContext* deviceContext);

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*,const char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, XMMATRIX, XMMATRIX);

private:
	Font* m_Font;
	FontShader* m_FontShader;
	int m_screenWidth, m_screenHeight;
	XMMATRIX m_baseViewMatrix;
	SentenceType* m_sentence1;
	SentenceType* m_sentence2;
};

