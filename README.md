# System Info

```bash
$ uname -a
Linux nstpc 5.4.0-42-generic #46-Ubuntu SMP Fri Jul 10 00:24:02 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

$ gcc -v
gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
```

# boost library
## Get source
`wget https://dl.bintray.com/boostorg/release/1.73.0/source/boost_1_73_0.tar.gz`

## build boost
```bash
tar -zxf boost_1_73_0.tar.gz
cd boost_1_73_0
./b2
```
## Adaptor
Change the CMakeLists.txt. Make it adaptor your boost directory if you don't want to system installed library
