#pragma once
#ifndef GALLERY_HPP
#define GALLERY_HPP

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_audio.h>
//#include <allegro5\allegro_acodec.h>

#include <map>

#include "R.hpp"

class Gallery {
public:
	static Gallery& getSingleton();

	ALLEGRO_BITMAP* getImage(const R::Image& id);
	ALLEGRO_FONT* getFont(const R::Font& id);
	ALLEGRO_SAMPLE* getSample(const R::Sample& id);
	ALLEGRO_AUDIO_STREAM* getStream(const R::Stream& id);

	/* Carga todos las imagenes, sonidos y fuentes.*/
	void loadResources();
	~Gallery();
private:
	Gallery();
	static Gallery* gallery; /// Apuntador a la única instancia que se creará.

	/// Maps para almacenar los recursos
	std::map<unsigned int, ALLEGRO_BITMAP*> images;
	std::map<int, ALLEGRO_FONT*> fonts;
	std::map<int, ALLEGRO_SAMPLE*> samples;
	std::map<int, ALLEGRO_AUDIO_STREAM*> streams;
};

#endif // !GALLERY_HPP
