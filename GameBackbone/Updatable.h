#pragma once
class Updatable {
public:

	Updatable() {
	}

	virtual ~Updatable() {
	}

	virtual void update() = 0;
};

