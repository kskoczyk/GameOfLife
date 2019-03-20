#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "Cell.h"
#include "Config.h"

using namespace std;

namespace gameMap
{
	void iterate(Config config);
	void init(bool &&random = false);
	void print(bool toFile = false);
	void create();
}
