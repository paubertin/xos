#include "gdt.h"

using namespace xos;

GlobalDescriptorTable::GlobalDescriptorTable() :
	_null_segment_selector(0,0,0),
	_unused_segment_selector(0,0,0),
	_code_segment_selector(0,64*1024*1024,0x9A),
	_data_segment_selector(0,64*1024*1024,0x92)
{
	uint32 i[2];
	i[0] = sizeof(GlobalDescriptorTable) << 16;
	i[1] = (uint32)(this);

	asm volatile("lgdt (%0)": :"p" ((uint8*)(i)+2));
}

GlobalDescriptorTable::~GlobalDescriptorTable()
{

}

uint16 GlobalDescriptorTable::code_segment_selector() const
{
	return (uint8*)(&_code_segment_selector) - (uint8*)(this);
}

uint16 GlobalDescriptorTable::data_segment_selector() const
{
	return (uint8*)(&_data_segment_selector) - (uint8*)(this);
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32 base, uint32 limit, uint8 flags)
{
	uint8* target = (uint8*)(this);

	if (limit <= 65536)
	{
		target[6] = 0x40;
	}
	else
	{
		if ((limit & 0xfff) != 0xfff)
			limit = (limit >> 12) - 1;
		else
			limit = limit >> 12;

		target[6] = 0xc0;
	}

	target[0] = limit & 0xff;
	target[1] = (limit >> 8) & 0xff;
	target[6] |= (limit >> 16) & 0xf;

	target[2] = base & 0xff;
	target[3] = (base >> 8) & 0xff;
	target[4] = (base >> 16) & 0xff;
	target[7] = (base >> 24) & 0xff;

	target[5] = flags;
}

uint32 GlobalDescriptorTable::SegmentDescriptor::base() const
{
	uint8* target = (uint8*)(this);
	uint32 result = target[7];
	result = (result << 8) + target[4];
	result = (result << 8) + target[3];
	result = (result << 8) + target[2];
	return result;
}

uint32 GlobalDescriptorTable::SegmentDescriptor::limit() const
{
	uint8* target = (uint8*)(this);
	uint32 result = target[6] & 0xf;
	result = (result << 8) + target[1];
	result = (result << 8) + target[0];

	if ((target[6] & 0xc0) == 0xc0)
		result = (result << 12) | 0xfff;

	return result;
}