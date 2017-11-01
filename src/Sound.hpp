#pragma once

#ifndef SOUND_HPP
#define SOUND_HPP

#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>

#include "R.hpp"

class Sound {
public:
	static void playSample(R::Sample resourceId);
	static void playStream(R::Stream resourceId, bool = true);
private:
};

#endif // !SOUND_HPP
