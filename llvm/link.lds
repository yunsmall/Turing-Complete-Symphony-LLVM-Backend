SECTIONS
{
    .text 0x0000:
    {
        _start = .;
        KEEP(*(.text.startup))
        *(.text)
        *(.text.*)
    }

    .data 0x8000:
    {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}
