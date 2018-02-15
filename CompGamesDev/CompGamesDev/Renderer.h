#pragma once

#include <nclgl\OGLRenderer.h>
#include <nclgl\Camera.h>
#include <nclgl\HeightMap.h>

class RendererO : public OGLRenderer
{
public:
	RendererO(Window &parent);
	virtual ~RendererO();

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:
	HeightMap* heightMap;
	Camera* camera;
	//Mesh* sphere;
};

