import PnuemaOS.BIOSf;
__attribute__((section(".text"))) void _start() {
  PnuemaOS::BIOSf::test();
  __asm__ volatile("hlt");
}
