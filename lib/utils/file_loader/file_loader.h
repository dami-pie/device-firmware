#ifndef __file_loader_h__
#define __file_loader_h__

#include <Arduino.h>
#include "SPIFFS.h"

File load_file(const char *file_path);

#endif