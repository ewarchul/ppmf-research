## Build 

```
mkdir build && cd build 
conan install .. --build missing -s compiler=gcc -s compiler.libcxx=libstdc++11 
```
