#include <cstdio>
#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"

using namespace std;

int main(int argc, char* args[]) {

	srand(static_cast<unsigned int>(time(0)));

	Screen screen;

	if (screen.init() == false) {
		cout << "Error initializing SDL." << endl;
	}

	double rSpeed = 0.0001;
	double gSpeed = 0.0002;
	double bSpeed = 0.0003;

	Swarm swarm;

	const Particle* const pParticles = swarm.getParticles();

	while (true) {
		
		int elapsed = SDL_GetTicks();

		swarm.update(elapsed);

		unsigned char red = (1 + sin(elapsed * rSpeed)) * 128;
		unsigned char green = (1 + sin(elapsed * gSpeed)) * 128;
		unsigned char blue = (1 + sin(elapsed * bSpeed)) * 128;
		
		//const Particle* const pParticles = swarm.getParticles();
		
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;
			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		screen.update();

		if (screen.processEvents() == false) {
			break;
		}
	}

	screen.close();

	return 0;
}