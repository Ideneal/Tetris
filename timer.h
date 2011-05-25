#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>
#include <iostream>

using namespace std;

class Timer{
	private:
		int starTime;
		int pauseTime;
		
		bool paused;
		bool started;
	public:
		Timer();
		
		bool isPaused() const;
		bool isStarted() const;
		int getTicks() const;
		
		void start();
		void pause();
		void unpause();
		void stop();
};
#endif
