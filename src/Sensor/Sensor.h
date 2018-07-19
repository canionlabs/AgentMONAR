#pragma once


class Sensor {
public:
	Sensor(int PORT);

	bool isDS18B20();
	int getCount();
	float getTemperature(int index);

private:
	int PORT;	
};