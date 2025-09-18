/* ENTRY(_start) */

SECTIONS
{
    . = 0x0000;
    .text :
    {
        /* _start = .; */
        KEEP(*(.text._start))
        KEEP(*(.text.startup))
        *(.text)
        *(.text.*)
    }
    . = 0x8000;
    .data :
    {
        *(.data)
        *(.data.*)
    }

    .bss : {
        *(.bss)
        *(.bss.*)
    }
}
