#include "file_loader.h"

File load_file(const char *file_path)
{
  if (!SPIFFS.begin(true))
  {
    Serial.begin(115200);
    Serial.println("[SPIFFS]: An Error has occurred while mounting SPIFFS");
    return File();
  }
  return SPIFFS.open(file_path);
}