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

#ifndef KP_COMPRESSOR_HPP
#define KP_COMPRESSOR_HPP

#include <string>
#include <vector>
#include <cstdint>

class KP_Compressor {
private:
  /**
   * Read the contents of a file from the given path
   * 
   * @param filepath: The path of the file to read
   * @param binary_mode: If true, the file is read in binary mode; otherwise, in text mode.
   * @return: The contents of the file as string
   */
  std::string read_file(const std::string& filepath, bool binary_mode);

  /**
   * Writes the given binary data to a file at the specified filepath.
   * 
   * @param filepath: The path to the file where the data will be written.
   * @param data: The binary data to write to the file.
   * @return: True if the file was written successfully, false otherwise. 
   */
  bool write_file(const std::string& filepath, const std::vector<uint8_t>& data);

  /**
   * Compresses the file at the given filepath and saves the compressed
   * data to a new file with a `.kpc` extension.
   * 
   * @param data: The filepath of the file to compress.
   * @return: True if the compression was successful, false otherwise.
   */
  std::vector<uint8_t> compress(std::string& filepath);

  /**
   * Decompresses a `.kpc` file and saves the decompressed data to
   * a new file with a `_decompressed.txt` extension.
   * 
   * @param filepath: The path to the `.kpc` file to decompress.
   * @return: True if the decompression was successful; false otherwise.
   */
  std::string decompress(const std::vector<uint8_t>& binary_data);

public:
  /**
   * Compresses the file at the given filepath.
   * 
   * @param data: The filepath of the file to compress.
   * @return: True if the compression was successful, false otherwise.
   */
  bool compress_file(std::string& data);

  /**
   * Decompresses the file at the given filepath.
   * 
   * @param data: The filepath of the file to decompress.
   * @return: True if the decompression was successful, false otherwise.
   */
  bool decompress_file(std::string& data);
};

#endif // KP_COMPRESSOR_HPP
