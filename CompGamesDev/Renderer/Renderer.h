#include <nclgl\OGLRenderer.h>
#include <nclgl\Camera.h>

#pragma once
class Renderer : public OGLRenderer
{
public:
	Renderer(Window &parent);
	virtual ~Renderer();

	virtual void RenderScene();
	virtual void UpdateScene(float msec);

protected:


};

