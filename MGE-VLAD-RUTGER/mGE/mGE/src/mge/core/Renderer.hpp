#ifndef RENDERER_H
#define RENDERER_H

class World;
class GameObject;
class Camera;

/**
 * Renderer implements a default single pass forward renderer.
 */
class Renderer
{
	public:
		Renderer();
		virtual ~Renderer();
		inline int getDrawCalls() const { return drawCalls; }
		inline int getTriangleCount() const { return currentlyRenderedTrianles; }
        //render whole world
        void render (World* pWorld);

        //render specific game object within the world (using world's light settings etc)
        void render (World* pWorld, GameObject* pGameObject, Camera* pCamera, bool pRecursive);

        //utility call
        void setClearColor (int pR, int pG, int pB);

private:
	int currentlyRenderedTrianles;
	int drawCalls;
};

#endif // RENDERER_H
