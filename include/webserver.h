#pragma once

namespace webserver {
	extern bool running;

	void setup();
	void start();
	void stop();
	void handleRequests();
}
