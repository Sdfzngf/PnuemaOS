module;

export module PnuemaOS.BIOSf;

export namespace PnuemaOS::BIOSf {
auto VGA_ADDRESS = reinterpret_cast<char *>(0xB8000);
auto print(const char *msg) -> void {
  int i(0);
  while (*msg) {
    VGA_ADDRESS[i] = *msg;
    VGA_ADDRESS[i + 1] = 0x04;
    msg++;
    i += 2;
  }
}
} // namespace PnuemaOS::BIOSf
