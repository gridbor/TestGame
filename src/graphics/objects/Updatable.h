#pragma once


class Updatable {
protected:
	Updatable() = default;

public:
	virtual ~Updatable() = default;

	virtual void Update(float deltaTime) = 0;

protected:
	bool m_updateEnabled = true;

};
