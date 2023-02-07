#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

#include "Motorcycle.h"

using namespace std;

namespace valetpark
{
	Motorcycle::Motorcycle() : Vehicle()
	{
		m_sidecar = false;
	}
	Motorcycle::Motorcycle(const char* license, const char* makeandmodel) : Vehicle(license, makeandmodel)
	{
		m_sidecar = false;
	}
	Motorcycle::Motorcycle(const Motorcycle& motorcycle)
	{
		operator=(motorcycle);
	}
	Motorcycle& Motorcycle::operator=(const Motorcycle& motorcycle)
	{
		if (&motorcycle != this)
		{
			(Vehicle&)(*this) = motorcycle;
			if (motorcycle.m_sidecar)
			{
				m_sidecar = true;
			}
			else
			{
				m_sidecar = false;
			}
		}
		return *this;
	}
	std::ostream& Motorcycle::writeType(std::ostream& os) const
	{
		if (isCsv())
		{
			os << "M,";
		}
		else
		{
			os << "Vehicle type: Motorcycle" << endl;
		}
		return os;
	}
	std::istream& Motorcycle::read(std::istream& is)
	{
		if (isCsv())
		{
			Vehicle::read(is);
			is >> m_sidecar;
			is.ignore(1000, '\n');
		}
		else
		{
			cout << "\nMotorcycle information entry" << endl;
			Vehicle::read(is);
			bool pass1 = false;
			bool pass2 = false;
			char select[100]{};
			char ch{};
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
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
					m_sidecar = true;
					pass2 = true;
				}
				else if (ch == 'N' || ch == 'n')
				{
					m_sidecar = false;
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
	std::ostream& Motorcycle::write(std::ostream& os) const
	{
		if (isEmpty())
		{
			os << "Invalid Motorcycle Object" << endl;
		}
		else
		{
			Vehicle::write(os);
			if (isCsv())
			{
				os << m_sidecar << endl;
			}
			else
			{
				if (m_sidecar)
				{
					os << "With Sidecar" << endl;
				}
			}
		}
		return os;
	}
}