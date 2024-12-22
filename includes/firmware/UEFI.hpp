// 创建于2024.12.22
// NullPotOS UEFI规范定义

#ifndef INCLUDES_FIRMWARE_UEFI_HPP_
#define INCLUDES_FIRMWARE_UEFI_HPP_

// types
typedef __UINT8_TYPE__  uint8;
typedef __UINT16_TYPE__ uint16;
typedef __UINT32_TYPE__ uint32;
typedef __UINT64_TYPE__ uint64;
typedef __INT8_TYPE__  int8;
typedef __INT16_TYPE__ int16;
typedef __INT32_TYPE__ int32;
typedef __INT64_TYPE__ int64;
typedef char boolean;

// UEFI color
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

// more types
typedef uint64 uintn; // our at 64-bit system
typedef uintn  EFI_STATUS; // UEFI status
typedef void   VOID; // void
typedef uint16 char16;
typedef uintn EFI_PHYSICAL_ADDRESS; // UEFI physical address
typedef uintn EFI_VIRTUAL_ADDRESS; // UEFI virtual address

typedef void *EFI_HANDLE; // UEFI handle
typedef void *EFI_EVENT; // UEFI event

// UEFI status code
#define EFI_ERROR_MASK           0x8000000000000000
#define EFIERR(a)                (EFI_ERROR_MASK | a)
#define EFI_ERROR(status)        (((long long)status) < 0)
#define EFIAPI                   __attribute__((ms_abi))
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
#define PT_LOAD 1

// UEFI file code
#define EFI_FILE_MODE_READ_ONLY  0x00000001
#define EFI_READ_ONLY  EFI_FILE_MODE_READ_ONLY
#define EFI_FILE_MODE_READ   0x0000000000000001
#define EFI_FILE_MODE_WRITE  0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

// view X and Y code
#define X 1024
#define Y 768

// memory code
#define FREE_MEMORY 1
#define MMIO_MEMORY 2
#define UEFI_MEMORY 3

// UEFI protocol code
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL        0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL       0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER           0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE           0x00000020


// max and min
#define min(a, b)                ((a) < (b) ? (a) : (b))
#define max(a, b)                ((a) < (b) ? (b) : (a))

// UEFI allocate type
enum EFI_ALLOCATE_TYPE 
{
  AllocateAnyPages,
  AllocateMaxAddress,
  AllocateAddress,
  MaxAllocateType
};

// UEFI pixel
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

// UEFI memory type
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
    uintn MapSize;
    void *Buffer;
    uintn MapKey;
    uintn DescriptorSize;
    uintn DescriptorVersion;
} MEMORY_MAP;

typedef struct 
{
	uint32 Type;
	uint64 PhysicalStart;
	uint64 PageSize;
} OS_MEMORY_DESCRIPTOR;

// boot config struct
typedef struct
{
    MEMORY_MAP MemoryMap;
} BOOT_CONFIG;



struct EFI_INPUT_KEY 
{
    uint16 ScanCode;
    char16 UnicodeChar;
};

struct EFI_KEY_DATA 
{
    uint16 Key;
    uint16 KeyShiftState;
    boolean KeyToggleState;
};


struct EFI_GUID 
{
    uint32 Data1;
    uint16 Data2;
    uint16 Data3;
    uint8  Data4[8];
};

// UEFI memory struct
typedef struct 
{
  uint32 Type;
  EFI_PHYSICAL_ADDRESS PhysicalStart;
  EFI_VIRTUAL_ADDRESS VirtualStart;
  uint64 NumberOfPages;
  uint64 Attribute;
}  __attribute__((__aligned__(16))) EFI_MEMORY_DESCRIPTOR;

struct FrameBufferConfig 
{
    uint8 *frame_buffer;
    uint32 pixels_per_scan_line;
    uint32 horizontal_resolution;
    uint32 vertical_resolution;
    enum PixelFormat pixel_format;
};

// UEFI boot services
struct EFI_BOOT_SERVICES 
{
    char _buf1[24];

    uintn _buf2[2];

    EFIAPI EFI_STATUS(*AllocatePages)(enum EFI_ALLOCATE_TYPE Type, enum EFI_MEMORY_TYPE MemoryType, uintn Pages,EFI_PHYSICAL_ADDRESS *Memory);
    EFIAPI EFI_STATUS (*FreePages)(EFI_PHYSICAL_ADDRESS Memory, uintn Pages);
    EFIAPI EFI_STATUS (*GetMemoryMap)(uintn *MemoryMapSize, EFI_MEMORY_DESCRIPTOR *MemoryMap,uintn *MapKey, uintn *DescriptorSize, uint32 *DescriptorVersion);
    EFIAPI EFI_STATUS (*AllocatePool)(enum EFI_MEMORY_TYPE PoolType, uintn Size, void **Buffer);
    EFIAPI EFI_STATUS (*FreePool)(VOID *Buffer);

    uintn _buf4[2];
    EFIAPI EFI_STATUS (*WaitForEvent)(uintn NumberOfEvents, EFI_EVENT *Event, uintn *Index);
    uintn _buf4_2[3];

    uintn _buf5[9];

    uintn _buf6[5];

    uintn  _buf7[2];
    EFIAPI EFI_STATUS (*SetWatchdogTimer)(uintn Timeout, uint64 WatchdogCode, uintn DataSize,char16 *WatchdogData);

    uintn _buf8[2];

    EFIAPI
    EFI_STATUS(*OpenProtocol)
    (EFI_HANDLE Handle, struct EFI_GUID *Protocol, VOID **Interface, EFI_HANDLE AgentHandle,
    EFI_HANDLE ControllerHandle, uint32 Attributes);
    uintn _buf9[2];

    uintn _buf10[2];
    EFIAPI EFI_STATUS (*LocateProtocol)(struct EFI_GUID *Protocol, VOID *Registration, VOID **Interface);
    uintn _buf10_2[2];

    uintn _buf11;

    uintn _buf12[3];
};

struct EFI_SYSTEM_TABLE 
{
    char _buf1[44];
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL 
    {
        uintn     Reset;
        EFIAPI    EFI_STATUS (*ReadKeyStroke)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,struct EFI_INPUT_KEY                  *Key);
        EFI_EVENT WaitForKey;
    }  *ConIn;
    uintn _buf2;
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL 
    {
        unsigned long long (*SetAttribute)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,unsigned long long Attribute);
        uintn _buf;
        EFIAPI EFI_STATUS (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, char16 *String);
        uintn  _buf2[4];
        EFIAPI EFI_STATUS (*ClearScreen)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    }   *ConOut;
    uintn   _buf3[3];
    struct EFI_BOOT_SERVICES *BootServices;
};

struct EFI_SIMPLE_POINTER_STATE 
{
    int32 RelativeMovementX;
    int32 RelativeMovementY;
    int32 RelativeMovementZ;
    boolean LeftButton;
    boolean RightButton;
};

struct EFI_SIMPLE_POINTER_PROTOCOL 
{
    EFIAPI EFI_STATUS (*Reset)(struct EFI_SIMPLE_POINTER_PROTOCOL *This,unsigned char ExtendedVerification);
    EFIAPI EFI_STATUS (*GetState)(struct EFI_SIMPLE_POINTER_PROTOCOL *This,struct EFI_SIMPLE_POINTER_STATE *State);
    void *WaitForInput;
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
    uint32 Version;
    uint32 HorizontalResolution;
    uint32 VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    uint32 PixelInformation[4];
    uint32 PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct 
{
    uint32 MaxMode;
    uint32 Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    uintn SizeOfInfo;
    uintn FrameBufferBase;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL 
{
    EFIAPI EFI_STATUS (*QueryMode)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, unsigned int ModeNumber, unsigned long long *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);

    EFIAPI EFI_STATUS (*SetMode)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, unsigned int ModeNumber);

    uintn pad;

    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL 
{
    unsigned long long (*Reset)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,unsigned char ExtendedVerification);
    unsigned long long (*ReadKeyStrokeEx)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,struct EFI_KEY_DATA *KeyData);
    void *WaitForKeyEx;
    unsigned long long (*SetState)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,unsigned char *KeyToggleState);
    unsigned long long (*RegisterKeyNotify)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,struct EFI_KEY_DATA *KeyData,unsigned long long (*KeyNotificationFunction)(struct EFI_KEY_DATA *KeyData),void **NotifyHandle);
    unsigned long long (*UnregisterKeyNotify)(struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *This,void *NotificationHandle);
};

struct EFI_LOADED_IMAGE_PROTOCOL 
{
    uint32                   Revision;
    EFI_HANDLE               ParentHandle;
    struct EFI_SYSTEM_TABLE *SystemTable;

    EFI_HANDLE DeviceHandle;
    void *FilePath;
    void *Reserved;

    uint32 LoadOptionsSize;
    void  *LoadOptions;

    void                *ImageBase;
    uint64               ImageSize;
    enum EFI_MEMORY_TYPE ImageCodeType;
    enum EFI_MEMORY_TYPE ImageDataType;
    EFIAPI               EFI_STATUS (*Unload)(EFI_HANDLE ImageHandle);
};

struct EFI_FILE_INFO
{
    unsigned char _buf[80];
    char16        FileName[];
};

struct EFI_FILE_PROTOCOL 
{
    uintn Revision;
    EFIAPI EFI_STATUS(*Open)(struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_PROTOCOL **NewHandle, char16 *FileName,uint64 OpenMode, uint64 Attributes);
    EFIAPI EFI_STATUS (*Close)(struct EFI_FILE_PROTOCOL *This);
    uintn  _buf2;
    EFIAPI EFI_STATUS (*Read)(struct EFI_FILE_PROTOCOL *This, uintn *BufferSize, VOID *Buffer);
    EFIAPI EFI_STATUS (*Write)(struct EFI_FILE_PROTOCOL *This, uintn *BufferSize, VOID *Buffer);
    uintn _buf3[4];
    EFIAPI EFI_STATUS (*Flush)(struct EFI_FILE_PROTOCOL *This);
};
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL 
{
    uint64 Revision;
    EFIAPI EFI_STATUS (*OpenVolume)(struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,struct EFI_FILE_PROTOCOL **Root);
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static void xmemset(void *dst_, uint8 value, uintn size) 
{
    uint8 *dst = (uint8 *)dst_;
    while (size-- > 0)
    {
        *dst++ = value;
    }
}

static void *xmemcpy(void *dst_, const void *src_, uintn size) 
{
    uint8       *dst = (uint8 *)dst_;
    const uint8 *src = (uint8 *)src_;
    while (size-- > 0)
    {
        *dst++ = *src++;
    }
    return (void *)src_;
}


#pragma GCC diagnostic pop
#endif // INCLUDES_FIRMWARE_UEFI_HPP_