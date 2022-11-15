ESP_ROOT := $(HOME)/esp8266
ESP_LIBS := $(ESP_ROOT)/libraries
 
UPLOAD_PORT := /dev/ttyUSB0
BOARD := nodemcu
FLASH_DEF := 4M1M
 
SKETCH := main.ino
LIBS := $(ESP_LIBS)/ESP8266WiFi \
 $(ESP_LIBS)/ESPAsyncWebServer \
 $(ESP_LIBS)/ESPAsyncTCP \
 $(ESP_LIBS)/ArduinoJson \
 
BUILD_EXTRA_FLAGS := -Og -ggdb
 
include $(HOME)/makeEspArduino/makeEspArduino.mk
