#pragma once
#include "../Math/Vector3.h"
#include <string>

struct SDL_Texture;

namespace viper {
	class Text {
	public:
		Text() = default;
		Text(class Font* font) : m_font{ font } {}
		~Text();

		bool Create(class Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(class Renderer& renderer, float x, float y);

	private:
		class Font* m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}