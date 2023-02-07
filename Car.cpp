#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Car.h"

using namespace std;

namespace valetpark
{
	Car::Car() : Vehicle()
	{
		m_flagcarwash = false;
	}
	Car::Car(const char* license, const char* makeandmodel) : Vehicle(license, makeandmodel)
	{
		m_flagcarwash = false;
	}
	Car::Car(const Car& car)
	{
		operator=(car);
	}
	Car& Car::operator=(const Car& car)
	{
		if (&car != this)
		{
			(Vehicle&)(*this) = car;
			if (car.m_flagcarwash)
			{
				m_flagcarwash = true;
			}
			else
			{
				m_flagcarwash = false;
			}
		}
		return *this;
	}
	std::ostream& Car::writeType(std::ostream& os) const
	{
		if (isCsv())
		{
			os << "C,";
		}
		else
		{
			os << "Vehicle type: Car" << endl;
		}
		return os;
	}
	std::istream& Car::read(std::istream& is)
	{
		if (isCsv())
		{
			Vehicle::read(is);
			is >> m_flagcarwash;
			is.ignore(1000, '\n');
		}
		else
		{
			cout << "\nCar information entry" << endl;
			Vehicle::read(is);
			bool pass1 = false;
			bool pass2 = false;
			char select[100]{};
			char ch{};
			cout << "Carwash while parked? (Y)es/(N)o: ";
			while (!pass2)
			{	
				while (!pass1)
				{
					is >> select;
					if (strlen(select) > 1)
					{
						cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					}
					else
					{
						pass1 = true;
					}
				}
				ch = select[0];
				if (ch == 'Y' || ch == 'y')
				{
					m_flagcarwash = true;
					pass2 = true;
				}
				else if (ch == 'N' || ch == 'n')
				{
					m_flagcarwash = false;
					pass2 = true;
				}
				else
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					pass1 = false;
				}
			}
		}
		return is;
	}
	std::ostream& Car::write(std::ostream& os) const
	{
		if (isEmpty())
		{
			os << "Invalid Car Object" << endl;
		}
		else
		{
			Vehicle::write(os);
			if (isCsv())
			{
				os << m_flagcarwash << endl;
			}
			else
			{
				if (m_flagcarwash)
				{
					os << "With Carwash" << endl;
				}
				else
				{
					os << "Without Carwash" << endl;
				}
			}
		}
		return os;
	}
}