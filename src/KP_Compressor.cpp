/**
 * This file is from Kompreshar - a lossless text compression tool.
 * Copyright (C) 2025 Mehedi Rahman Mahi
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <kompreshar/KP_Compressor.hpp>

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>

std::string KP_Compressor::read_file(const std::string& filepath, bool binary_mode) {
  std::ifstream file(filepath, binary_mode ? std::ios::binary : std::ios::in);
  if (!file) {
    std::cerr << "Failed to open file: " << filepath << std::endl;
    return "";
  }

  return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}

bool KP_Compressor::write_file(const std::string& filepath,
  const std::vector<uint8_t>& data) {
  std::ofstream file(filepath, std::ios::binary);
  if (!file) {
    std::cerr << "Failed to write to file: " << filepath << std::endl;
    return false;
  }

  file.write(reinterpret_cast<const char*>(data.data()), data.size());
  return true;
}

bool KP_Compressor::compress_file(std::string& filepath) {
  std::string data = read_file(filepath, true);
  if (data.empty()) {
    std::cerr << "No data was read from " << filepath << std::endl;
    return 0;
  }

  std::vector<uint8_t> compressed_data = compress(data);
  std::string output_filename = filepath + ".kpc";

  if (write_file(output_filename, compressed_data)) {
    std::cout << "Compressed file saved as " << output_filename << std::endl;
    return 1;
  }
  return 0;
}

bool KP_Compressor::decompress_file(std::string& filepath) {
  std::string data = read_file(filepath, true);
  if (data.empty()) {
    std::cerr << "No data was read from " << filepath << std::endl;
    return 0;
  }

  std::vector<uint8_t> bin_data(data.begin(), data.end());
  std::string decompressed_data = decompress(bin_data);
  std::string output_filename = filepath.substr(0, filepath.find(".kpc")) + "_decompressed.txt";

  if (write_file(output_filename,
    std::vector<uint8_t>(decompressed_data.begin(), decompressed_data.end()))) {
    std::cout << "Decompressed file saved as " << output_filename << std::endl;
    return 1;
  }
  return 0;
}

/**
 * Refer to the following link for detailed explanation about the algorithm:
 * https://github.com/mehedirm6244/kompreshar/blob/main/ALGORITHM.md#compression-process
 */
std::vector<uint8_t> KP_Compressor::compress(std::string& data) {
  std::set<char> unique_chars(data.begin(), data.end());
  int unique_char_cnt = unique_chars.size();

  // Maximum number of bits required to represent each unique character
  int bit_size = std::max((int)(ceil(log2(unique_char_cnt))), 1);

  // Create a mapping from each unique character to a unique index
  std::map<char, int> char_map;
  int current_ch_idx = 0;
  for (auto ch : unique_chars) {
    char_map[ch] = current_ch_idx++;
  }

  /**
   * Calculate the size of the compressed data (vector) in bytes
   * - 1 byte for the number of unique characters
   * - `unique_char_cnt` bytes for the unique characters themselves
   * - `data.size() * bit_size` bits for the encoded data
   */
  int compressed_data_size = (1 + unique_char_cnt) * 8 + data.size() * bit_size; // By bits
  compressed_data_size = ceil(compressed_data_size / 8.0); // By bytes
  std::vector<uint8_t> compressed_data(compressed_data_size, 0);

  compressed_data[0] = static_cast<uint8_t>(unique_char_cnt);
  current_ch_idx = 1;
  for (auto ch : unique_chars) {
    compressed_data[current_ch_idx++] = ch;
  }

  int compressed_vec_idx = current_ch_idx;
  int bit_pos = 0; // Current bit position within a byte

  for (char ch : data) {
    int encoded_value = char_map[ch];

    // Write the encoded value into the compressed data using `bit_size` bits
    for (int i = bit_size - 1; i >= 0; i--) {
      if ((encoded_value >> i) & 1) {
        compressed_data[compressed_vec_idx] |= (1 << (7 - bit_pos));
      }
      bit_pos++;
      if (bit_pos == 8) {
        // Move to the next byte if the byte is filled
        bit_pos = 0;
        compressed_vec_idx++;
      }
    }
  }

  return compressed_data;
}

/**
 * Refer to the following link for detailed explanation about the algorithm:
 * https://github.com/mehedirm6244/kompreshar/blob/main/ALGORITHM.md#decompression
 */
std::string KP_Compressor::decompress(const std::vector<uint8_t>& bin_data) {
  int unique_char_cnt = bin_data[0];

  // The number of bits used to represent each character during compression
  int bit_size = std::max((int)(ceil(log2(unique_char_cnt))), 1);

  std::map<int, char> char_map;
  for (int i = 1; i <= unique_char_cnt; i++) {
    char_map[i - 1] = static_cast<char>(bin_data[i]);
  }

  std::string decompressed_data;
  int bit_pos = 0; // Current bit position within a byte

  for (int i = unique_char_cnt + 1; i < bin_data.size(); ) {
    int compressed_code = 0;

    // Decode the next `bit_size` bits to get the compressed code
    for (int j = 0; j < bit_size; j++) {
      if (bit_pos == 8) {
        bit_pos = 0;
        i++;
      }
      compressed_code = (compressed_code << 1);
      if (bin_data[i] & (1 << (7 - bit_pos))) {
        compressed_code++;
      }
      bit_pos++;
    }

    if (char_map.find(compressed_code) != char_map.end()) {
      decompressed_data += char_map[compressed_code];
    } else {
      std::cerr << "Unrecognized compressed code: " << compressed_code << ". Ignoring...\n";
    }
  }

  return decompressed_data;
}
