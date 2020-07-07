# Questions

## What's `stdint.h`?

stdint.h is a header file who's purpose is to define and differentiate between the different types of 'exact-width' integers. The file sets the parameters (these being the lowest accepted value to highest accepted value) for both signed and unsigned integers of 8 bit size through to 64 bit.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Supporting different types of integer allows for efficient allocation of memory. You wouldn't use a uint32_t (4 bytes of memory) for a number that only requires 1 byte.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

'BYTE': 1 byte
'DWORD': 4 bytes
'LONG': 4 bytes
'WORD': 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII: 'B M'
Decimal: '66 77'
Hexadecimal: 42 4D'
This specifies the filetype

## What's the difference between `bfSize` and `biSize`?

'bfSize' defines the total size of the file in bytes.
'biSize' defines the number of bytes required for the structure.

## What does it mean if `biHeight` is negative?

If 'biHeight' is negative, it means the bitmap is structured from top-down with it's origin in the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

It would return 'NULL' if intpr location is either empty or doesn't contain compatible data.

## Why is the third argument to `fread` always `1` in our code?

The thrid argument '1' states that fread only read the specified amount of data once.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

It would assign a value of '3'.

## What does `fseek` do?

'fseek' allows the 'file pointer' to skip a specified distance from a given position in the file e.g. beginning/current position/end.
In this example it says that, if there is a buffer, skip over it so it doens't atempt to read/write empty metadata.

## What is `SEEK_CUR`?

'SEEK_CUR' tells fseek to jump the given distance (in this instance, the buffer) from the file pointer's CURRENT POSITION.

## Whodunit?

It was professor plum with the candlestick in the library
