#include "BitmapPrinter.h"
#include <fstream>
#include <cmath>
BitmapPrinter::BitmapPrinter(std::shared_ptr<GridMap> gridMap)
: gridMap_(gridMap)
{

}

void BitmapPrinter::print()
{
    if(!gridMap_->isGridMapCreatedSuccess()) return;
    std::vector<RGB> bitmap(gridMap_->dimension()*gridMap_->dimension(), {255, 255, 255});
    RGB circleColor = {0, 0, 255};
    const std::vector<bool>& gridMap = gridMap_->gridMap();
    std::cout<<"bitmap size: "<<bitmap.size()<<", gridMap size: "<<gridMap.size()<<"\n";
    for(int i = 0; i < gridMap.size(); i++){
        if(gridMap[i]){
            bitmap[i] = circleColor;
        }
    }
    saveBitmap(bitmap, "output_bitmap.bmp");
}

void BitmapPrinter::saveBitmap(const std::vector<RGB> &bitmap, const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);

    // Bitmap file header
    const int HEADER_SIZE = 54;
    const int PIXEL_ARRAY_OFFSET = 54;
    const int BITS_PER_PIXEL = 24;
    const unsigned char WIDTH = gridMap_->dimension();
    const unsigned char HEIGHT = gridMap_->dimension();
    unsigned char header[54] = {
        'B', 'M',                               // Signature
        0, 0, 0, 0,                             // Image file size in bytes
        0, 0, 0, 0,                             // Reserved
        PIXEL_ARRAY_OFFSET, 0, 0, 0,            // Pixel data offset
        40, 0, 0, 0,                            // Header size
        WIDTH, 0, 0, 0,                         // Image width
        HEIGHT, 0, 0, 0,                        // Image height
        1, 0,                                   // Planes
        BITS_PER_PIXEL, 0,                      // Bits per pixel
        0, 0, 0, 0,                             // Compression
        0, 0, 0, 0,                             // Image size (can be 0 for uncompressed)
        0, 0, 0, 0,                             // Horizontal resolution
        0, 0, 0, 0,                             // Vertical resolution
        0, 0, 0, 0,                             // Colors in color table
        0, 0, 0, 0                              // Important color count
    };

    // Set the file size
    int fileSize = HEADER_SIZE + WIDTH * HEIGHT * 3;
    header[2] = fileSize & 0xFF;
    header[3] = (fileSize >> 8) & 0xFF;
    header[4] = (fileSize >> 16) & 0xFF;
    header[5] = (fileSize >> 24) & 0xFF;

    // Write header
    file.write(reinterpret_cast<char*>(header), HEADER_SIZE);

    // Write pixel data
    for (int y = HEIGHT - 1; y >= 0; y--) {  // BMP format stores pixels bottom-to-top
        for (int x = 0; x < WIDTH; x++) {
            RGB color = bitmap[y * WIDTH + x];
            file.write(reinterpret_cast<char*>(&color), 3);
        }
    }

    file.close();
}
