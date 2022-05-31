#ifndef __AUDIO_MIXER__
#define __AUDIO_MIXER__

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

class AudioMixer {
	private:
		bool mutedChunk;
		bool mutedMusic;

	public:
		AudioMixer() { mutedChunk = false; mutedMusic = false; }

		void createAudio();
		void closeAudio();

		bool getMutedChunk() { return mutedChunk; }
		void changeMutedChunk() { mutedChunk = 1 - mutedChunk; }
		void setMutedChunk(bool mutedChunk) { this->mutedChunk = mutedChunk; }

		bool getMutedMusic() { return mutedMusic; }
		void changeMutedMusic() { mutedMusic = 1 - mutedMusic; }
		void setMutedMusic(bool mutedMusic) { this->mutedMusic = mutedMusic; }
};

#endif // __AUDIO_MIXER__
