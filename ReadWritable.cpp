#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ReadWritable.h"

using namespace std;

namespace valetpark
{
	ReadWritable::ReadWritable()
	{
		m_flag = false;
	}
	bool ReadWritable::isCsv() const
	{
		return m_flag;
	}
	void ReadWritable::setCsv(bool value)
	{
		if (value == true)
		{
			m_flag = true;
		}
		else
		{
			m_flag = false;
		}
	}
	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw)
	{
		rw.write(os);
		return os;
	}
	std::istream& operator>>(std::istream& is, ReadWritable& rw)
	{
		rw.read(is);
		return is;
	}
}