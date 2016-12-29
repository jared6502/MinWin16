#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdint.h>

typedef struct
{
    uint8_t Signature[2];
    uint8_t DosStuff[28];
    uint16_t StubRelocationTable;
    uint8_t Reserved[28];
    uint32_t NE_Header_Offset;
} MZ_Header;

typedef struct
{
    uint8_t Signtaure[2];
    uint8_t LinkerMajorVersion;
    uint8_t LinkerMinorVersion;
    uint16_t EntryTableOffset;
    uint16_t EntryTableLength;
    uint32_t FileLoadChecksum;
    uint8_t ProgramFlags;
    uint8_t ApplicationFlags;
    uint8_t AutoDataSegmentIndex;
    uint16_t InitialLocalHeapSize;
    uint16_t InitialStackSize;
    uint32_t EntryPoint;
    uint32_t InitialStackPointer;
    uint16_t SegmentCount;
    uint16_t ModuleReferenceCount;
    uint16_t NonResidentNameTableSize;
    uint16_t SegmentTableOffset;
    uint16_t ResourceTableOffset;
    uint16_t ResidentNameTableOffset;
    uint16_t ModuleReferenceTableOffset;
    uint16_t ImportedNameTableOffset;
    uint32_t NonResidentNameTableOffset;
    uint16_t MovableEntryPointCount;
    uint16_t FileAlignmentSizeShiftCount;
    uint16_t ResourceTableEntryCount;
    uint8_t TargetOS;
    uint8_t OtherFlags;
    uint16_t GangloadAreaOffset;
    uint16_t GangloadAreaLength;
    uint16_t MinimumCodeSwapAreaSize;
    uint16_t ExpectedWindowsVersion;
} NE_Header;

#endif

