#include <nclgl\OGLRenderer.h>
#include <nclgl\Camera.h>
#include "RenderObject.h"
#include <vector>
#include <map>
#include <Common\GameObject.h>

using namespace std;

#pragma once
class Renderer : public OGLRenderer
{
public:
	Renderer(Window &parent);
	virtual ~Renderer();

	virtual void RenderScene();

	virtual void Render(const RenderObject &o);

	virtual void UpdateScene(float msec);

	void AddRenderObject(RenderObject &r) {
		renderObjects.push_back(&r);
	}

	void AddObject(RenderObject &r, GameObject &g) {
		obj.insert(pair<RenderObject*, GameObject*>(&r, &g));
	}

	map<RenderObject*, GameObject*> getObjects() {
		return obj;
	}

	vector<RenderObject*> getRenderObj() {
		return renderObjects;
	}

	void SetProjMatrix(Matrix4 m) { projMatrix = m; }
	Matrix4 GetProjMatrix() { return projMatrix; }

	void SetViewMatrix(Matrix4 m) { viewMatrix = m; }
	Matrix4 GetViewMatrix() { return viewMatrix; }

protected:
	vector<RenderObject*> renderObjects;
	map<RenderObject*, GameObject*> obj;
};

