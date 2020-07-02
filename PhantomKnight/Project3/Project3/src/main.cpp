

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib")
#pragma comment(lib,"thor-d.lib") 
#pragma comment(lib,"libyaml-cppmdd.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"thor.lib") 
#pragma comment(lib,"openGL32.lib")
#pragma comment(lib,"libyaml-cppmd.lib")


#endif 

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")



/// <summary>
/// main enrtry point
/// </summary>
/// <returns>zero</returns>
#include "game.h"

int main()
{
	GameData data;
	LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", data);

	Game aGame(data);
	aGame.run();

}