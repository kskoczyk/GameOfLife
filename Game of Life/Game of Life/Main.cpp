// TODO:
// shared pointers for map
// handle non-existing config file
//done? handle non-existing history/map file
//?? randomize map?
//?? non-square map?

#include <iostream>
#include <vector>
#include <Windows.h>

#include <boost/thread.hpp>

#include "Cell.h"
#include "GameMap.h"
#include "UI.h"
#include "Config.h"

using namespace std;

int main()
{	
	// game::run()

	Config config;
	config.save();
	gameMap::init();

	boost::thread t1([]{});
	for ( ; ; )
	{
		gameMap::print(config.isHistory());
		gameMap::iterate(config);

		UI::waitForInput(t1, boost::chrono::milliseconds(300), config);
	}

	system("pause");
	return 0;
}