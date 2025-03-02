# Kompreshar
Kompreshar is a stupidly simple, lossless text compression and decompression tool.

The name comes from "kom preshar" (কম প্রেশার) in Bengali, which means "low pressure".

### Build and Run
```
mkdir build
cd build
cmake ..
cmake --build .
./kompreshar
```

### Algorithm
Kompreshar uses a unique character encoding scheme to reduce file size. See [ALGORITHM.md](ALGORITHM.md)
