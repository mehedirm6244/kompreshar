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

public:
  void compress_file(std::string& data);
  void decompress_file(std::string& data);
};

#endif // KP_COMPRESSOR_HPP
