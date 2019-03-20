#include "GameMap.h"

namespace gameMap
{
	vector< vector<Cell>> prev;
	vector< vector<Cell>> current;
	string mapPath = "Map.txt"; // same directory as solution
	string historyPath = "Map_history.txt";
}

void gameMap::iterate(Config config)
{
	for (int i = 0; i < prev.size(); i++)
	{
		for (int j = 0; j < prev[i].size(); j++)
		{
			// COUNT
			int aliveCount = 0;

			if (i - 1 >= 0)
			{
				if (j - 1 >= 0)
				{
					if (prev[i - 1][j - 1].getState()) aliveCount++;
					if (prev[i][j - 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[i - 1][prev[i - 1].size() - 1].getState()) aliveCount++;
					if (prev[i][prev[i].size() - 1].getState()) aliveCount++;
				}
				if (prev[i - 1][j].getState()) aliveCount++;
				if (j + 1 <= prev[i].size() - 1)
				{
					if (prev[i - 1][j + 1].getState()) aliveCount++;
					if (prev[i][j + 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[i - 1][0].getState()) aliveCount++;
					if (prev[i][0].getState()) aliveCount++;
				}
			}
			else if (config.isTopBottom())
			{
				if (j - 1 >= 0)
				{
					if (prev[prev.size() - 1][j - 1].getState()) aliveCount++;
					if (prev[i][j - 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[prev.size() - 1][prev[prev.size() - 1].size() - 1].getState()) aliveCount++;
					if (prev[i][prev[i].size() - 1].getState()) aliveCount++;
				}
				if (prev[prev.size() - 1][j].getState()) aliveCount++;
				if (j + 1 <= prev[i].size() - 1)
				{
					if (prev[prev.size() - 1][j + 1].getState()) aliveCount++;
					if (prev[i][j + 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[prev.size() - 1][0].getState()) aliveCount++;
					if (prev[i][0].getState()) aliveCount++;
				}
			}

			if (i + 1 <= prev.size() - 1)
			{
				if (j - 1 >= 0)
				{
					if (prev[i + 1][j - 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[i + 1][prev[i + 1].size() - 1].getState()) aliveCount++;
				}
				if (prev[i + 1][j].getState()) aliveCount++;
				if (j + 1 <= prev[i].size() - 1)
				{
					if (prev[i + 1][j + 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[i + 1][0].getState()) aliveCount++;
				}
			}
			else if (config.isTopBottom())
			{
				if (j - 1 >= 0)
				{
					if (prev[0][j - 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[0][prev[0].size() - 1].getState()) aliveCount++;
				}
				if (prev[0][j].getState()) aliveCount++;
				if (j + 1 <= prev[i].size() - 1)
				{
					if (prev[0][j + 1].getState()) aliveCount++;
				}
				else if (config.isCylindrical())
				{
					if (prev[0][0].getState()) aliveCount++;
				}
			}

			// STATE
			if (prev[i][j].getState())
			{
				if (aliveCount < 2)	current[i][j].setState(false);
				else if(aliveCount > 3) current[i][j].setState(false);
				// else still alive
			}
			else
			{
				if (aliveCount == 3) current[i][j].setState(true);
			}
		}
	}

	prev = current;
}

void gameMap::init(bool &&random)
{
	ofstream history(historyPath, ios::trunc);
	if (random)
	{
		// TBA
	}
	else
	{
		string line;
		ifstream map(mapPath);
		if (map)
		{
			while (getline(map, line))
			{
				current.push_back(vector<Cell>());
				auto end_pos = remove(line.begin(), line.end(), ' '); // std::string::iterator
				line.erase(end_pos, line.end());
				for (int i = 0; i < line.size(); i++)
				{
					// consider using boost:lexical<cast>
					if (line[i] == '0')
					{
						current[current.size() - 1].push_back(Cell(false));
					}
					else
					{
						current[current.size() - 1].push_back(Cell(true));
					}
				}
			}
			copy(current.begin(), current.end(), back_inserter(prev));
		}
		map.close();
	}
}

void gameMap::print(bool toFile)
{
	string visualize = "";
	stringstream ss;
	for (int i = 0; i < current.size(); i++)
	{
		for (int j = 0; j < current[i].size(); j++)
		{
			ss << current[i][j].getState() << " ";
		}
		ss << endl;
	}
	ss << endl;
	visualize = ss.str();
	cout << visualize;

	if (toFile)
	{
		ofstream history(historyPath, ios::app);
		if (history)
		{
			history << visualize;
		}
		else
		{
			cerr << "Could not open/create the history file.";
		}
		history.close();
	}
}

void gameMap::create()
{
	cout << "User-created new map" << endl;
	cout << "Set number of rows" << endl;
	int rows;
	cin >> rows;
	if (rows == 0)
	{
		cout << "Aborted" << endl;
		return;
	}

	cout << "Set number of columns" << endl;
	int columns;
	cin >> columns;

	vector<vector<Cell>>().swap(current);
	current.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		current[i].resize(columns);
		for (int j = 0; j < columns; j++)
		{
			bool isAlive;
			cin >> isAlive;
			Cell cell = Cell(isAlive); // TODO: USE SMART POINTERS with emplace_back
			current[i][j] = cell;
		}
	}
	prev = current;
}
