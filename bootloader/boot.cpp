import PnuemaOS.BIOSf;
__attribute__((section(".text"))) void _start() {
  PnuemaOS::BIOSf::print("Hello World");
  __asm__ volatile("hlt");
}
