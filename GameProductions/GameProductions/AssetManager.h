#pragma once

#include <map> //to store list of textures the game has
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "EntityComponentSystem.h"
//#include "SDL_ttf.h"

//class responsible for managing textures and creating game objects
class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	//game objects
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);


	//texture management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	//void AddFont(std::string id, std::string path, int fontsize);
	//TTF_Font* GetFont(std::string id);

private:
	Manager* manager;
	//assign a key to each value so we can grab it via that key
	std::map<std::string, SDL_Texture*> textures;
	//std::map<std::string, TTF_Font*> fonts;
};
