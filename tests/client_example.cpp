#include <iostream>
using namespace std;

#include "Clock.hpp"
using namespace cat;

#include "hardio.h"

static bool m_running = true;

void on_conn(hardio_client *C) {
	cout << "** Connected to server" << endl;
}

void on_data(hardio_client *C, char *data, int len) {
	cout << "Received " << len << " bytes" << endl;

	hardio_send(C, data, len);
}

void on_disc(hardio_client *C) {
	cout << "** Disconnected from server" << endl;

	m_running = false;
}

int main() {
	hardio_client C;

	hardio_connect(&C, "127.0.0.1", 8765, "public key", on_conn, on_data, on_disc, 0);

	while (!m_running) {
		Clock::sleep(1000);
	}

	cout << "** Good night" << endl;
	return 0;
}

