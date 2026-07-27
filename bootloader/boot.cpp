import PnuemaOS.BIOSf;

__attribute__((section(".text"))) auto _start() -> void {
  PnuemaOS::BIOSf::print("Hello World!");
  __asm__ volatile("hlt");
}
