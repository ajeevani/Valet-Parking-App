#ifndef VALETPARK_CAR_H_
#define VALETPARK_CAR_H_

#include "Vehicle.h"

namespace valetpark
{
	class Car : public Vehicle
	{
		bool m_flagcarwash;
	public:
		Car();
		Car(const char* license, const char* makeandmodel);
		Car(const Car& car);
		Car& operator=(const Car& car);
		~Car() = default;
		std::ostream& writeType(std::ostream& os)const;
		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os)const;
	};
}

#endif