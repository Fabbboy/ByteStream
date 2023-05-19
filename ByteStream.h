#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <libc.h>
#include <cjson/cJSON.h>

typedef struct ByteStream {
    uint8_t* data;
    size_t size;
    size_t capacity;
    size_t pointer;
} ByteStream;

ByteStream* createByteStream(size_t size);
void destroyByteStream(ByteStream* stream);

//simple byte operations
void writeByte(ByteStream* stream, uint8_t byte);
uint8_t readByte(ByteStream* stream);
void writeBytes(ByteStream* stream, uint8_t* bytes, size_t size);
uint8_t* readBytes(ByteStream* stream, size_t size);

//i32 operations
void writeInt(ByteStream* stream, int32_t integer);
int32_t readInt(ByteStream* stream);

//string operations
void writeString(ByteStream* stream, char* string);
char* readString(ByteStream* stream);

//file operations
void writeToFile(ByteStream* stream, char* path);
ByteStream*readFromFile(char* path);

//debug operations
uint32_t byteStreamGetPointer(ByteStream* stream);
void byteStreamSetPointer(ByteStream* stream, uint32_t pointer);
void printByteStream(ByteStream* stream);
void printByteStreamData(ByteStream* stream);

void resizeByteStream(ByteStream* stream, size_t size);

// Functions for CJSON serialization/deserialization
ByteStream* createByteStreamFromCJSON(cJSON* json);
cJSON* createCJSONFromByteStream(ByteStream* stream);

