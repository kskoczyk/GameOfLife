#include "Config.h"

Config::Config()
{
	load();
}

void Config::save()
{
	properties.put("map.cylindrical", cylindrical);
	properties.put("map.topBottom", topBottom);
	properties.put("history", history);
	write_info(configPath, properties);
}

void Config::load()
{
	read_info(configPath, properties);
	cylindrical = properties.get("map.cylindrical", false);
	topBottom = properties.get("map.topBottom", false);
	history = properties.get("history", false);
}

bool Config::isCylindrical()
{
	return cylindrical;
}

bool Config::isTopBottom()
{
	return topBottom;
}

bool Config::isHistory()
{
	return history;
}

void Config::setCylindrical(bool state)
{
	cylindrical = state;
}

void Config::setTopBottom(bool state)
{
	topBottom = state;
}

void Config::setHistory(bool state)
{
	history = state;
}
