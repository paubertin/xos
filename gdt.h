#pragma once

#include "types.h"

namespace xos {

	class GlobalDescriptorTable
	{
	public:
	
		GlobalDescriptorTable();
		~GlobalDescriptorTable();
	
		uint16 code_segment_selector() const;
		uint16 data_segment_selector() const;
	
		class SegmentDescriptor
		{
		public:
			SegmentDescriptor(uint32 base, uint32 limit, uint8 flags);
	
			uint32 base() const;
			uint32 limit() const;
	
		private:
			uint16 	limit_low;
			uint16 	base_low;
			uint8	base_mid;
			uint8	access;
			uint8	flags_limit_high;
			uint8	base_high;
		} __attribute__((packed));
	
		SegmentDescriptor _null_segment_selector;
		SegmentDescriptor _unused_segment_selector;
		SegmentDescriptor _code_segment_selector;
		SegmentDescriptor _data_segment_selector;
	
	
	};

}