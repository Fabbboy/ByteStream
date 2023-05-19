#include "../ByteStream.h"

ByteStream *createByteStream(size_t size) {
    ByteStream *stream = malloc(sizeof(ByteStream));
    stream->data = malloc(size);
    stream->size = 0;
    stream->capacity = size;
    stream->pointer = 0;
    return stream;
};

void destroyByteStream(ByteStream *stream) {
    free(stream->data);
    free(stream);
};

//simple byte operations
void writeByte(ByteStream *stream, uint8_t byte) {
    if (stream->size == stream->capacity) {
        stream->capacity *= 2;
        stream->data = realloc(stream->data, stream->capacity);
    };
    stream->data[stream->size] = byte;
    stream->size++;
};

uint8_t readByte(ByteStream *stream) {
    if (stream->pointer == stream->size) {
        return 0;
    };
    uint8_t byte = stream->data[stream->pointer];
    stream->pointer++;
    return byte;
};

void writeBytes(ByteStream *stream, uint8_t *bytes, size_t size) {
    for (size_t i = 0; i < size; i++) {
        writeByte(stream, bytes[i]);
    };
};

uint8_t *readBytes(ByteStream *stream, size_t size) {
    uint8_t *bytes = malloc(size);
    for (size_t i = 0; i < size; i++) {
        bytes[i] = readByte(stream);
    };
    return bytes;
};

void writeInt(ByteStream *stream, int32_t integer) {
    writeBytes(stream, (uint8_t * ) & integer, sizeof(int32_t));
};

int32_t readInt(ByteStream *stream) {
    return *(int32_t *) readBytes(stream, sizeof(int32_t));
};

void writeString(ByteStream *stream, char *string) {
    size_t size = strlen(string);
    writeInt(stream, size);
    writeBytes(stream, (uint8_t *) string, size);
};

char *readString(ByteStream *stream) {
    size_t size = readInt(stream);
    return (char *) readBytes(stream, size);
};

void writeToFile(ByteStream *stream, char *path) {
    FILE *file = fopen(path, "wb");
    fwrite(stream->data, stream->size, 1, file);
    fclose(file);
};

ByteStream* readFromFile(char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    ByteStream* stream = createByteStream(size);
    if (stream == NULL) {
        printf("Failed to create byte stream.\n");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(stream->data, 1, size, file);
    fclose(file);

    if (bytesRead != size) {
        printf("Failed to read data from file.\n");
        destroyByteStream(stream);
        return NULL;
    }

    stream->size = size;

    return stream;
}
uint32_t byteStreamGetPointer(ByteStream *stream) {
    return stream->pointer;
};

void byteStreamSetPointer(ByteStream *stream, uint32_t pointer) {
    stream->pointer = pointer;
};

void printByteStream(ByteStream *stream) {
    printf("ByteStream: {\n");
    printf("\tdata: %p\n", stream->data);
    printf("\tsize: %zu\n", stream->size);
    printf("\tcapacity: %zu\n", stream->capacity);
    printf("\tpointer: %zu\n", stream->pointer);
    printf("}\n");
};

void printByteStreamData(ByteStream* stream){
    printf("ByteStreamData: {\n");
    uint8_t bytes[stream->size];
    for (size_t i = 0; i < stream->size; i++) {
        bytes[i] = stream->data[i];
    };
    printf("\tdata: [");
    for (size_t i = 0; i < stream->size; i++) {
        printf("%d", bytes[i]);
        if (i != stream->size - 1) {
            printf(", ");
        };
    };
    printf("]\n");
    printf("}\n");
};


void resizeByteStream(ByteStream *stream, size_t size) {
    stream->data = realloc(stream->data, size);
    stream->capacity = size;
};


ByteStream *createByteStreamFromCJSON(cJSON *json) {
    ByteStream *stream = createByteStream(0);
    char *string = cJSON_Print(json);
    size_t size = strlen(string);
    resizeByteStream(stream, size);
    writeString(stream, string);
    free(string);
    return stream;
};

cJSON *createCJSONFromByteStream(ByteStream *stream) {
    char *string = readString(stream);
    cJSON *json = cJSON_Parse(string);
    free(string);
    return json;
};

