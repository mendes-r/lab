# NOTES

## The ELF Format - Inspection

### ELF Executable header

Definition of ELF64\_Ehdr in _/usr/include/elf.h_:

```c
typedef struct {
    unsigned char e_ident[16];  /* Magic number and other info       */
    uint16_t    e_type;         /* Object file type                  */
    uint16_t    e_machine;      /* Architecture                      */
    uint32_t    e_version;      /* Object file version               */
    uint64_t    e_entry;        /* Entry point virtual address       */
    uint64_t    e_phoff;        /* Programm header table file offset */
    uint64_t    e_shoff;        /* Section header table file offset  */
    uint32_t    e_flags;        /* Processsor specific flags         */
    uint16_t    e_ehsize;       /* ELF header size in bytes          */
    uint16_t    e_phentsize;    /* Program header table entry size   */
    uint16_t    e_phnum;        /* Program header table entry count  */
    uint16_t    e_shentsize     /* Section header table entry size   */
    uint16_t    e_shnum;        /* Section header table entry count  */
    uint16_t    e_shstrndx;     /* Section header string table index */
} Elf64_Ehdr
```

```sh
$ readelf -h ls
```

ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x6d30
  Start of program headers:          64 (bytes into file)
  Start of section headers:          139864 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         32
  Section header string table index: 31


Looking at the _ls_ hex with __xxd__ hex viewer:

```sh
$ xxd ls | head -n 30
```

``` [16 bytes] e_ident ELF ```
00000000: 7f45 4c46 0201 0100 0000 0000 0000 0000  .ELF............ 
``` [2 bytes] e_type ET_DYN 3 Shared object file ```
00000010: 0300 
``` [2 bytes] e_machine EM_X86_64 62 = 0x3e AMD x86-64 architecture ```
               3e00 
``` [4 bytes] e_version EV_CURRENT 1 Current version ```
                    0100 0000 
``` [8 bytes] e_entry 0x6d30 ```
                              306d 0000 0000 0000  ..>.....0m...... 
``` [8 bytes] e_phoff 64 = 0x40 ```
00000020: 4000 0000 0000 0000 
``` [8 bytes] e_shoff 139864 = 0x022258 ```
                              5822 0200 0000 0000  @.......X"......
``` [4 bytes] e_flag ```
00000030: 0000 0000 
``` [2 bytes] e_ehsize 64 = 0x40 ```
                    4000 
``` [2 bytes] e_phentsize 56 = 0x38 ```
                         3800 
``` [2 bytes] e_phum 13 = 0x0d ```
                              0d00
``` [2 bytes] e_shentsize 64 = 0x40 ```
                                   4000 
``` [2 bytes] e_shnum 32 = ox20 ```
                                        2000
``` [2 bytes] e_shstrndxv 31 = 0x1f
                                             1f00  ....@.8...@. ...
00000040: 0600 0000 0400 0000 4000 0000 0000 0000  ........@.......
00000050: 4000 0000 0000 0000 4000 0000 0000 0000  @.......@.......
00000060: d802 0000 0000 0000 d802 0000 0000 0000  ................
00000070: 0800 0000 0000 0000 0300 0000 0400 0000  ................
00000080: 1803 0000 0000 0000 1803 0000 0000 0000  ................
00000090: 1803 0000 0000 0000 1c00 0000 0000 0000  ................
000000a0: 1c00 0000 0000 0000 0100 0000 0000 0000  ................

