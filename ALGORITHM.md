# Algorithm used in Kompreshar
Note: This algorithm probably exists somewhere already, under a different name.

## Overview

This algorithm reduces file size by encoding unique characters with a variable-length bit representation, instead of the standard 8-bit ASCII encoding.

- Identify the number of unique characters (*n*) and total characters in the input file 
- Determine the minimum number of bits required to represent each unique character. It can be shown that the number is *ceil(log2(n))*
- Replace each character in the input text with its corresponding compressed representation.
- **The effectiveness of this compression increases when the number of unique characters is small and the file size is large.**

## Compression Process

The compressed file is stored in binary format, structured as follows:

- **Header/ Metadata**:
  - The **first byte** stores the number of unique characters (*n*).
  - The **next 4 bytes** store the number of total characters (32 bit integer).
  - The **next n bytes** (each byte representing an 8-bit ASCII value) store the unique characters, sorted in ascending order.
- **Compressed Data**
  - Each character from the original text is encoded using *ceil(log2(n))* bits instead of the standard 8 bits.

### Sample Input
```
cse paina public versity te aaaaaaaaaaaaaaaaaaaaa
```
- Unique characters: 15
- Size: 49 bytes

### Compressed Representation (newlines added for clarity)
```
15
0 0 0 49
32 97 98 99 101 105 108 110 112 114 115 116 117 118 121
58 64 129 87 16 140 38 83 13 73 165 190 11 64 17 17 17 17 17 17 17 17 17 17 16 
```
- The **first byte**, *15*, is the number of the unique characters.
- The **next 4 bytes** represent the number of total characters in binary format (`00000000 00000000 00000000 00110001` = *49*)
- The **next *15* bytes** are the ASCII values of the unique characters, stored in increasing order: `[ ' ',  'a', 'b', 'c', 'e', 'i', 'l', 'n', 'p', 'r', 's', 't', 'u', 'v', 'y' ]`
- **Character Encoding:**
  - *ceil(log2(15)) = 4* bits are enough to represent 15 unique characters.
  - The next *(4 x 49) = 196* bits store the compressed data

### Compression Efficiency
- Original size: *49* bytes
- Compressed size: *45* bytes
- **Compression is more effective when the input has fewer unique characters and more repetitions.**


## Decompression

The decompression process reverses the compression steps:

- Read the **first byte** to determine the number of unique characters (*n*).
- Read the **next 4 bytes** to determine the number of total characters.
- Read the **next *n* bytes** to reconstruct the unique character set.
- Read the rest of the file in *ceil(log2(n))*-bit chunks to decode the original text.
- Convert each chunk back into its corresponding ASCII character using the stored dictionary.

## Summary

- Advantages:
  - Reduces file size when input has a low number of unique characters.
  - Simple to implement with straightforward bit manipulation.

- Limitations:
  - Not efficient for text with many unique characters for increased bit-length.
  - May increase file size if the number of unique characters is large (more than 128).
