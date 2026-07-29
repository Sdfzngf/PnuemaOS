import PnuemaOS.BIOSf;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;

struct __attribute__((packed)) DAP {
  uint8_t size;
  uint8_t reserved;
  uint16_t count;
  uint16_t offset;
  uint16_t segment;
  unsigned int lba_low;
  unsigned int lba_high;
};

enum class DPT_BOOTFLAG : uint8_t { ACTIVE = 0x80, UNACTIVE = 0x00 };

enum class PARTITION_TYPE : uint8_t {
  EMPTY = 0x00,
  FAT12 = 0x01,
  FAT16_S32 = 0x04,
  EXTENDED = 0x05,
  FAT16_L32 = 0x06,
  NTFS = 0x07,
  WIN95FAT32 = 0x0B,
  WIN95FAT32_LBA = 0x0C,
  WIN95FAT16_LBA = 0x0F,
  WIN95EXT_LBA = 0x0F,
  LINUX_SWAP = 0x82,
  LINUX_NATIVE = 0x83,
  LINUX_EXT = 0x85,
  GPT_P = 0xEE
};

struct __attribute__((packed)) _DPT {
  DPT_BOOTFLAG flag = DPT_BOOTFLAG::ACTIVE;
  uint8_t start_head = 0x00;
  uint8_t start_sector = 0x01;
  uint8_t start_cyl = 0x00;
  PARTITION_TYPE type = PARTITION_TYPE::NTFS;
  uint8_t end_head = 0xFE;
  uint8_t end_sector = 0xFF;
  uint8_t end_cyl = 0xFF;
  unsigned int start_lba = 0x00000001;
  unsigned int total_sectors = 0xAABBCCDD;
};

__attribute__((section(".sig2"))) _DPT dpt[4] = {
    {

        .flag = DPT_BOOTFLAG::ACTIVE,
        .start_head = 0x01,
        .start_sector = 0x01,
        .start_cyl = 0x00,
        .type = PARTITION_TYPE::FAT16_S32,
        .end_head = 0xFE,
        .end_sector = 0xFF,
        .end_cyl = 0xFF,
        .start_lba = 0x00'00'00'01,
        .total_sectors = 0x00'01'00'00

    },
    {

        .flag = DPT_BOOTFLAG::UNACTIVE,
        .start_head = 0x00,
        .start_sector = 0x00,
        .start_cyl = 0x00,
        .type = PARTITION_TYPE::EMPTY,
        .end_head = 0x00,
        .end_sector = 0x00,
        .end_cyl = 0x00,
        .start_lba = 0x00'00'00'00,
        .total_sectors = 0x00'00'00'00

    },
    {

        .flag = DPT_BOOTFLAG::UNACTIVE,
        .start_head = 0x00,
        .start_sector = 0x00,
        .start_cyl = 0x00,
        .type = PARTITION_TYPE::EMPTY,
        .end_head = 0x00,
        .end_sector = 0x00,
        .end_cyl = 0x00,
        .start_lba = 0x00'00'00'00,
        .total_sectors = 0x00'00'00'00

    },
    {

        .flag = DPT_BOOTFLAG::UNACTIVE,
        .start_head = 0x00,
        .start_sector = 0x00,
        .start_cyl = 0x00,
        .type = PARTITION_TYPE::EMPTY,
        .end_head = 0x00,
        .end_sector = 0x00,
        .end_cyl = 0x00,
        .start_lba = 0x00'00'00'00,
        .total_sectors = 0xDD'CC'BB'AA

    }};

__attribute__((section(".data"))) static bool relocated = false;

__attribute__((section(".text"))) auto _start() -> void {
  __asm__ volatile("xorw %%ax, %%ax\n"
                   "movw %%ax, %%ds\n"
                   "movw %%ax, %%es\n"
                   "movw %%ax, %%ss\n"
                   "movw $0x7C00, %%sp\n"
                   "cld"
                   :
                   :
                   : "ax", "memory");
  PnuemaOS::BIOSf::put('P');
  if (!relocated) {
    PnuemaOS::BIOSf::put('R');
    relocated = true;
    __asm__ volatile("movw $0x7C00, %%si\n"    // 源地址
                     "movw $0x0600, %%di\n"    // 目标地址
                     "movw $0x0100, %%cx\n"    // 512 字节 = 256 个字
                     "rep movsw\n"             // 复制
                     "ljmp $0x0000, $0x0600\n" // 远跳转到新地址
                     :
                     :
                     : "si", "di", "cx", "memory");
  }
  _DPT *active = nullptr;
  for (char i = 0; i < 4; ++i) {
    if (dpt[i].flag == DPT_BOOTFLAG::ACTIVE) {
      PnuemaOS::BIOSf::put('C');
      active = &dpt[i];
      break;
    }
  }
  DAP dap = {.size = 0x10,
             .reserved = 0,
             .count = 1,
             .offset = 0x7C00,
             .segment = 0x0000,
             .lba_low = active->start_lba,
             .lba_high = 0};
  if (!active) {
    PnuemaOS::BIOSf::put('1');
    goto fail;
  }
  uint8_t result;
  __asm__ volatile("movb $0x42, %%ah\n"
                   "movb $0x80, %%dl\n"
                   "movw %1, %%si\n"
                   "int $0x13\n"
                   "setc %0"
                   : "=r"(result)
                   : "r"((uint16_t)((int)&dap))
                   : "ax", "dx", "si", "memory");
  if (result) {
    PnuemaOS::BIOSf::put('2');
    goto fail;
  }
  PnuemaOS::BIOSf::put('\n');
  PnuemaOS::BIOSf::put('\r');

  __asm__ volatile("ljmp $0x0000, $0x7C00");
fail:
  goto fail;
}
