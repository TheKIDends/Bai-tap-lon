#ifndef __FPS__
#define __FPS__

#include <SDL.h>
#include <SDL_image.h>

class FPS {
	private:
		int start_tick_;
		int pause_tick_;
		bool is_paused_;
		bool is_started_;

	public:
		FPS();
		~FPS();
		void start();
		void stop();
		void paused();
		void unpaused();
		int get_ticks();
		bool is_started();
		bool is_paused();
};

#endif // __FPS__
