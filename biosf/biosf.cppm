module;

export module PnuemaOS.BIOSf;

export namespace PnuemaOS::BIOSf {
void print(const char* msg) {
  for (int i = 0; msg[i]; i++) {
    __asm__ volatile("int $0x10"
                     :
                     : "a"((0x0E << 8) | msg[i]), "b"(0x0007)
                     : "cc", "memory");
  }
}
} // namespace PnuemaOS::BIOSf
