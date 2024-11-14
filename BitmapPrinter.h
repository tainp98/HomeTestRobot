#ifndef BITMAPPRINTER_H
#define BITMAPPRINTER_H
#include "MapPrinter.h"
#include <vector>
#include <memory>
#include "GridMap.h"

class BitmapPrinter : public MapPrinter
{
public:
    struct RGB {
        unsigned char r, g, b;
    };
public:
    BitmapPrinter(std::shared_ptr<GridMap> gridMap);
    void print() override;
private:
    void saveBitmap(const std::vector<RGB>& bitmap, const std::string& filename);
private:
    std::shared_ptr<GridMap> gridMap_;
};

#endif // BITMAPPRINTER_H
