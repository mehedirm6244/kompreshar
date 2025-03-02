# Algorithm used in Kompreshar
Note: This algorithm probably exists somewhere already, under a different name.

## Overview

This algorithm reduces file size by encoding unique characters with a variable-length bit representation, instead of the standard 8-bit ASCII encoding.

- Identify the number of unique characters in the input file (*n*)
- Determine the minimum number of bits required to represent each unique character. It can be shown that the number is *ceil(log2(n))*
- Replace each character in the input text with its corresponding compressed representation.
- **The effectiveness of this compression increases when the number of unique characters is small and the file size is large.**

## Compression Process

The compressed file is stored in binary format, structured as follows:

- Header/ Metadata:
  - The **first 8 bits** store the number of unique characters (*n*).
  - The **next n bytes** (*n × 8* bits) store the ASCII values of the unique characters, sorted in ascending order.
- Compressed Data
  - Each character from the original text is encoded using *ceil(log2(n))* bits instead of the standard 8 bits.

### Sample Input
```
cse paina public versity te aaaaaaaaaaaaaaaaaaaaa
```
- Unique characters: 15
- Size: 49 bytes

### Compressed Binary Represantation (newlines added for clarity)
```
00001111
00100000
01100001
01100010
01100011
01100101
01101001
01101100
01101110
01110000
01110010
01110011
01110100
01110101
01110110
01111001
0011101001000000100000010101011100010000100011000010011001010011000011010100100110100101101111100000101101000000000100010001000100010001000100010001000100010001000100010001000100010001000100010001
```
- The first 8 bits (`00001111`) = *15* is the number of the unique characters.
- Next *15* bytes are the  The ASCII values of the unique characters, stored in increasing order: `[ ' ',  'a', 'b', 'c', 'e', 'i', 'l', 'n', 'p', 'r', 's', 't', 'u', 'v', 'y' ]`
- **Character Encoding:**
  - *ceil(log2(15)) = 4* bits are enough to represent 15 unique characters.
  - The next *(4 x 49) = 196* bits store the compressed data

### Compression Effeciency
- Original size: *49* bytes
- Compressed size: *41* bytes
- Compression is more effective when the input has fewer unique characters and more repetitions.


## Decompression

The decompression process reverses the compression steps:

- Read the first *8* bits to determine the number of unique characters (*n*).
- Read the next *n × 8* bits to reconstruct the unique character set.
- Read the rest of the file in *ceil(log2(15))*-bit chunks to decode the original text.
- Convert each chunk back into its corresponding ASCII character using the stored dictionary.

## Summary

- Advantages:
  - Reduces file size when input has a low number of unique characters.
  - Simple to implement with straightforward bit manipulation.

- Limitations:
  - Not efficient for text with many unique characters for increased bit-length.
  - May increase file size if the number of unique characters is large (more than 128).
