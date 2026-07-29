module;

export module PnuemaOS.BIOSf;

export namespace PnuemaOS::BIOSf {
inline auto VGA_ADDRESS = reinterpret_cast<char *>(0xB8000);
inline auto print(const char *msg) -> void {
  int i(0);
  while (*msg) {
    VGA_ADDRESS[i] = *msg;
    VGA_ADDRESS[i + 1] = 0x04;
    msg++;
    i += 2;
  }
}
inline auto puts(const char *str) -> void {
  while (*str) {
    __asm__ volatile("movb $0x0E, %%ah\n"       // 功能号：写字符并移动光标
                     "movb %0, %%al\n"          // 要显示的字符
                     "int $0x10\n"              // 调用 BIOS 视频中断
                     :                          // 无输出
                     : "r"((unsigned char)*str) // 输入：字符
                     : "ah", "al", "memory"     // 破坏的寄存器
    );
    ++str;
  }
}
inline auto put(char ch) -> void {
  __asm__ volatile("movb $0x0E, %%ah\n"   // 功能号：写字符并移动光标
                   "movb %0, %%al\n"      // 要显示的字符
                   "int $0x10\n"          // 调用 BIOS 视频中断
                   :                      // 无输出
                   : "r"(ch)              // 输入：字符
                   : "ah", "al", "memory" // 破坏的寄存器
  );
}
} // namespace PnuemaOS::BIOSf
