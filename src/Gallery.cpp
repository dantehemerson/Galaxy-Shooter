#include "Gallery.hpp"

#include <stdexcept>
#include <stdio.h>
#include <array>

#include "ResourceNotLoaded.hpp"
#include "R.hpp"

using namespace R;

Gallery* Gallery::gallery = nullptr;

Gallery::Gallery() {
}

Gallery& Gallery::getSingleton() {
	if (!gallery) {
		gallery = new Gallery();
	}
	return *gallery;
}

void Gallery::loadResources() {
	/// Carga las imagenes
	for (size_t i = 0; i < imagesUrl.size(); i++) {
		images[int(Image(i))] = al_load_bitmap(imagesUrl.at(i).c_str());
		if (!images[i]) {
			throw ResourceNotLoaded(imagesUrl.at(i));
		}
	}

	/// Carga las Fuentes para dibujar texto de colorcitas.
	fonts[int(R::Font::VENUS_18)] = al_load_font(fontsUrl.at(0).c_str(), R::Constant::SIZE_FONT_VENUS_18, NULL);
	fonts[int(R::Font::VENUS_20)] = al_load_font(fontsUrl.at(0).c_str(), R::Constant::SIZE_FONT_VENUS_20, NULL);
	fonts[int(R::Font::VENUS_TITLES)] = al_load_font(fontsUrl.at(0).c_str(), R::Constant::SIZE_FONT_VENUS_TITLES, NULL);
	fonts[int(R::Font::VENUS_SMALL)] = al_load_font(fontsUrl.at(0).c_str(), R::Constant::SIZE_FONT_VENUS_SMALL, NULL);
	fonts[int(R::Font::VENUS_BIG)] = al_load_font(fontsUrl.at(0).c_str(), R::Constant::SIZE_FONT_VENUS_BIG, NULL);
	fonts[int(R::Font::VENUS_INTRO)] = al_load_font(fontsUrl.at(0).c_str(), 70, NULL);

	/// Carga los sonidos del juego para escuchar musiquita. claro pesh causha
	for (size_t i = 0; i < soundsUrl.size(); i++) {
		samples[int(Sample(i))] = al_load_sample(soundsUrl.at(i).c_str());
		if (!(samples[i])) {
			throw ResourceNotLoaded(soundsUrl.at(i));
		}
	}

	printf("Pase todos los sonidos\n");
	///// Cargando los streams
	//for (size_t i = 0; i < streamsUrl.size(); i++) {
	//	streams[int(Stream(i))] = al_load_audio_stream(streamsUrl.at(i).c_str(), 4, 1024);
	//	if (!(streams[i])) {
	//		throw ResourceNotLoaded(streamsUrl.at(i));
	//	}
	//	al_set_audio_stream_playing(streams[i], false);
	//	al_set_audio_stream_playmode(streams[i], ALLEGRO_PLAYMODE_LOOP);
	//	al_attach_audio_stream_to_mixer(streams[i], al_get_default_mixer());
	//}
}

ALLEGRO_BITMAP* Gallery::getImage(const Image& id) {
	return images[int(id)];
}

ALLEGRO_FONT* Gallery::getFont(const Font& id) {
	return fonts[int(id)];
}

ALLEGRO_SAMPLE* Gallery::getSample(const Sample& id) {
	return samples[int(id)];
}

ALLEGRO_AUDIO_STREAM* Gallery::getStream(const Stream& id) {
	return streams[int(id)];
}

/* PREGUNTAR A UN PROGRAMADOR SENIOR
Esto es el destructor y la verdad no sé si se ejecuta
La única instancia que se crea es estática, se que los valores estáticos se destruyen
cuando termina el programa y no cuando sale de un bloque.

Ó para estár seguros.
* Crear una función que sirva como contructor y llamarla en el destructor de Application.
*/
Gallery::~Gallery() {
	//	printf("\nEliminando la galería\n"); // Y cómo podría imprimir esto en este caso?
	for (auto it = images.begin(); it != images.end(); it++) {
		al_destroy_bitmap(it->second);
	}

	for (auto it = fonts.begin(); it != fonts.end(); it++) {
		al_destroy_font(it->second);
	}

	//al_stop_samples();
	for (auto it = samples.begin(); it != samples.end(); it++) {
		if (it->second)
			al_destroy_sample(it->second);
	}
	for (auto it = streams.begin(); it != streams.end(); it++) {
		if (it->second)
			al_destroy_audio_stream(it->second);
	}


	images.clear();
	fonts.clear();
	samples.clear();
	streams.clear();
	delete gallery;
}
