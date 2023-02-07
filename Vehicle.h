#ifndef VALETPARK_VEHICLE_H_
#define VALETPARK_VEHICLE_H_

#include "ReadWritable.h"

namespace valetpark
{
	class Vehicle : public ReadWritable
	{
		char m_licenseplate[9]{};
		char* m_makeandmodel{};
		int m_spot;
	protected:
		void setEmpty();
		bool isEmpty()const;
		const char* getLicensePlate();
		const char* getMakeModel();
		void setMakeModel(const char* makemodel);
	public:
		Vehicle();
		Vehicle(const char* license, const char* makemodel);
		Vehicle(const Vehicle& vehicle);
		~Vehicle();
		Vehicle& operator=(const Vehicle& vehicle);
		int getParkingSpot() const;
		void setParkingSpot(int spot);
		bool operator==(const char* license);
		bool operator==(const Vehicle& vehicle);
		std::istream& read(std::istream& is);
		virtual std::ostream& writeType(std::ostream& os)const = 0;
		std::ostream& write(std::ostream& os) const;
	};
}
#endif