![Chiika](https://raw.githubusercontent.com/arkenthera/Chiika/master/resources/icon.png)

[![Build Status](https://travis-ci.org/arkenthera/ChiikaApi.svg?branch=master)](https://travis-ci.org/arkenthera/ChiikaApi)



Chiika Api is the framework that powers [Chiika](https://github.com/arkenthera/Chiika). It is a multipurpose C++ library.It can fully interact with MAL official API and unofficial things like scraping,Senpai.Moe data for calendars,video file and library detection,anime list,manga list and custom lists support, local database and many more!

Chiika Api builds on all platforms.

## Building on OS X

To build on OS X, you will need Clang 6.0

### Requirements
- Clang 6.0+
- CMake 2.8+
- Xcode 6.4+

```
git clone https://github.com/arkenthera/ChiikaApi
git submodule update --init --recursive
mkdir build && cd build && cmake ..
make
```

## Building on Linux

To build on Linux, you will need GCC 4.8. See the travis build for more info about the platform details.

### Requirements
- GCC 4.8 G++ 4.8
- libcap-dev
- CMake 2.8+

Our gcc script will download CMake.

```
git clone https://github.com/arkenthera/ChiikaApi
git submodule update --init --recursive
sudo add-apt-repository -y ppa:ubuntu-sdk-team/ppa
sudo apt-get install gcc-4.8 g++-4.8 libcap-dev
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 20
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 20
if [ "$CXX" = "g++" ]; then export CXX="g++-4.8" CC="gcc-4.8"; fi
sudo bash ./rungcc.sh
```

## Building on Windows

To build on Windows you will need a compiler with strong C++11 support. We're currently building on **Msvc Win64 Vs2013**

### Requirements
- Msvc
- CMake 2.8+

```
git clone https://github.com/arkenthera/ChiikaApi
git submodule update --init --recursive
mkdir build && cd build && cmake ..
make
```

##### 3rd party libraries used
- [Anitomy](https://github.com/arkenthera/anitomy)
- [Curl](https://github.com/bagder/curl)
- [Googletest](https://github.com/google/googletest)
- [Boost](http://www.boost.org/)
- [ICU](http://site.icu-project.org/)
- [log4cplus](http://site.icu-project.org/)
- [Jsoncpp](https://github.com/arkenthera/jsoncpp)
- [Pugixml](https://github.com/arkenthera/pugixml)
