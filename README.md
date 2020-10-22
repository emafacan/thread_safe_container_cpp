# thread_safe_container_cpp
Customized standard library containers for thread safety and concurreny

### Usage
Require C++ 11 and higher versions

HEADER ONLY library, you can include any container you wish to use in standard library with prefix 'concurrent_'

All containers are template type

#### Example
You can use namespace 'ema'

```c++
#inlcude "concurrent_queue.h"

int main() {
  // code piece
  ema::concurrent_queue<std::string> qString;
  ema::concurrent_queue<std::vector<uint8_t> qByteArray;
  ...
  ema::concurrent_queueu<unsigned char> qChar;
  // code piece
}
```
