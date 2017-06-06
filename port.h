#pragma once

#include "types.h"

namespace xos {

	class Port
	{
	protected:
		Port(uint16 pnumber);
		~Port();

		uint16 port_number;
	};

	class Port8bit : public Port
	{
	public:
		Port8bit(uint16 pnumber);
		~Port8bit();

		virtual void write(uint8 data);
		virtual uint8 read();
	};

	class Port8bitSlow : public Port8bit
	{
	public:
		Port8bitSlow(uint16 pnumber);
		~Port8bitSlow();

		virtual void write(uint8 data);
	};


	class Port16bit : public Port
	{
	public:
		Port16bit(uint16 pnumber);
		~Port16bit();

		void write(uint16 data);
		uint16 read();
	};

	class Port32bit : public Port
	{
	public:
		Port32bit(uint16 pnumber);
		~Port32bit();

		void write(uint32 data);
		uint32 read();
	};

}