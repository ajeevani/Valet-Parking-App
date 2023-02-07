#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#include "Parking.h"
#include "Car.h"
#include "Motorcycle.h"
using namespace std;

namespace valetpark
{
	bool Parking::isEmpty()
	{
		return (m_filename == nullptr);
	}
	void Parking::parkingstatus()
	{
		cout << "****** Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout << setw(4) << left << (m_noOfSpots - m_parkedcars);
		cout.unsetf(ios::left);
		cout << " *****" << endl;
	}
	void Parking::parkvehicle()
	{
		if (m_parkedcars == m_noOfSpots)
		{
			cout << "Parking is full" << endl;
		}
		else
		{
			int selection = m_vehiclemenu->run();
			Vehicle* tempvehicle{};
			switch (selection)
			{
			case 1:
				tempvehicle = new Car();
				break;
			case 2:
				tempvehicle = new Motorcycle();
				break;
			case 3:
				cout << "Parking Cancelled" << endl;
				return;
			}
			tempvehicle->setCsv(false);
			cin >> *tempvehicle;
			bool pass1 = false;
			for (int i = 0; i < m_noOfSpots && !pass1; i++)
			{
				if (m_parkingspots[i] == nullptr)
				{
					tempvehicle->setParkingSpot(i + 1);
					m_parkingspots[i] = tempvehicle;
					m_parkedcars++;
					cout << endl << "Parking Ticket" << endl;
					cout << *tempvehicle << endl;
					pass1 = true;
				}
			}
			//delete[] tempvehicle;
		}

		cin.ignore();
		cout << "Press <ENTER> to continue....";
		cin.ignore(1000, '\n');
	}
	void Parking::returnvehicle()
	{
		bool pass1 = false;
		char templisence[100];

		cout << "Return Vehicle" << endl;
		cout << "Enter License Plate Number: ";
		while (!pass1)
		{
			cin.clear();
			//cin.ignore(1000, '\n');
			cin >> templisence;

			if (strlen(templisence) > 8)
			{
				cout << "Invalid License Plate, try again: ";
			}
			else
			{
				pass1 = true;
			}
		}

		int len = strlen(templisence);
		for (int i = 0; i < len; i++)
		{
			templisence[i] = toupper(templisence[i]);
		}

		bool pass2 = false;
		for (int i = 0; i < m_noOfSpots && !pass2; i++)
		{
			if (m_parkingspots[i] && (*m_parkingspots[i] == templisence))
			{
				cout << endl << "Returning:" << endl;
				m_parkingspots[i]->setCsv(false);
				cout << *m_parkingspots[i];
				delete m_parkingspots[i];
				m_parkingspots[i] = nullptr;
				m_parkedcars--;
				pass2 = true;
			}
		}
		if (!pass2)
		{
			cout << endl << "License plate " << templisence << " Not found" << endl;
		}

		cin.ignore();
		cout << endl << "Press <ENTER> to continue....";
		cin.ignore(1000, '\n');
	}
	void Parking::listparkedvehicles()
	{
		cout << "*** List of parked vehicles ***" << endl;
		for (int i = 0; i < m_noOfSpots; i++)
		{
			if (m_parkingspots[i] != nullptr)
			{
				m_parkingspots[i]->setCsv(false);
				cout << *m_parkingspots[i];
				cout << "-------------------------------" << endl;
			}
		}
		cout << "Press <ENTER> to continue....";
		cin.ignore(1000, '\n');
	}
	void Parking::findvehicle()
	{
		bool pass1 = false;
		char templisence[100];

		cout << "Vehicle Search" << endl;
		cout << "Enter License Plate Number: ";
		while (!pass1)
		{
			cin.clear();
			//cin.ignore(1000, '\n');
			cin >> templisence;

			if (strlen(templisence) > 8)
			{
				cout << "Invalid License Plate, try again: ";
			}
			else
			{
				pass1 = true;
			}
		}

		int len = strlen(templisence);
		for (int i = 0; i < len; i++)
		{
			templisence[i] = toupper(templisence[i]);
		}

		bool pass2 = false;
		for (int i = 0; i < m_noOfSpots && !pass2; i++)
		{
			if (m_parkingspots[i] && (*m_parkingspots[i] == templisence))
			{
				pass2 = true;
				m_parkingspots[i]->setCsv(false);
				cout << endl << "Vehicle found:" << endl;
				cout << *m_parkingspots[i];
			}
		}
		if (!pass2)
		{
			cout << endl << "License plate " << templisence << " Not found" << endl;
		}
		cin.ignore();
		cout << endl << "Press <ENTER> to continue....";
		cin.ignore(1000, '\n');
	}
	bool Parking::closeparking()
	{
		bool pass = true;
		if (isEmpty())
		{
			cout << "Closing Parking" << endl;
			return true;
		}
		else
		{
			char select;
			int done = 0;
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			do {
				select = cin.get();
				if (select == 'y' || select == 'Y')
				{
					cout << "Closing Parking" << endl;
					for (int i = 0; i < m_noOfSpots; i++)
					{
						if (m_parkingspots[i] != nullptr)
						{
							cout << endl << "Towing request" << endl;
							cout << "*********************" << endl;
							m_parkingspots[i]->setCsv(false);
							cout << *m_parkingspots[i];
							delete m_parkingspots[i];
							m_parkingspots[i] = nullptr;
						}
					}
					pass = true;
					done = 1;

				}
				else if (select == 'n' || select == 'N')
				{
					pass = false;
					done = 1;
				}
				else
				{
					cin.ignore(1000, '\n');
					select = 'x';
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			} while (done == 0);
		}
		return pass;
	}
	bool Parking::exitparking()
	{
		bool pass;
		char select;
		int done = 0;
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		do {
			select = cin.get();
			if (select == 'y' || select == 'Y')
			{
				cout << "Exiting program!" << endl;
				pass = true;
				done = 1;

			}
			else if (select == 'n' || select == 'N')
			{
				pass = false;
				done = 1;
			}
			else
			{
				cin.ignore(1000, '\n');
				select = 'x';
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
		} while (done == 0);
		return pass;
	}
	bool Parking::loaddata()
	{
		bool pass = 1;
		if (isEmpty())
		{
			pass = false;
		}
		else
		{
			ifstream file;
			file.open(m_filename);
			Vehicle* vehicle = nullptr;
			m_parkedcars = 0;
			bool pass2 = true;
			while (pass2)
			{
				char c = '\0';
				file.get(c);
				file.ignore();
				if (c == 'C')
				{
					vehicle = new Car();
				}
				else if (c == 'M')
				{
					vehicle = new Motorcycle();
				}
				else
				{
					break;
				}
				vehicle->setCsv(true);
				file >> *vehicle;
				m_parkingspots[vehicle->getParkingSpot() - 1] = vehicle;
				m_parkedcars++;
				if (m_parkedcars == m_noOfSpots)
				{
					pass2 = false;
				}
			}

			file.close();
		}

		return pass;
	}
	void Parking::savedata()
	{
		if (!isEmpty())
		{
			ofstream file;
			file.open(m_filename);
			if (file.is_open())
			{
				for (int i = 0; i < m_noOfSpots; i++)
				{
					if (m_parkingspots[i])
					{
						m_parkingspots[i]->setCsv(true);
						file << *m_parkingspots[i];
						file.flush(); // havent tried yet
					}
				}
				file.close();
			}
		}
	}
	Parking::Parking()
	{
		m_filename = nullptr;
		m_parkingmenu = nullptr;
		m_vehiclemenu = nullptr;
		for (int i = 0; i < MAX_PARKING_SPOTS; i++)
		{
			m_parkingspots[i] = nullptr;
		}
		m_parkedcars = 0;
		m_noOfSpots = 0;
	}
	Parking::Parking(const char* filename, int noOfspots) 
	{
		for (int i = 0; i < MAX_PARKING_SPOTS; i++)
		{
			m_parkingspots[i] = nullptr;
		}
		m_parkedcars = 0;

		if (filename && filename[0] && !(noOfspots < 10 && noOfspots > MAX_PARKING_SPOTS))
		{
			m_noOfSpots = noOfspots;
			m_filename = new char[strlen(filename) + 1];
			strcpy(m_filename, filename);
			if (loaddata())
			{
				m_parkingmenu = new Menu("Parking Menu, select an action:");
				m_parkingmenu->add("Park Vehicle");
				m_parkingmenu->add("Return Vehicle");
				m_parkingmenu->add("List Parked Vehicles");
				m_parkingmenu->add("Find Vehicle");
				m_parkingmenu->add("Close Parking (End of day)");
				m_parkingmenu->add("Exit Program");

				m_vehiclemenu = new Menu("Select type of the vehicle:",1);
				m_vehiclemenu->add("Car");
				m_vehiclemenu->add("Motorcycle");
				m_vehiclemenu->add("Cancel");
			}
			else
			{
				m_parkingmenu = nullptr;
				m_vehiclemenu = nullptr;
			}
		}
		else
		{
			cout << "Error in data file" << endl;

			m_filename = nullptr;
			m_parkingmenu = nullptr;
			m_vehiclemenu = nullptr;
			m_noOfSpots = 0;
		}
	}
	Parking::~Parking()
	{
		savedata();
		delete[] m_filename;
		delete m_parkingmenu;
		delete m_vehiclemenu;
		for (int i = 0; i < m_noOfSpots; i++)
		{
			delete m_parkingspots[i];
			//m_parkingspots[i] = nullptr;
		}
	}
	int Parking::run()
	{
		int choice;
		int exit = 0;
		if (!isEmpty())
		{
			while (!exit)
			{
				parkingstatus();
				choice = m_parkingmenu->run();
				switch (choice)
				{
				case 1:
					parkvehicle();
					break;
				case 2:
					returnvehicle();
					break;
				case 3:
					listparkedvehicles();
					break;
				case 4:
					findvehicle();
					break;
				case 5:
					if (closeparking())
					{
						exit = 1;
					}
					break;
				case 6:
					if (exitparking())
					{
						exit = 1;
					}
					break;
				}
			}
		}

		return exit;
	}
}