#include "AbstractGame.hpp"

#include <iostream>
using namespace std;

#include "mge/core/Timer.hpp"
#include "mge/core/FPS.hpp"
#include "mge/core/Renderer.hpp"
//#include "mge/core/World.hpp"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/events/EventDispatcher.h"

AbstractGame::AbstractGame():_window(NULL),_renderer(NULL),_world(NULL),_running(false)
{
    //ctor
}

AbstractGame::~AbstractGame()
{
    //dtor
    delete _window;
    delete _renderer;
    delete _world;
}

void AbstractGame::initialize() {
    cout << "Initializing engine..." << endl << endl;
    _initializeWindow();
    _printVersionInfo();
    _initializeGlew();
    _initializeRenderer();
    _initializePhysiscs();
    _initializeWorld();

    _initializeScene();

    cout << endl << "Engine initialized." << endl << endl;
}

///SETUP

void AbstractGame::_initializeWindow() {
	cout << "Initializing window..." << endl;
	_window = new sf::RenderWindow( sf::VideoMode(1366,768), "My Game!", sf::Style::Fullscreen, sf::ContextSettings(24,8,0,3,3));
	_window->setVerticalSyncEnabled(false);
    cout << "Window initialized." << endl << endl;
}

void AbstractGame::_printVersionInfo() {
	cout << "Context info:" << endl;
    cout << "----------------------------------" << endl;
    //print some debug stats for whoever cares
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    cout << "----------------------------------" << endl << endl;
}

void AbstractGame::_initializeGlew() {
	cout << "Initializing GLEW..." << endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
	cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << endl << endl;
}

void AbstractGame::_initializeRenderer() {
    //setup our own renderer
	cout << "Initializing renderer..." << endl;
	_renderer = new Renderer();
    cout << "Renderer done." << endl << endl;
}

void AbstractGame::_initializeWorld() {
    //setup our own world
	cout << "Initializing world..." << endl;
	_world = new PhysicsWorld(2000, 20);

    cout << "Physics World initialized." << endl << endl;
}

void AbstractGame::_initializePhysiscs() {
 //   //setup our own physics manaer
	//cout << "Initializing physics..." << endl;
	//_collisionManager = new CollisionManager();
 //   cout << "Physics initialized." << endl << endl;
}

///LOOP

void AbstractGame::run()
{
	_running = true;

	float accumulatedTime = 0.0f;
	float lastTime = clock();

	int count = 0;

	while (_running) {

		float currentTime = clock();
		float deltaTime = currentTime - lastTime;
		accumulatedTime += deltaTime;

		while (accumulatedTime > 5.0f) {
			_fixedUpdate();
			accumulatedTime -= 5.0f;
			//count++;
		}

		lastTime = currentTime;

	/*	if (count == 50) {
			cout << "dsad" << endl;
			count = 0;
		}*/

		Timer::update();
		FPS::update();

	    //clear frame, do it here so we can draw debug stuff in any other step etc
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		clock_t startUpdate;
		startUpdate = clock();
	
        _update();

		updateTime = (std::clock() - startUpdate) / (double)(CLOCKS_PER_SEC / 1000);

		clock_t startRender;
		startRender = clock();

        _render();

		renderTime = (std::clock() - startRender) / (double)(CLOCKS_PER_SEC / 1000);
		drawCalls = _renderer->getDrawCalls();
		triangleCount = _renderer->getTriangleCount();
        //swap colorbuffer to screen
        _window->display();

		_processEvents();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
			cout << "TIME NEEDED TO UPDATE -> " << updateTime << endl;
			cout << "TIME NEEDED TO RENDER -> " << renderTime << endl;
		}
	}
}

void AbstractGame::_update()
{
    _world->update(Timer::deltaTime(), glm::mat4());
}

void AbstractGame::_fixedUpdate() {
	_world->fixedUpdate();
}

void AbstractGame::_render ()
{
    _renderer->render(_world);
}




void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you...
        //SystemEventDispatcher::dispatchEvent(event);
		//EventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
         /*       if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }*/
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
	}

	if (exit) {
		_world->CleanUpPhysicsWorld();
        _window->close();
        _running = false;
	}
}



