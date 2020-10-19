#pragma once
#include <string>
using namespace std;

class Map
{
public:
	Map(string tID, int ms, int ts); //mfp = map file path, ms = map scale, ts = tile size
	~Map();

	void LoadMap(string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
	string texID;
	int mapScale;
	int tileSize;
	int scaledSize;
};
