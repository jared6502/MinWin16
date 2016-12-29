//memory manager

#define M_TABLE_SIZE 16384
#define M_TABLE_LENGTH_UNIT 16

#define SEGMENT_LENGTH (65536 / M_TABLE_LENGTH_UNIT)

//0000:0000		system
//1000:0000		memory allocation stack
//				2b	base address (segment only)
//				2b	length (paragraphs - 16 bytes/8 words)
//				= 16k total items
//				base addr 0000 - reserved
//				base addr FFFF - free
//2000:0000		stack
#define SYSTEM_SEGMENT_COUNT 3

//3000:0000		program memory
//A000:0000		end of program memory (16bit)
#define INIT_FREE_SEGMENT_COUNT 8
#define RESERVED_SEGMENT_COUNT 5
//FFFF:0000		end of program memory (32bit), start of EMS
//beyond		XMS/DPMI

//mm definitions

#define START_BLOCK 2
#define END_BLOCK (M_TABLE_SIZE - 2)

#define SHIFT_BLOCK_SUCCESS 0
#define SHIFT_BLOCK_FAIL -1

#define FREE_MEM_BASE 0xFFFF
#define EMPTY_ENTRY_LEN 0

typdef struct
{
	uint16_t base;
	uint16_t length;
} m_entry;

//mm variables
far m_entry *m_table;

//mm code

//initialize m table
//can be called to reset system to defaults on closing all open programs
//not completely safe, may cause issues
void mm_init()
{
	//m_table address = 1000:0000
	m_table = 0x1000:0x0000;
	
	m_table[0].base = 0x0000;
	m_table[0].length = SYSTEM_SEGMENT_COUNT * SEGMENT_LENGTH;
	
	m_table[1].base = FREE_MEM_BASE;
	m_table[1].length = INIT_FREE_SEGMENT_COUNT * SEGMENT_LENGTH;
	
	m_table[M_TABLE_SIZE - 1].base = 0xA000;
	m_table[M_TABLE_SIZE - 1].length = RESERVED_SEGMENT_COUNT * SEGMENT_LENGTH;
	
	int i;
	
	for (i = START_BLOCK; i <= END_BLOCK; i++)
	{
		m_table[i].base = FREE_MEM_BASE;
		m_table[i].length = EMPTY_ENTRY_LEN;
	}
}

//allocate a block of memory
far void *malloc(int size)
{
	int blocksize;
	
	//round requested size up to multiple of minimum size
	blocksize = size + (16 - (size % 16));
	
	int i;
	
	uint16_t current_pos;
	
	current_pos = 0;
	
	for (i = 0; i < M_TABLE_SIZE; i++)
	{
		//find a free block
		if (m_table[i].base == FREE_MEM_BASE)
		{
			//free block found
			if (m_table[i].length >= blocksize)
			{
				//free block exists and is at least the requested size
				if (m_table[i].length > blocksize)
				{
					//block is bigger than requested, break the block
					if (shift_blocks(i) == SHIFT_BLOCK_FAIL)
					{
						//couldn't shift table entries, can't break any blocks
						//this is the last call before failure (OOM) unless other entries are freed
						//this potentially also locks up a huge chunk of memory for nothing
					}
					else
					{
						//entry added with size of blocksize
						m_table[i].length = blocksize;
						
						//block was just made by splitting it off of the start of the next block
						m_table[i + 1].length -= blocksize;
					}
				}
				
				m_table[i].base = current_pos;
				return (far void *)((uint32_t)(m_table[i].base) << 16);
			}
		}
		else
		{
			//not a free entry, advance segment address to end of checked block
			current_pos += m_table[i].length;
		}
	}
	
	//failed to allocate memory
	return (far void *)0;
}

uint32_t normalize_pointer(far void *ptr)
{
	uint32_t normalized;
	
	//normalize the pointer
	normalized = (uint32_t)ptr;
	normalized = (((normalized & 0xFFFF0000) >> 12) + (normalized & 0x0000FFFF)) >> 4);
	
	return normalized;
}

//free a block of memory
void free(far void *block)
{
	//get base addr from pointer
	uint16_t base;
	base = (uint16_t)(normalize_pointer(block) >> 4);
	
	int i;
	
	for (i = START_BLOCK; i <= END_BLOCK; i++)
	{
		if (m_table[i].base == base)
		{
			//entry found, mark it free
			m_table[i].base = FREE_MEM_BASE;
			return;
		}
	}
}

//scan m table, combine any free memory entries that are adjacent
//expensive, only happens when otherwise out of contiguous memory blocks of the required size
int coalesce_blocks()
{
	//return 1 if blocks were coalesced
	//return 0 if unable to coalesce further
	
	int coalesced;
	int i;
	int j;
	
	uint16_t base;
	
	coalesced = 0;
	
	for (i = START_BLOCK; i < END_BLOCK; i++)
	{
		if ()
	}
	
	return coalesced;
}

//shift table entries by one
//this can fail if there aren't any empty entries left at the end of the list
//in this case, return error
int shift_blocks(int entry)
{
	if (entry > END_BLOCK - 1 || entry < START_BLOCK)
	{
		//invalid entry selection, return failure
		return SHIFT_BLOCK_FAIL;
	}
	
	if (m_table[END_BLOCK].length > EMPTY_ENTRY_LEN)
	{
		//no empty entry, can't shift blocks
		//try combining blocks until they can't be combined further
		while (coalesce_blocks());
		
		if (m_table[END_BLOCK].length > EMPTY_ENTRY_LEN)
		{
			//no possibility of combining blocks further
			//still no entries freed
			return SHIFT_BLOCK_FAIL;
		}
	}
	
	//free entry found at end of table, shift entries down by 1
	int i;
	
	for (i = END_BLOCK; i > entry; i--)
	{
		m_table[i] = m_table[i - 1];
	}
	
	return SHIFT_BLOCK_SUCCESS;
}