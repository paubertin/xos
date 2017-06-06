#include "port.h"

using namespace xos;

// base class

Port::Port(uint16 pnumber):
	port_number(pnumber)
{ }

Port::~Port()
{ }

// 8 bit

Port8bit::Port8bit(uint16 pnumber):
	Port(pnumber)
{ }

Port8bit::~Port8bit()
{ }

void Port8bit::write(uint8 data)
{
	__asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port_number));
}

uint8 Port8bit::read()
{
	uint8 result;
	__asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (port_number));
	return result;
}

// 8bit slow

Port8bitSlow::Port8bitSlow(uint16 pnumber):
	Port8bit(pnumber)
{ }

Port8bitSlow::~Port8bitSlow()
{ }

void Port8bitSlow::write(uint8 data)
{
	__asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (port_number));
}

// 16 bit

Port16bit::Port16bit(uint16 pnumber):
	Port(pnumber)
{ }

Port16bit::~Port16bit()
{ }

void Port16bit::write(uint16 data)
{
	__asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (port_number));
}

uint16 Port16bit::read()
{
	uint16 result;
	__asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (port_number));
	return result;
}

// 32 bit

Port32bit::Port32bit(uint16 pnumber):
	Port(pnumber)
{ }

Port32bit::~Port32bit()
{ }

void Port32bit::write(uint32 data)
{
	__asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (port_number));
}

uint32 Port32bit::read()
{
	uint32 result;
	__asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (port_number));
	return result;
}