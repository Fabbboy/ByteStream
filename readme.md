# ByteStream Library

The ByteStream library provides a set of functions to work with byte streams in C. It allows you to easily perform operations such as reading and writing bytes, integers, strings, as well as serializing and deserializing data using the CJSON library.

!! **Current setup is for MacOS using Homebrew. If you're using Windows or Linux, you will need to edit the CMake** !!

## Features

- Create a byte stream with a specified size.
- Write and read individual bytes.
- Write and read byte arrays of arbitrary size.
- Write and read 32-bit integers.
- Write and read strings.
- Write the byte stream to a file.
- Read a byte stream from a file.
- Set and get the current pointer position within the byte stream.
- Print the contents of the byte stream for debugging purposes.
- Serialize and deserialize data to/from a CJSON object.

## Usage

To use the ByteStream library in your project, follow these steps:

1. Include the `ByteStream.h` header file in your source file(s):

   ```c
   #include "ByteStream.h"
    ```
2. Compile the `ByteStream.c` source file along with your source files.
3. Link the `cjson` library to your project.
4. Include the `cjson` header file in your source file(s):

   ```c
   #include "cJSON.h"
    ```
5. Compile the `cjson` source files along with your source files.
6. Link the `cjson` library to your project.
7. Compile and run your project.

## Examples
Here are a few examples demonstrating the usage of the ByteStream library:
```c
#include <stdio.h>
#include "ByteStream.h"

int main() {
    // Create a byte stream
    ByteStream* stream = createByteStream(1024);

    // Write and read bytes
    writeByte(stream, 0x41);
    uint8_t byte = readByte(stream);

    // Write and read byte arrays
    uint8_t bytes[] = {0x41, 0x42, 0x43};
    writeBytes(stream, bytes, sizeof(bytes));
    uint8_t* readedBytes = readBytes(stream, sizeof(bytes));

    // Write and read integers
    writeInt(stream, 12345);
    int32_t integer = readInt(stream);

    // Write and read strings
    writeString(stream, "Hello, World!");
    char* string = readString(stream);

    // Write the byte stream to a file
    writeToFile(stream, "data.bin");

    // Read a byte stream from a file
    ByteStream* fileStream = readFromFile("data.bin");
    
    // Print the byte stream contents
    printByteStream(fileStream);
    printByteStreamData(fileStream);

    // Clean up
    destroyByteStream(stream);
    destroyByteStream(fileStream);
    free(readedBytes);
    free(string);

    return 0;
}
```

## Contributing

Contributions to the ByteStream library are welcome! If you find any issues or have suggestions for improvement, please open an issue or submit a pull request on the GitHub repository.

## License

The ByteStream library is licensed under the MIT License. See the LICENSE file for more details.
