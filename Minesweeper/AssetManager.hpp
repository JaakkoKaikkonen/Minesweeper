#pragma once

#include <map>

#include <SFML/Graphics.hpp>

namespace Game {

	class AssetManager {

	public:
		void loadTexture(std::string name, std::string fileName);
		sf::Texture& getTexture(std::string name);

		void loadFont(std::string name, std::string fileName);
		sf::Font& getFont(std::string name);

	private:
		std::map<std::string, sf::Texture> textures;
		std::map<std::string, sf::Font> fonts;

	};

}