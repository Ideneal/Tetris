#include "timer.h"

Timer::Timer(){
	this->starTime = 0;
	this->pauseTime = 0;
	this->paused = false;
	this->started = false;
}

bool Timer::isPaused() const{
	return this->paused;
}

bool Timer::isStarted() const{
	return this->started;
}

int Timer::getTicks() const{
	if(this->started){
		if(this->paused)
			return this->pauseTime;
		else
			return SDL_GetTicks() - this->starTime;
	}
	
	return 0;
}

void Timer::start(){
	this->started = true;
	this->paused = false;
	this->starTime = SDL_GetTicks();
	this->pauseTime = 0;
}

void Timer::pause(){
	if(this->started && !this->paused){
		this->paused = true;
		this->pauseTime = SDL_GetTicks() - this->starTime;
	}
}

void Timer::unpause(){
	if(this->paused){
		this->starTime = this->pauseTime;
		this->pauseTime = 0;
		this->paused = false;
	}
}

void Timer::stop(){
	this->started = false;
	this->paused = false;
}
