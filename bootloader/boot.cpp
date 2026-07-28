import PnuemaOS.BIOSf;

typedef unsigned char uint8_t;

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
  uint8_t start_head = 0x01;
  uint8_t start_sector = 0x01;
  uint8_t start_cyl = 0x00;
  PARTITION_TYPE type = PARTITION_TYPE::NTFS;
  uint8_t end_head = 0xFE;
  uint8_t end_sector = 0xFF;
  uint8_t end_cyl = 0xFF;
  unsigned int start_lba = 0x0000003F;
  unsigned int total_sectors = 0xAABBCCDD;
};

__attribute__((section(".text"))) auto _start() -> void {
  PnuemaOS::BIOSf::print("Hello World!");
  __asm__ volatile("hlt");
}
__attribute__((section(".sig2"))) _DPT dpt[4] = {
    {

        .flag = DPT_BOOTFLAG::ACTIVE,
        .start_head = 0x01,
        .start_sector = 0x01,
        .start_cyl = 0x00,
        .type = PARTITION_TYPE::EMPTY,
        .end_head = 0xFE,
        .end_sector = 0xFF,
        .end_cyl = 0xFF,
        .start_lba = 0x00'00'00'3F,
        .total_sectors = 0xAA'BB'CC'DD

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
        .total_sectors = 0x00'00'00'00

    }};
