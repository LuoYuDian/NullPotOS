/*
    Copyright(c) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Uefi.hpp

    Description:
        This header file is used to define the Uefi Specification of the NullPotOS.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
*/

#ifndef UEFI_HPP
#define UEFI_HPP

#include <Types.hpp>

// Uefi Color
#define EFI_BLACK         0x00
#define EFI_BLUE          0x01
#define EFI_GREEN         0x02
#define EFI_CYAN          0x03
#define EFI_RED           0x04
#define EFI_MAGENTA       0x05
#define EFI_BROWN         0x06
#define EFI_LIGHTGRAY     0x07
#define EFI_BRIGHT        0x08
#define EFI_DARKGRAY      0x08
#define EFI_LIGHTBLUE     0x09
#define EFI_LIGHTGREEN    0x0A
#define EFI_LIGHTCYAN     0x0B
#define EFI_LIGHTRED      0x0C
#define EFI_LIGHTMAGENTA  0x0D
#define EFI_YELLOW        0x0E
#define EFI_WHITE         0x0F

#define EFI_BACKGROUND_BLACK      0x00
#define EFI_BACKGROUND_BLUE       0x10
#define EFI_BACKGROUND_GREEN      0x20
#define EFI_BACKGROUND_CYAN       0x30
#define EFI_BACKGROUND_RED        0x40
#define EFI_BACKGROUND_MAGENTA    0x50
#define EFI_BACKGROUND_BROWN      0x60
#define EFI_BACKGROUND_LIGHTGRAY  0x70

typedef UINT64 UINTN; // Our at 64-bit system
typedef UINTN  EFI_STATUS; // Uefi status
typedef void   Void; // Void
typedef UINT16 Char16;
typedef UINTN EFI_PHYSICAL_ADDRESS; // Uefi physical address
typedef UINTN EFI_VIRTUAL_ADDRESS; // Uefi virtual address

typedef Void *EFI_HANDLE; // Uefi handle
typedef Void *EFI_EVENT; // Uefi event

// Uefi status code
#define EFI_ERROR_MASK           0x8000000000000000
#define EFIERR(a)                (EFI_ERROR_MASK | a)
#define EFI_ERROR(status)        (((long long)status) < 0)
#define EFIAPI                   
#define IN                       
#define OUT                      
#define EFI_SUCCESS              0
#define EFI_LOAD_ERROR           EFIERR(1)
#define EFI_INVALID_PARAMETER    EFIERR(2)
#define EFI_UNSUPPORTED          EFIERR(3)
#define EFI_BAD_BUFFER_SIZE      EFIERR(4)
#define EFI_BUFFER_TOO_SMALL     EFIERR(5)
#define EFI_NOT_READY            EFIERR(6)
#define EFI_DEVICE_ERROR         EFIERR(7)
#define EFI_WRITE_PROTECTED      EFIERR(8)
#define EFI_OUT_OF_RESOURCES     EFIERR(9)
#define EFI_VOLUME_CORRUPTED     EFIERR(10)
#define EFI_VOLUME_FULL          EFIERR(11)
#define EFI_NO_MEDIA             EFIERR(12)
#define EFI_MEDIA_CHANGED        EFIERR(13)
#define EFI_NOT_FOUND            EFIERR(14)
#define EFI_ACCESS_DENIED        EFIERR(15)
#define EFI_NO_RESPONSE          EFIERR(16)
#define EFI_NO_MAPPING           EFIERR(17)
#define EFI_TIMEOUT              EFIERR(18)
#define EFI_NOT_STARTED          EFIERR(19)
#define EFI_ALREADY_STARTED      EFIERR(20)
#define EFI_ABORTED              EFIERR(21)
#define EFI_ICMP_ERROR           EFIERR(22)
#define EFI_TFTP_ERROR           EFIERR(23)
#define EFI_PROTOCOL_ERROR       EFIERR(24)
#define EFI_INCOMPATIBLE_VERSION EFIERR(25)
#define EFI_SECURITY_VIOLATION   EFIERR(26)
#define EFI_CRC_ERROR            EFIERR(27)
#define EFI_END_OF_MEDIA         EFIERR(28)
#define EFI_END_OF_FILE          EFIERR(31)
#define EFI_INVALID_LANGUAGE     EFIERR(32)
#define EFI_COMPROMISED_DATA     EFIERR(33)

// PT_LOAD code
#define PtLoad 1

// Uefi file code
#define EFI_FILE_MODE_READ_ONLY  0x00000001
#define EFI_READ_ONLY  EFI_FILE_MODE_READ_ONLY
#define EFI_FILE_MODE_READ   0x0000000000000001
#define EFI_FILE_MODE_WRITE  0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

// View X and Y code
#define ScreenX 1024
#define ScreenY 768

// Memory code
#define FREE_MEMORY 1
#define MMIO_MEMORY 2
#define Uefi_MEMORY 3

// Uefi protocol code
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020


// Max and Min
#define Min(a, b)                ((a) < (b) ? (a) : (b))
#define Max(a, b)                ((a) < (b) ? (b) : (a))

// Uefi allocate type
enum EFI_ALLOCATE_TYPE 
{
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
};

enum EFI_RESET_TYPE 
{
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
};

// Uefi pixel
typedef enum 
{
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBitOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

enum PixelFormat 
{
    kRGBR,
    kBGRR
};

// Uefi memory type
enum EFI_MEMORY_TYPE 
{
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiMaxMemoryType
};

// memory map struct
typedef struct __packed
{
    UINTN MapSize;
    Void *Buffer;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINTN DescriptorVersion;
} MEMORY_MAP;

typedef struct 
{
	UINT32 Type;
	UINT64 PhysicalStart;
	UINT64 PageSize;
} OS_MEMORY_DESCRIPTOR;

// Boot config struct
typedef struct
{
    MEMORY_MAP MemoryMap;
} BOOT_CONFIG;



struct EFI_INPUT_KEY 
{
    UINT16 ScanCode;
    Char16 UnicodeChar;
};

struct EFI_KEY_DATA 
{
    UINT16 Key;
    UINT16 KeyShiftState;
    Boolean KeyToggleState;
};

struct EFI_GUID 
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8  Data4[8];
};

// Uefi memory struct
typedef struct 
{
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
}  __attribute__((__aligned__(16))) EFI_MEMORY_DESCRIPTOR;

struct FrameBufferConfig 
{
    UINT8 *FrameBuffer;
    UINT32 PixelsPerScanLine;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    enum PixelFormat PixelFormat;
};

// Uefi boot services
struct EFI_BOOT_SERVICES 
{
    char _buf1[24];
    UINTN _buf2[2];

    EFIAPI EFI_STATUS(*AllocatePages)(enum EFI_ALLOCATE_TYPE Type, enum EFI_MEMORY_TYPE MemoryType, UINTN Pages,EFI_PHYSICAL_ADDRESS *Memory);
    EFIAPI EFI_STATUS (*FreePages)(EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);
    EFIAPI EFI_STATUS (*GetMemoryMap)(UINTN *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap,UINTN *MapKey, UINTN *DescriptorSize, UINT32 *DescriptorVersion);
    EFIAPI EFI_STATUS (*AllocatePool)(enum EFI_MEMORY_TYPE PoolType, UINTN Size, Void **Buffer);
    EFIAPI EFI_STATUS (*FreePool)(Void *Buffer);

    UINTN _buf4[2];
    EFIAPI EFI_STATUS (*WaitForEvent)(UINTN NumberOfEvents, EFI_EVENT *Event, UINTN *Index);
    UINTN _buf4_2[3];

    UINTN _buf5[9];

    UINTN _buf6[5];

    UINTN  _buf7[2];
    EFIAPI EFI_STATUS (*SetWatchdogTimer)(UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize,Char16 *WatchdogData);

    UINTN _buf8[2];

    EFIAPI EFI_STATUS(*OpenProtocol)(EFI_HANDLE Handle, struct EFI_GUID *Protocol, Void **Interface, EFI_HANDLE AgentHandle,EFI_HANDLE ControllerHandle, UINT32 Attributes);
    UINTN _buf9[2];

    UINTN _buf10[2];
    EFIAPI EFI_STATUS (*LocateProtocol)(struct EFI_GUID *Protocol, Void *Registration, Void **Interface);
    UINTN _buf10_2[2];

    UINTN _buf11;

    UINTN _buf12[3];
};

struct EFI_SYSTEM_TABLE 
{
    char _buf1[44];
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL 
    {
        UINTN     Reset;
        EFIAPI    EFI_STATUS (*ReadKeyStroke)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,struct EFI_INPUT_KEY                  *Key);
        EFI_EVENT WaitForKey;
    }  *ConIn;
    UINTN _buf2;
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL 
    {
        unsigned long long (*SetAttribute)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,unsigned long long Attribute);
        UINTN _buf;
        EFIAPI EFI_STATUS (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, Char16 *String);
        UINTN  _buf2[4];
        EFIAPI EFI_STATUS (*ClearScreen)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    }   *ConOut;
    UINTN   _buf3[3];
    struct EFI_BOOT_SERVICES *BootServices;
    struct EFI_RUNTIME_SERVICES 
    {
        unsigned long long _buf_rs5;
        Void (*ResetSystem)(enum EFI_RESET_TYPE ResetType,unsigned long long ResetStatus,unsigned long long DataSize,Void *ResetData);
    } *RuntimeServices;
};

struct EFI_SIMPLE_POINTER_STATE 
{
    INT32 RelativeMovementX;
    INT32 RelativeMovementY;
    INT32 RelativeMovementZ;
    Boolean LeftButton;
    Boolean RightButton;
};

struct EFI_SIMPLE_POINTER_PROTOCOL 
{
    EFIAPI EFI_STATUS (*Reset)(struct EFI_SIMPLE_POINTER_PROTOCOL *This,unsigned char ExtendedVerification);
    EFIAPI EFI_STATUS (*GetState)(struct EFI_SIMPLE_POINTER_PROTOCOL *This,struct EFI_SIMPLE_POINTER_STATE *State);
    Void *WaitForInput;
};

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL 
{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
    unsigned char Reserved;
};

typedef struct 
{
    UINT32 Version;
    UINT32 HorizontalResolution;
    UINT32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    UINT32 PixelInformation[4];
    UINT32 PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct 
{
    UINT32 MaxMode;
    UINT32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    UINTN SizeOfInfo;
    UINTN FrameBufferBase;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL 
{
    EFIAPI EFI_STATUS (*QueryMode)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, unsigned int ModeNumber, unsigned long long *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
    EFIAPI EFI_STATUS (*SetMode)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, unsigned int ModeNumber);
    UINTN pad;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL 
{
    unsigned long long (*Reset)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,unsigned char ExtendedVerification);
    unsigned long long (*ReadKeyStrokeEx)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,struct EFI_KEY_DATA *KeyData);
    Void *WaitForKeyEx;
    unsigned long long (*SetState)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,unsigned char *KeyToggleState);
    unsigned long long (*RegisterKeyNotify)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,struct EFI_KEY_DATA *KeyData,unsigned long long (*KeyNotificationFunction)(struct EFI_KEY_DATA *KeyData),Void **NotifyHandle);
    unsigned long long (*UnregisterKeyNotify)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,Void *NotificationHandle);
};

struct EFI_LOADED_IMAGE_PROTOCOL 
{
    UINT32                   Revision;
    EFI_HANDLE               ParentHandle;
    struct EFI_SYSTEM_TABLE *SystemTable;

    EFI_HANDLE DeviceHandle;
    Void *FilePath;
    Void *Reserved;

    UINT32 LoadOptionsSize;
    Void  *LoadOptions;

    Void                *ImageBase;
    UINT64               ImageSize;
    enum EFI_MEMORY_TYPE ImageCodeType;
    enum EFI_MEMORY_TYPE ImageDataType;
    EFIAPI               EFI_STATUS (*Unload)(EFI_HANDLE ImageHandle);
};

struct EFI_FILE_INFO
{
    unsigned char _buf[80];
    Char16        FileName[];
};

struct EFI_FILE_PROTOCOL 
{
    UINTN Revision;
    EFIAPI EFI_STATUS(*Open)(struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_PROTOCOL **NewHandle, Char16 *FileName,UINT64 OpenMode, UINT64 Attributes);
    EFIAPI EFI_STATUS (*Close)(struct EFI_FILE_PROTOCOL *This);
    UINTN  _buf2;
    EFIAPI EFI_STATUS (*Read)(struct EFI_FILE_PROTOCOL *This, UINTN *BufferSize, Void *Buffer);
    EFIAPI EFI_STATUS (*Write)(struct EFI_FILE_PROTOCOL *This, UINTN *BufferSize, Void *Buffer);
    UINTN _buf3[4];
    EFIAPI EFI_STATUS (*Flush)(struct EFI_FILE_PROTOCOL *This);
};
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL 
{
    UINT64 Revision;
    EFIAPI EFI_STATUS (*OpenVolume)(struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,struct EFI_FILE_PROTOCOL **Root);
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static Void Xmemset(Void *Dst_, UINT8 Value, UINTN Size) 
{
    UINT8 *Dst = (UINT8 *)Dst_;
    while (Size-- > 0)
    {
        *Dst++ = Value;
    }
}

static Void *Xmemcpy(Void *Dst_, const Void *Src_, UINTN Size) 
{
    UINT8       *Dst = (UINT8 *)Dst_;
    const UINT8 *src = (UINT8 *)Src_;
    while (Size-- > 0)
    {
        *Dst++ = *src++;
    }
    return (Void *)Src_;
}

#pragma GCC diagnostic pop
#endif // UEFI_HPP