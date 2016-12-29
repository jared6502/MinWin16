//API handler

#include "kernel.h"
#include "regs.h"

extern Regs InRegs;
extern Regs OutRegs;

void HandleAPICall()
{
	OutRegs = InRegs;
	
	switch (InRegs.bytes[AH])
	{
		case 0x00:
			//terminate program
			TerminateProgram();
			break;
			
		case 0x01:
			//read stdin char with echo into AL
			//ctrl+brk terminates program
			break;
			
		case 0x02:
			//put char in DL to stdout
			break;
			
		case 0x03:
			//read char from stdin into AL
			break;
			
		case 0x04:
			//write char in DL to stdout
			break;
			
		case 0x05:
			//write char in DL to printer
			break;
			
		case 0x06:
			if (InRegs.bytes[DL] != 0xFF)
			{
				//write char in DL to stdout
			}
			else
			{
				//read char from stdin into AL
				//set ZF and return if no char available
			}
			break;
			
		case 0x07:
			//read stdin char without echo into AL
			break;
			
		case 0x08:
			//read stdin char without echo into AL
			//ctrl+brk terminates program
			break;
			
		case 0x09:
			//print $ terminated string to stdout
			//pointer is in DS:DX
			//ctrl+brk terminates program
			break;
			
		case 0x0A:
			//get string including cr from stdin
			//pointer is in DS:DX
			//first byte - buffer size
			//second byte - returned string length
			//nth byte - string
			//ctrl+brk and ctrl+c terminate program
			break;
			
		case 0x0B:
			//check for chars on stdin
			//ctrl+brk terminates program
			break;
			
		case 0x0C:
			//clear stdin buffer
			//execute function in AL
			//valid: 0x01, 0x06, 0x07, 0x08, 0x0A
			break;
			
		case 0x0D:
			//flush all file buffers
			break;
			
		case 0x0E:
			//select drive by index
			//return total number of drives
			break;
			
		case 0x0F:
			//open file with FCB
			//pointer is in DS:DX
			//return value in AL (0x00 - failure, 0xFF - success)
			break;
			
		case 0x10:
			//close file with FCB
			//see above
			break;
			
		case 0x11:
			//find first file matching FCB
			//see above
			break;
			
		case 0x12:
			//find next file matching FCB
			//see above
			break;
			
		case 0x13:
			//delete file using FCB
			//see above
			break;
			
		case 0x14:
			//sequential file read using FCB
			//see above
			//AL = 0 on success, 1 on EOF and no data read, 2 if buffer too small (?), 3 if EOF and data read
			
		default:
			break;
	}
}