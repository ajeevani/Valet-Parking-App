#ifndef VALETPARK_MOTORCYCLE_H_
#define VALETPARK_MOTORCYCLE_H_

#include "Vehicle.h"

namespace valetpark
{
	class Motorcycle : public Vehicle
	{
		bool m_sidecar;
	public:
		Motorcycle();
		Motorcycle(const char* license, const char* makeandmodel);
		Motorcycle(const Motorcycle& motorcycle);
		Motorcycle& operator=(const Motorcycle& motorcycle);
		~Motorcycle() = default;
		std::ostream& writeType(std::ostream& os)const;
		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os)const;
	};
}

#endif 
