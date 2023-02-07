#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

#include "Vehicle.h"

using namespace std;

namespace valetpark
{
	Vehicle::Vehicle() : ReadWritable()
	{
		m_licenseplate[0] = '\0';
		m_makeandmodel = nullptr;
		m_spot = 0;
	}

	Vehicle::Vehicle(const char* license, const char* makemodel) : ReadWritable()
	{
		if ((license != nullptr) && (license[0] != '\0') && (strlen(license) <= 8) && (makemodel != nullptr) && (makemodel[0] != '\0') && (strlen(makemodel) >= 2))
		{
			strcpy(m_licenseplate, license);

			m_makeandmodel = new char[strlen(makemodel) + 1];
			strcpy(m_makeandmodel, makemodel);
			m_spot = 0;
		}
		else
		{
			m_licenseplate[0] = '\0';
			m_makeandmodel = nullptr;
			m_spot = 0;
		}
	}
	Vehicle::Vehicle(const Vehicle& vehicle) : ReadWritable()
	{
		operator=(vehicle);
	}
	Vehicle::~Vehicle()
	{
		delete[] m_makeandmodel;
	}
	Vehicle& Vehicle::operator=(const Vehicle& vehicle)
	{
		if (!(isEmpty()))
		{
			setEmpty();
		}
		if ((vehicle.m_licenseplate != nullptr) && (vehicle.m_licenseplate[0] != '\0') && (strlen(vehicle.m_licenseplate) <= 8) && (vehicle.m_makeandmodel != nullptr) && (vehicle.m_makeandmodel[0] != '\0') && (strlen(vehicle.m_makeandmodel) >= 2))
		{
			strcpy(m_licenseplate, vehicle.m_licenseplate);

			m_makeandmodel = new char[strlen(vehicle.m_makeandmodel) + 1];
			strcpy(m_makeandmodel, vehicle.m_makeandmodel);
			if (vehicle.m_spot != 0)
			{
				m_spot = vehicle.m_spot;
			}
			else
			{
				m_spot = 0;
			}
			if (vehicle.isCsv())
			{
				setCsv(true);
			}
			else
			{
				setCsv(false);
			}
		}
		else
		{
			m_licenseplate[0] = '\0';
			m_makeandmodel = nullptr;
			m_spot = 0;
			setCsv(false);
		}
		return *this;
	}
	int Vehicle::getParkingSpot() const
	{
		return m_spot;
	}
	void Vehicle::setParkingSpot(int spot)
	{
		if (spot >= 0)
		{
			m_spot = spot;
		}
		else
		{
			setEmpty();
		}
	}
	void Vehicle::setEmpty()
	{
		delete[] m_makeandmodel;
		m_makeandmodel = nullptr;
		m_licenseplate[0] = '\0';
		m_spot = 0;
	}
	bool Vehicle::isEmpty() const
	{
		return m_makeandmodel == nullptr;
	}
	const char* Vehicle::getLicensePlate()
	{
		return m_licenseplate;
	}
	const char* Vehicle::getMakeModel()
	{
		return m_makeandmodel;
	}
	void Vehicle::setMakeModel(const char* makemodel)
	{
		if (makemodel != nullptr && makemodel[0] != '\0')
		{
			delete[] m_makeandmodel;
			m_makeandmodel = new char[strlen(makemodel) + 1];
			strcpy(m_makeandmodel, makemodel);
		}
		else
		{
			setEmpty();
		}
	}
	bool Vehicle::operator==(const char* license)
	{
		bool pass = false;

		if ((license != nullptr && license[0] != '\0') && !isEmpty())
		{
			char temp[9];
			strcpy(temp, license);
			int len = strlen(license);
			for (int i = 0; i < len; i++)
			{
				temp[i] = toupper(temp[i]);
			}
			if (strcmp(m_licenseplate, temp) == 0)
			{
				pass = true;
			}
			else
			{
				pass = false;
			}
		}

		return pass;
	}
	bool Vehicle::operator==(const Vehicle& vehicle)
	{
		return operator==(vehicle.m_licenseplate);
	}
	std::istream& Vehicle::read(std::istream& is)
	{
		if (isCsv())
		{
			int tempspot = 0;
			char templisence[100]{};
			char tempmake[100]{};
			is >> tempspot;
			setParkingSpot(tempspot);
			is.ignore(1, ',');
			is.getline(templisence, 8, ',');

			int len = strlen(templisence);
			for (int i = 0; i < len; i++)
			{
				m_licenseplate[i] = toupper(templisence[i]);
			}
			is.getline(tempmake, 60, ',');
			delete[] m_makeandmodel;
			m_makeandmodel = nullptr;
			m_makeandmodel = new char[strlen(tempmake) + 1];
			strcpy(m_makeandmodel, tempmake);
		}
		else
		{
			bool pass1 = false;
			char templisence[100];
			cout << "Enter License Plate Number: ";
			while (!pass1)
			{
				is >> templisence;
				is.clear();

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
				m_licenseplate[i] = toupper(templisence[i]);
			}

			bool pass2 = false;
			cout << "Enter Make and Model: ";
			char tempmake[100]{};
			//char* tempmake{};
			while (!pass2)
			{
				is.ignore(1000, '\n');
				//is.clear();
				//is >> tempmake;
				is.getline(tempmake,60,'\n');
				//is.ignore(1000, '\n');
				//is.ignore('\n');
				//is.clear();
				//len = tempmake.length();
				//{
				if (strlen(tempmake) < 2)
				{
					cout << strlen(tempmake);
					cout << "Invalid Make and model, try again: ";
				}
				else
				{
					pass2 = true;
				}
				//}
			} 
			delete[] m_makeandmodel;
			m_makeandmodel = nullptr;
			m_makeandmodel = new char[strlen(tempmake) + 1];
			strcpy(m_makeandmodel, tempmake);
		}
		return is;
	}
	std::ostream& Vehicle::write(std::ostream& os) const
	{
		if (isEmpty())
		{
			os << "Invalid Vehicle Object\n";
		}
		else
		{
			writeType(os);
			if (isCsv())
			{
				os << m_spot << "," << m_licenseplate << "," << m_makeandmodel << ",";
			}
			else
			{
				if (m_spot == 0)
				{
					os << "Parking Spot Number: N/A\n";
				}
				else
				{
					os << "Parking Spot Number: " << m_spot << endl;
				}
				os << "License Plate: " << m_licenseplate << endl;
				os << "Make and Model: " << m_makeandmodel << endl;
			}
		}

		return os;
	}
}
