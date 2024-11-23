#pragma once

#include "Arduino_DataBus.h"

#if defined(ESP32) && (CONFIG_IDF_TARGET_ESP32S3)
#if (!defined(ESP_ARDUINO_VERSION_MAJOR)) || (ESP_ARDUINO_VERSION_MAJOR < 3)

#ifndef LCD_MAX_PIXELS_AT_ONCE
#define LCD_MAX_PIXELS_AT_ONCE 2046
#endif
#ifndef USE_DMA_THRESHOLD
#define USE_DMA_THRESHOLD 6
#endif

class Arduino_ESP32LCD16 : public Arduino_DataBus
{
public:
  Arduino_ESP32LCD16(
      int8_t dc, int8_t cs, int8_t wr, int8_t rd,
      int8_t d0, int8_t d1, int8_t d2, int8_t d3, int8_t d4, int8_t d5, int8_t d6, int8_t d7,
      int8_t d8, int8_t d9, int8_t d10, int8_t d11, int8_t d12, int8_t d13, int8_t d14, int8_t d15); // Constructor

  bool begin(int32_t speed = GFX_NOT_DEFINED, int8_t dataMode = GFX_NOT_DEFINED) override;
  void beginWrite() override;
  void endWrite() override;
  void writeCommand(uint8_t) override;
  void writeCommand16(uint16_t) override;
  void writeCommandBytes(uint8_t *data, uint32_t len) override;
  void write(uint8_t) override;
  void write16(uint16_t) override;
  void writeRepeat(uint16_t p, uint32_t len) override;
  void writePixels(uint16_t *data, uint32_t len) override;

  void writeC8D8(uint8_t c, uint8_t d) override;
  void writeC8D16(uint8_t c, uint16_t d) override;
  void writeC8D16D16(uint8_t c, uint16_t d1, uint16_t d2) override;
  void writeC8D16D16Split(uint8_t c, uint16_t d1, uint16_t d2) override;
  void writeBytes(uint8_t *data, uint32_t len) override;

  void writeIndexedPixels(uint8_t *data, uint16_t *idx, uint32_t len) override;
  void writeIndexedPixelsDouble(uint8_t *data, uint16_t *idx, uint32_t len) override;
  void writeYCbCrPixels(uint8_t *yData, uint8_t *cbData, uint8_t *crData, uint16_t w, uint16_t h) override;

protected:
private:
  GFX_INLINE void WRITECOMMAND16(uint16_t c);
  GFX_INLINE void WRITE16(uint16_t d);
  GFX_INLINE void WRITE32(uint32_t d);
  GFX_INLINE void CS_HIGH(void);
  GFX_INLINE void CS_LOW(void);

  int8_t _dc, _cs, _wr, _rd;
  int8_t _d0, _d1, _d2, _d3, _d4, _d5, _d6, _d7;
  int8_t _d8, _d9, _d10, _d11, _d12, _d13, _d14, _d15;

  PORTreg_t _csPortSet; ///< PORT register SET
  PORTreg_t _csPortClr; ///< PORT register CLEAR
  uint32_t _csPinMask;  ///< Bitmask

  uint32_t _fast_wait;
  esp_lcd_i80_bus_handle_t _i80_bus = nullptr;
  dma_descriptor_t *_dmadesc = nullptr;
  gdma_channel_handle_t _dma_chan;

  union
  {
    uint32_t value;
    struct
    {
      uint16_t value16;
      uint16_t value16_2;
    };
    struct
    {
      uint8_t lsb;
      uint8_t msb;
      uint8_t lsb_2;
      uint8_t msb_2;
    };
  } _data32;

  union
  {
    uint8_t* _buffer;
    uint16_t* _buffer16;
    uint32_t* _buffer32;
  };

  union
  {
    uint8_t *_2nd_buffer;
    uint16_t *_2nd_buffer16;
    uint32_t *_2nd_buffer32;
  };
};

#endif // #if (!defined(ESP_ARDUINO_VERSION_MAJOR)) || (ESP_ARDUINO_VERSION_MAJOR < 3)
#endif // #if defined(ESP32) && (CONFIG_IDF_TARGET_ESP32S3)
