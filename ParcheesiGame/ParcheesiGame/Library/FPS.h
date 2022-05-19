#ifndef __FPS__
#define __FPS__

class FPS {
	private:
		int startTick;
		int pauseTick;
		bool isPaused;
		bool isStarted;

	public:
		FPS();
		~FPS();
		void start();
		void stop();
		void paused();
		void unpaused();
		int getTicks();
		bool getIsStarted();
		bool getIsPaused();
};

#endif // __FPS__
