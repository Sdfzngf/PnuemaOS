OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
SECTIONS
{
    . = 0x7C00;
    .text : {
        *(.text*)
    }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    . = 0x7DBE;
    .sig2 : SUBALIGN(1) {
        /*SHORT(0x0180)*/
        *(.sig2*)
    }
    . = 0x7DFE;
    .sig : {
        SHORT(0xAA55)
    }

    ASSERT( . <= 0x7E00, "Error: Image too large!" )
}
