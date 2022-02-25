#include "Bitmap.h"

#include <fstream>
#include <iostream>
#include <string>

namespace {

const char kFileName[] = "output.bmp";

const uint32_t kPixelSizeBytes = 3;
const uint32_t kBitmapHeaderSizeBytes = 14;
const uint32_t kBitmapInfoHeaderSizeBytes = 40;

// Bitmap header
const char kSignature[2] = {'B', 'M'};
const uint32_t kReservedBytes = 0;
const uint32_t kPixelDataOffset =
    kBitmapHeaderSizeBytes + kBitmapInfoHeaderSizeBytes;

// Bitmap info header:
const uint32_t kNumBytesInInfoHeader = kBitmapInfoHeaderSizeBytes;
const uint16_t kNumColorPlanes = 1;  // Must be 1.
const uint16_t kColorDepth = kPixelSizeBytes * 8u;
const uint32_t kCompressionMethod = 0;       // BI_RGB.
const uint32_t kRawBitmapDataSize = 0;       // Ignored for BI_RGB.
const int32_t kHorizontalPixelPerMeter = 0;  // Hopefully ignored.
const int32_t kVerticalPixelPerMeter = 0;    // Hopefully ignored.
const uint32_t kNumColorsInPalette = 0;      // Will default to 2^n.
const uint32_t kNumImportantColors = 0;      // Generally ignored.

std::string ToLittleEndian(uint16_t num) {
  std::string out(2, 0x00);
  out[0] = (num & 0x00ff);
  out[1] = (num & 0xff00) >> 8;
  return out;
}
std::string ToLittleEndian(uint32_t num) {
  std::string out(4, 0x00);
  out[0] = (num & 0x000000ff);
  out[1] = (num & 0x0000ff00) >> 8;
  out[2] = (num & 0x00ff0000) >> 16;
  out[3] = (num & 0xff000000) >> 24;
  return out;
}
std::string ToLittleEndian(int32_t num) {
  std::string out(4, 0x00);
  out[0] = (num & 0x000000ff);
  out[1] = (num & 0x0000ff00) >> 8;
  out[2] = (num & 0x00ff0000) >> 16;
  out[3] = (num & 0xff000000) >> 24;
  return out;
}
std::string ToLittleEndian(Bitmap::Pixel pixel) {
  std::string out(3, 0x00);
  out[0] = pixel.blue;
  out[1] = pixel.green;
  out[2] = pixel.red;
  return out;
}

}  // namespace

void Bitmap::WriteToFile(const std::vector<std::vector<Pixel>>& pixels) {
  std::ofstream out(kFileName, std::ios::out | std::ios::binary);

  int32_t height_pixels = pixels.size();
  int32_t width_pixels = pixels[0].size();
  uint32_t num_bytes_in_file = kBitmapHeaderSizeBytes +
                               kBitmapInfoHeaderSizeBytes +
                               (kPixelSizeBytes * width_pixels * height_pixels);

  // Header:
  out.write(kSignature, sizeof(kSignature));
  out.write(ToLittleEndian(num_bytes_in_file).data(),
            sizeof(num_bytes_in_file));
  out.write(ToLittleEndian(kReservedBytes).data(), sizeof(kReservedBytes));
  out.write(ToLittleEndian(kPixelDataOffset).data(), sizeof(kPixelDataOffset));

  // Info header:
  out.write(ToLittleEndian(kNumBytesInInfoHeader).data(),
            sizeof(kNumBytesInInfoHeader));
  out.write(ToLittleEndian(width_pixels).data(), sizeof(width_pixels));
  out.write(ToLittleEndian(height_pixels).data(), sizeof(height_pixels));
  out.write(ToLittleEndian(kNumColorPlanes).data(), sizeof(kNumColorPlanes));
  out.write(ToLittleEndian(kColorDepth).data(), sizeof(kColorDepth));
  out.write(ToLittleEndian(kCompressionMethod).data(),
            sizeof(kCompressionMethod));
  out.write(ToLittleEndian(kRawBitmapDataSize).data(),
            sizeof(kRawBitmapDataSize));
  out.write(ToLittleEndian(kHorizontalPixelPerMeter).data(),
            sizeof(kHorizontalPixelPerMeter));
  out.write(ToLittleEndian(kVerticalPixelPerMeter).data(),
            sizeof(kVerticalPixelPerMeter));
  out.write(ToLittleEndian(kNumColorsInPalette).data(),
            sizeof(kNumColorsInPalette));
  out.write(ToLittleEndian(kNumImportantColors).data(),
            sizeof(kNumImportantColors));

  // Pixels:
  // Note: bitmap fills bottom up, so reverse rows.
  for (int i = pixels.size() - 1; i >= 0; --i) {
    for (size_t j = 0; j < pixels[i].size(); ++j) {
      std::string pixel_str = ToLittleEndian(pixels[i][j]);
      out.write(pixel_str.data(), pixel_str.size());
    }
  }

  out.close();
}
