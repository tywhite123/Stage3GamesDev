#include <nclgl\OGLRenderer.h>
#include <nclgl\Camera.h>
#include "RenderObject.h"
#include <vector>
#include <map>
#include <Common\GameObject.h>
#include <GLText\gltext.h>

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

	//Add/get objects from the stores
	void AddRenderObject(RenderObject &r) {
		renderObjects.push_back(&r);
	}

	void AddObject(GameObject &g, RenderObject &r) {
		obj.insert(pair<GameObject*, RenderObject*>(&g, &r));
	}

	map<GameObject*, RenderObject*> getObjects() {
		return obj;
	}

	vector<RenderObject*> getRenderObj() {
		return renderObjects;
	}


	//Setting up view and model matrix
	void SetProjMatrix(Matrix4 m) { projMatrix = m; }
	Matrix4 GetProjMatrix() { return projMatrix; }

	void SetViewMatrix(Matrix4 m) { viewMatrix = m; }
	Matrix4 GetViewMatrix() { return viewMatrix; }


	void removeRenderObj(GameObject* o) {
		for (int i = 0; i < renderObjects.size(); ++i) {
			if (renderObjects.at(i) == obj.at(o)) {
				renderObjects.erase(renderObjects.begin() + i);
			}
		}
		obj.erase(o);
	}

protected:
	vector<RenderObject*> renderObjects;
	map<GameObject*, RenderObject*> obj;

	GLTtext *playerHealth;
	GLTtext *enemyHealth;
};

