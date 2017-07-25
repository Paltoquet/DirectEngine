#include "stdafx.h"
#include "meshLoader.h"
#include "loger.h"

#include <direct.h>

using namespace std;

struct VertexTextureType
{
	XMFLOAT3 position;
	XMFLOAT2 texture;
	XMFLOAT3 normal;
};


MeshLoader::MeshLoader()
{

}
MeshLoader::MeshLoader(string filename):
	m_filename(filename)
{
	m_parserLoger = "test.txt";
}

MeshLoader::VertexTextureType* MeshLoader::getVertices(){
	VertexTextureType* ptr = &m_vertices[0];
	return ptr;
}

int MeshLoader::getNbFaces() {
	return m_faces.size();
}

int MeshLoader::getNbVertices() {
	return m_vertices.size();
}

bool MeshLoader::loadMesh()
{
	ifstream fin;
	ofstream fout;
	char input, input2;
	float t1, t2, t3;

	fout.open(m_parserLoger);	

	fin.open(m_filename);
	//fout.close();
	if(fin.is_open() == false || fout.is_open() == false)
	{
		return false;
	}
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// Read in the vertices.
			if (input == ' ')
			{
				fin >> t1 >> t2 >> t3;
				fout << t1 << "," << t2 << "," << t3 << endl;
				//change z coordonnate
				t3 = -1 * t3;
				m_position.push_back(XMFLOAT3(t1, t2, t3));
			}
			if (input == 'n')
			{
				float t1, t2, t3;
				fin >> t1 >> t2 >> t3;
				fout << t1 << "," << t2 << "," << t3 << endl;
				//change z coordonnate
				t3 = -1 * t3;
				m_normal.push_back(XMFLOAT3(t1, t2, t3));
			}
			if (input == 't')
			{
				float t1, t2, t3;
				fin >> t1 >> t2;
				fout << t1 << "," << t2 << endl;
				//change y coordonate
				t2 = 1 - t2;
				m_texture.push_back(XMFLOAT2(t1, t2));
			}

			while (input != '\n')
			{
				fin.get(input);
			}
		}

		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				FaceType face;
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				fin >> face.vIndex3 >> input2 >> face.tIndex3 >> input2 >> face.nIndex3
					>> face.vIndex2 >> input2 >> face.tIndex2 >> input2 >> face.nIndex2
					>> face.vIndex1 >> input2 >> face.tIndex1 >> input2 >> face.nIndex1;

				face.vIndex3  = face.vIndex3 - 1;
				face.vIndex2  = face.vIndex2 - 1;
				face.vIndex1  = face.vIndex1 - 1;
				face.nIndex3  = face.nIndex3 - 1;
				face.nIndex2  = face.nIndex2 - 1;
				face.nIndex1  = face.nIndex1 - 1;
				face.tIndex3  = face.tIndex3 - 1;
				face.tIndex2  = face.tIndex2 - 1;
				face.tIndex1  = face.tIndex1 - 1;

				fout << face.vIndex3 << input2 << face.tIndex3 << input2 << face.nIndex3 << " "
					 << face.vIndex2 << input2 << face.tIndex2 << input2 << face.nIndex2 << " "
					 << face.vIndex1 << input2 << face.tIndex1 << input2 << face.nIndex1 << endl;

				m_faces.push_back(face);
			}
		}
		fin.get(input);
	}
	fout << m_position.size() << " " << m_normal.size() << " " << m_texture.size() << m_faces.size();
	fout << flush;
	fout.close();
	fin.close();
	loadDataStructure();
	return true;
}

void MeshLoader::loadDataStructure() {
	int nb_faces = m_faces.size();
	for (int i = 0; i < nb_faces; i++) {
		VertexTextureType vertex;
		VertexTextureType vertex2;
		VertexTextureType vertex3;
		vertex.position	 = m_position[m_faces[i].vIndex1];
		vertex2.position = m_position[m_faces[i].vIndex2];
		vertex3.position = m_position[m_faces[i].vIndex3];
		vertex.normal	 = m_normal[m_faces[i].nIndex1];
		vertex2.normal	 = m_normal[m_faces[i].nIndex2];
		vertex3.normal	 = m_normal[m_faces[i].nIndex3];
		vertex.texture   = m_texture[m_faces[i].tIndex1];
		vertex2.texture  = m_texture[m_faces[i].tIndex2];
		vertex3.texture  = m_texture[m_faces[i].tIndex3];
		m_vertices.push_back(vertex);
		m_vertices.push_back(vertex2);
		m_vertices.push_back(vertex3);
	}
}

MeshLoader::~MeshLoader()
{
}
