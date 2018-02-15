#include <nclgl\Window.h>
#include "Renderer.h"
#include "..\Renderer\Graphics.h"

/*int main() {
	Window w("Test", 800, 600);


}*/

int main() {
	Window w("Index Buffers!", 800, 600, false);
	if (!w.HasInitialised()) {
		return -1;
	}

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	Graphics graphics(w, renderer);

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		renderer.UpdateScene(w.GetTimer()->GetTimedMS());
		renderer.RenderScene();
	}
	return 0;
}