#ifndef KP_COMPRESSOR_HPP
#define KP_COMPRESSOR_HPP

#include <string>
#include <vector>
#include <cstdint>

class KP_Compressor {
private:
  std::string read_file(const std::string& filepath, bool binary_mode);
  bool write_file(const std::string& filepath, const std::vector<uint8_t>& data);
  std::vector<uint8_t> compress(std::string& filepath);
  std::string decompress(const std::vector<uint8_t>& binary_data);
  std::string binary_to_str(const std::vector<uint8_t>& binary_data, size_t& offset, int bits);
  std::string int_to_binary_str(int n, int bufsize);
  int binary_str_to_int(const std::string& binary_str);

public:
  void compress_file(std::string& data);
  void decompress_file(std::string& data);
};

#endif // KP_COMPRESSOR_HPP
