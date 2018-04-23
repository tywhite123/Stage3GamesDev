#pragma once
#pragma once
#include "OGLRenderer.h"

enum MeshBuffer
{
	VERTEX_BUFFER, COLOUR_BUFFER, TEXTURE_BUFFER, INDEX_BUFFER, MAX_BUFFER
};


class Mesh
{
public:
	Mesh();
	~Mesh();

	virtual void Draw();
	static Mesh* GenerateTriangle();
	static Mesh* GenerateQuad();
	static Mesh* GenerateSquare(Vector4 colour);
	static Mesh* GenerateSphere();

	void SetTexture(GLuint tex) { texture = tex; }
	GLuint GetTexture() { return texture; }

protected:
	void BufferData();

	GLuint arrayObject;
	GLuint bufferObject[MAX_BUFFER];
	GLuint numVertices;
	GLuint type;

	GLuint numIndices;
	unsigned int* indices;

	Vector3* vertices;
	Vector4* colours;

	GLuint texture;
	Vector2* textureCoords;
};

