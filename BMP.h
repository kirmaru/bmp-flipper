#pragma pack(push, 1)
struct BMPHeader {
    char signature[2];
    int fileSize;
    int reserved;
    int dataOffset;
    int headerSize;
    int width;
    int height;
    short planes;
    short bitCount;
    int compression;
    int sizeImage;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    int colorsUsed;
    int colorsImportant;
};
#pragma pack