# Chiika Api
Chiika Anime Tracker Api

C++ library for MyAnimelist interactions.

## Some of the features:
-Full Myanimelist integration
-Scraping anime and user data(such as friends)
-Senpai.Moe data for calendar and such
-Media player recognition (only for Windows yet)
-Local database
-Tests

#### 3rd party libraries used
- [Anitomy](https://github.com/arkenthera/anitomy)

- [Curl](https://github.com/bagder/curl)

- [Googletest and Googlemock](https://github.com/google/googletest)

- [Jsoncpp](https://github.com/arkenthera/jsoncpp)

- [Pugixml](https://github.com/arkenthera/pugixml)

Some libraries are edited for enchanced use.

## Building

To build this project,you will need [Cmake](https://cmake.org/)

```
git clone https://github.com/arkenthera/ChiikaApi.git
cd ChiikaApi
mkdir _build
cd _build
cmake .. 
```

Recomended Cmake settings

```
BUILD_CURL_EXE uncheck
BUILD_CURL_TESTS uncheck
BUILD_STATIC_LIBS uncheck
JSON_CPP_WITH_TESTS uncheck
```
