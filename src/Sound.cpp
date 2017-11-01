#include "Sound.hpp"

#include "Gallery.hpp"	


void Sound::playSample(R::Sample resourceId) {
	al_play_sample(Gallery::getSingleton().getSample(resourceId), 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Sound::playStream(R::Stream resourceId, bool val) {
	al_set_audio_stream_playing(Gallery::getSingleton().getStream(resourceId), val);
}