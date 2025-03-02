#include "KPCompressor.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <algorithm>

std::string KPCompressor::read_file(const std::string& filepath, bool binary_mode) {
  std::ifstream file(filepath, binary_mode ? std::ios::binary : std::ios::in);
  if (!file) {
    std::cerr << "Failed to open file: " << filepath << std::endl;
    return "";
  }

  return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

bool KPCompressor::write_file(const std::string& filepath,
  const std::vector<uint8_t>& data) {
  std::ofstream file(filepath, std::ios::binary);
  if (!file) {
    std::cerr << "Failed to write to file: " << filepath << std::endl;
    return false;
  }

  file.write(reinterpret_cast<const char*>(data.data()), data.size());
  return true;
}

void KPCompressor::compress_file(std::string& filepath) {
  std::string data = read_file(filepath, true);
  if (data.empty()) {
    std::cerr << "No data was read from " << filepath << std::endl;
    return;
  }

  std::vector<uint8_t> compressed_bin_data = compress(data);
  std::string output_filename = filepath + ".rle";
  if (write_file(output_filename, compressed_bin_data)) {
    std::cout << "Compressed file saved as " << output_filename << std::endl;
  }
}

void KPCompressor::decompress_file(std::string& filepath) {
  std::string data = read_file(filepath, true);
  if (data.empty()) {
    std::cerr << "No data was read from " << filepath << std::endl;
    return;
  }

  std::vector<uint8_t> bin_data(data.begin(), data.end());
  std::string decompressed_data_str = decompress(bin_data);
  std::string output_filename = filepath.substr(0, filepath.find(".rle")) + "_decompressed.txt";

  std::ofstream output_file(output_filename);
  if (!output_file) {
    std::cerr << "Failed to open file for writing: " << output_filename << std::endl;
    return;
  }
    
  output_file << decompressed_data_str;
  std::cout << "Decompressed file saved as " << output_filename << std::endl;
}

int KPCompressor::binary_str_to_int(const std::string& binary_str) {
  int value = 0;
  for (char ch : binary_str) {
    value = (value << 1) | (ch == '1' ? 1 : 0);
  }
  return value;
}

std::string KPCompressor::binary_to_str(const std::vector<uint8_t>& bin_data, size_t& offset, int bits) {
  std::string binary_str;
  binary_str.reserve(bits);
  for (int i = 0; i < bits; ++i) {
    if (offset >= bin_data.size() * 8) {
      break;
    }
    uint8_t byte = bin_data[offset / 8];
    int bit_pos = 7 - (offset % 8);
    binary_str += ((byte >> bit_pos) & 1) ? '1' : '0';
    offset++;
  }
  return binary_str;
}

std::string KPCompressor::int_to_binary_str(int n, int bufsize) {
  std::string output;
  output.reserve(bufsize);
  for (int i = bufsize - 1; i >= 0; --i) {
    output += ((n >> i) & 1) ? '1' : '0';
  }
  return output;
}

std::vector<uint8_t> KPCompressor::compress(std::string& data) {
  std::set<char> unique_char(data.begin(), data.end());
  int unique_char_cnt = unique_char.size();
  int bufsize = ceil(log2(unique_char_cnt));

  std::map<char, std::string> char_map;
  int current_ch = 0;
  for (auto ch : unique_char) {
    char_map[ch] = int_to_binary_str(current_ch++, bufsize);
  }

  std::string compressed_str;
  compressed_str += int_to_binary_str(unique_char_cnt, 8);
  for (char ch : unique_char) {
    compressed_str += int_to_binary_str(ch, sizeof(ch) * 8);
  }
  for (char ch : data) {
    compressed_str += char_map[ch];
  }

  std::vector<uint8_t> compressed_bytes;
  for (size_t i = 0; i < compressed_str.size(); i += 8) {
    std::string byte_str = compressed_str.substr(i, 8);
    uint8_t byte = 0;
    for (size_t j = 0; j < byte_str.size(); ++j) {
      if (byte_str[j] == '1') {
        byte |= (1 << (7 - j));
      }
    }
    compressed_bytes.push_back(byte);
  }

  return compressed_bytes;
}

std::string KPCompressor::decompress(const std::vector<uint8_t>& bin_data) {
  size_t offset = 0;

  std::string unique_char_cnt_str = binary_to_str(bin_data, offset, 8);
  int unique_char_cnt = binary_str_to_int(unique_char_cnt_str);
  int bufsize = ceil(log2(unique_char_cnt));

  std::map<std::string, char> binary_to_char_map;
  for (int i = 0; i < unique_char_cnt; ++i) {
    std::string char_binary_str = binary_to_str(bin_data, offset, 8);
    char ch = static_cast<char>(binary_str_to_int(char_binary_str));
    std::string binary_code = int_to_binary_str(i, bufsize);
    binary_to_char_map[binary_code] = ch;
  }

  std::string decompressed_data_str;
  while (offset < bin_data.size() * 8) {
    std::string binary_code = binary_to_str(bin_data, offset, bufsize);
    if (binary_to_char_map.find(binary_code) != binary_to_char_map.end()) {
      decompressed_data_str += binary_to_char_map[binary_code];
    } else {
      std::cerr << "Invalid binary code encountered during decompression." << std::endl;
      break;
    }
  }

  return decompressed_data_str;
}
