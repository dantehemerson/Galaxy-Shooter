#pragma once
#ifndef R_HPP
#define R_HPP

#include <allegro5\allegro.h>
#include <allegro5\allegro_color.h>

#include <string>
#include <array>

namespace R {
	namespace Constant {

		// Frames por segundo.
		static const int FPS = 140;
		static const int SIZE_FONT_VENUS_18 = 18;
		static const int SIZE_FONT_VENUS_20 = 20;
		static const int SIZE_FONT_VENUS_TITLES = 60;
		static const int SIZE_FONT_VENUS_BIG = 50;
		static const int SIZE_FONT_VENUS_SMALL = 14;
	}
	namespace Dimen {
		// Ancho y alto de la pantalla
		static const int WIDTH  = 800;
		static const int HEIGHT = 600;
	}

	namespace String {
		static const std::string WINDOW_TITLE = "Arkanoid";
		static const std::string ERROR_INSTALL_KEYBOARD = "Error al instalar el teclado.";
		static const std::string ERROR_ALLEGRO_INIT = "Error al iniciar la librearía Allegro";

		static const std::string ERROR_INSTALL_MOUSE = "Error al instalar el ratón";
		static const std::string ERROR_INSTALL_AUDIO = "Error al instalar el periférico de audio.";
		static const std::string ERROR_INSTALL_PHYSICS = "Error al iniciar physics.";
		static const std::string ERROR_ABRIR_FICHERO_RECURSOS = "Error al abrir el fichero de recursos.";

		static const std::string PLAY_GAME = "START GAME";
		static const std::string HIGHSCORES = "HIGHSCORES";
		static const std::string OPTIONS = "OPTIONS";
		static const std::string HELP = "HELP";
		static const std::string ABOUT = "ABOUT";
		static const std::string QUIT = "QUIT";
		static const std::string BACK = "BACK";

		static const std::string VERSION_GAME = "VERSION 1.0.0.1";
		static const std::string POWERED = "POWERED";
		static const std::string COPYRIGHT = "Copyright (C) 2017 Dante Calderon";
		static const std::string GITHUB = "GITHUB";
		static const std::string NAME_AUTHOR = "DANTE CALDERON";
		static const std::string AND = "AND";

		static const std::string BRICK_WHITE_DESCRIPTION = "WHITE - 50 PTS";
		static const std::string BRICK_ORANGE_DESCRIPTION = "ORANGE - 60 PTS";
		static const std::string BRICK_LIGHT_BLUE_DESCRIPTION = "LIGHT BLUE - 70 PTS";
		static const std::string BRICK_GREEN_DESCRIPTION = "GREEN - 80 PTS";
		static const std::string BRICK_RED_DESCRIPTION = "RED - 90 PTS";
		static const std::string BRICK_BLUE_DESCRIPTION = "BLUE - 100 PTS";
		static const std::string BRICK_PINK_DESCRIPTION = "PINK - 110 PTS";
		static const std::string BRICK_YELLOW_DESCRIPTION = "YELLOW - 120 PTS";
		static const std::string BRICK_SILVER_DESCRIPTION = "SILVER - 50 PTS X ROUND #";
		static const std::string BRICK_GOLD_DESCRIPTION = "GOLD - INDESTRUCTIBLE";

		/// Archivo de configuraciones titulos
		static const std::string CONFIG_SCREEN = "SCREEN";
		static const std::string CONFIG_SOUND = "SOUND";
		static const std::string CONFIG_CONTROL = "CONTROL";


		/// Menu Pausa
		static const std::string PAUSE = "PAUSE";
		static const std::string CONTINUE = "CONTINUE";
		static const std::string RESTART = "RESTART";

		static const std::string GAMEOVER = "GAME OVER";
	}


	/// Colores
	namespace Color {
		static const ALLEGRO_COLOR WHITE = { 1.0, 1.0, 1.0 };
		static const ALLEGRO_COLOR BLACK = { 0.0, 0.0, 0.0 };
		static const ALLEGRO_COLOR GREEN = { 0.0, 1.0, 0.0 };
		//static const ALLEGRO_COLOR GRAY = al_color_html("#2BDA50");
		static const ALLEGRO_COLOR GRAY = al_color_html("#8F8F8F");
		//static const ALLEGRO_COLOR YELLOW_BTN = al_color_html("#C3C3C3");
		static const ALLEGRO_COLOR BUTTON_FOCUSED = al_color_html("#c22d2d");

		static const ALLEGRO_COLOR SHADOWN_TITLE = al_color_html("#FF1F28");
		static const ALLEGRO_COLOR GITHUB = al_color_html("#8B368C");


		/* ? - Esto no funcióna la transparencia*/
		//static const ALLEGRO_COLOR BACKGROUND_ABOUT_TRANSPARENT = al_map_rgba(125, 215, 215, 255);

		static const ALLEGRO_COLOR BACKGROUND_ABOUT_TRANSPARENT = al_map_rgba_f(0.4, 0.4, 0.4, 0.5);
		static const ALLEGRO_COLOR BACKGROUND_HIGHSCORE_TRANSPARENT = al_map_rgba_f(0.3, 0.3, 0.3, 0.5);
		static const ALLEGRO_COLOR TRANSPARENTS = al_map_rgba_f(0.0, 0.0, 0.0, 0.0);

		/* Declaro y no funcióna talvéz es por static */
		static const ALLEGRO_COLOR BACKGROUND_STARTING = al_map_rgba(50, 50, 50, 150);
		static const ALLEGRO_COLOR BACKGROUND_LOSING = al_map_rgba(80, 0, 0, 150);
		static const ALLEGRO_COLOR SHADOW_GRAY = al_color_html("#8d8b8f");
	}
	static const std::array<std::string, 5>
		fontsUrl = {
		"resources/fonts/venus.ttf",
	};
	enum class Font {
		VENUS_18,
		VENUS_20,
		VENUS_TITLES,
		VENUS_SMALL,
		VENUS_BIG,
		VENUS_INTRO
	};

	static const std::array<std::string, 19>
		imagesUrl = {
		"resources/images/arkanoid_logo.png",
		"resources/images/items.png",
		"resources/images/spaceship_1.png",
		"resources/images/background1.png",
		"resources/images/button.png",
		"resources/images/button_focused.png",
		"resources/images/cplusplus.png",
		"resources/images/allegro.jpg",
		"resources/images/buttton_medium_focused.png",
		"resources/images/buttton_medium.png",
		"resources/images/buttton_medium_facebook.png",
		"resources/images/buttton_medium_github.png",
		"resources/images/buttton_medium_google_plus.png",
		"resources/images/button_small_focused.png",
		"resources/images/button_small.png",
		"resources/images/shadow_top.png",
		"resources/images/shadow_bottom.png",
		"resources/images/shadow_left.png",
		"resources/images/shadow_right.png"
	};
	enum class Image {
		ARKANOID_LOGO,
		ITEMS,
		PADDLE,
		BACKGROUND1,
		BUTTON,
		BUTTON_FOCUSED,
		C_PLUS_PLUS_LOGO,
		ALLEGRO_LOGO,
		BUTTON_MEDIUM_FOCUSED,
		BUTTON_MEDIUM,
		BUTTON_FACEBOOK,
		BUTTON_GITHUB,
		BUTTON_GOOGLE_PLUS,
		BUTTON_SMALL_FOCUSED,
		BUTTON_SMALL,
		SHADOW_TOP,
		SHADOW_BOTTOM,
		SHADOW_LEFT,
		SHADOW_RIGHT
	};

	static const std::array<std::string, 4>
		soundsUrl = {
		"resources/sounds/release.wav",
		"resources/sounds/bounce.wav",
		"resources/sounds/click.wav",
		"resources/sounds/shot.wav"
	};
	enum class Sample {
		RELEASE,
		BOUNCE,
		CLICK,
		SHOT
	};

	enum class Stream {

	};


}

/// Constantes para registrar eventos.
enum ActionMenu {
	DOWN,
	UP,
	ENTER,
	LEFT,
	RIGHT,
	MOUSE_MICKEY_LEFT,
	BACKSPACE,
	MOUSE_MICKEY_LEFT_DOWN,
	MOUSE_MICKEY_LEFT_UP,
	ESCAPE
};

#endif // !R_HPP
