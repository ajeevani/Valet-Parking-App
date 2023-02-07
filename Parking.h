#ifndef VALETPARK_PARKING_H_
#define VALETPARK_PARKING_H_
#include <iostream>
#include "Menu.h"
#include "Vehicle.h"

namespace valetpark
{
	const int MAX_PARKING_SPOTS = 100;
	class Parking
	{
		char* m_filename;
		Menu* m_parkingmenu;
		Menu* m_vehiclemenu;
		int m_noOfSpots;
		Vehicle* m_parkingspots[MAX_PARKING_SPOTS];
		int m_parkedcars;

		bool isEmpty();
		void parkingstatus();
		void parkvehicle();
		void returnvehicle();
		void listparkedvehicles();
		void findvehicle();
		bool closeparking();
		bool exitparking();
		bool loaddata();
		void savedata();
	public:
		Parking();
		Parking(const char* filename, int noOfSpots);
		~Parking();
		Parking(const Parking&) = delete;
		void operator=(const Parking&) = delete;
		int run();
	};
}

#endif