#ifndef VALETPARK_READWRITABLE_H_
#define VALETPARK_READWRITABLE_H_

namespace valetpark
{
	class ReadWritable
	{
		bool m_flag;
	public:
		ReadWritable();
		virtual ~ReadWritable() {};
		bool isCsv()const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& is) = 0;
		virtual std::ostream& write(std::ostream& os)const = 0;
	};
	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw);
	std::istream& operator>>(std::istream& is, ReadWritable& rw);

}

#endif