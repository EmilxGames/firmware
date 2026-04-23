#define I2C_SDA 15
#define I2C_SCL 16

#if CROW_SELECT == 1
#define WAKE_ON_TOUCH
#define SCREEN_TOUCH_INT 47
#define USE_POWERSAVE
#define SLEEP_TIME 180
#endif

#if CROW_SELECT == 1
// dac / amp
// #define HAS_I2S // didn't get I2S sound working
#define PIN_BUZZER 8 // using pwm buzzer instead (nobody will notice, lol)
#define DAC_I2S_BCK 13
#define DAC_I2S_WS 11
#define DAC_I2S_DOUT 12
#define DAC_I2S_MCLK 8 // don't use GPIO0 because it's assigned to LoRa or button
#else
// On hardware revision v1.2+ the LoRa module's NSS/CS line was moved to IO8,
// which is the same pin the 4.3"/5.0"/7.0" boards previously wired to an
// external buzzer. Leave PIN_BUZZER undefined for those boards so the startup
// chime and ExternalNotification PWM don't steal the SPI chip-select. (The
// STC8H1K28 on v1.2+ has its own buzzer reachable via I2C 0x30 command 246.)
#ifndef CROWPANEL_HW_V14
#define PIN_BUZZER 8
#endif
#endif

// GPS via UART1 connector
#define GPS_DEFAULT_NOT_PRESENT 1
#define HAS_GPS 1
#if CROW_SELECT == 1
#define GPS_RX_PIN 18
#define GPS_TX_PIN 17
#else
// GPIOs shared with LoRa or MIC module
#define GPS_RX_PIN 19
#define GPS_TX_PIN 20
#endif

// Extension Slot Layout, viewed from above (2.4-3.5)
// DIO1/IO1 o   o IO2/NRESET
// SCK/IO10 o   o IO16/NC
// MISO/IO9 o   o IO15/NC
// MOSI/IO3 o   o NC/DIO2
//      3V3 o   o IO46/BUSY
//      GND o   o IO0/NSS
//    5V/NC o   o NC/DIO3
//         J9   J8

// Extension Slot Layout, viewed from above (4.3-7.0)
// !! DIO1/IO20 o   o IO19/NRESET !!
// !!   SCK/IO5 o   o IO16/NC
// !!  MISO/IO4 o   o IO15/NC
// !!  MOSI/IO6 o   o NC/DIO2
//          3V3 o   o IO2/BUSY !!
//          GND o   o IO0/NSS
//        5V/NC o   o NC/DIO3
//             J9   J8

// LoRa
#define USE_SX1262

#if CROW_SELECT == 1
// 2.4", 2.8, 3.5"""
#define HW_SPI1_DEVICE
#define LORA_CS 0
#define LORA_SCK 10
#define LORA_MISO 9
#define LORA_MOSI 3

#define LORA_RESET 2
#define LORA_DIO1 1  // SX1262 IRQ
#define LORA_DIO2 46 // SX1262 BUSY

// need to pull IO45 low to enable LORA and disable Microphone on 24 28 35
#define SENSOR_POWER_CTRL_PIN 45
#define SENSOR_POWER_ON LOW
#else
// 4.3", 5.0", 7.0"
// Hardware revision v1.2+ moved the LoRa NSS from IO0 to IO8.
// Enable CROWPANEL_HW_V14 to build for boards labelled v1.2, v1.3, v1.4.
#ifdef CROWPANEL_HW_V14
#define LORA_CS 8
#else
#define LORA_CS 0
#endif
#define LORA_SCK 5
#define LORA_MISO 4
#define LORA_MOSI 6

#define LORA_RESET 19
#define LORA_DIO1 20 // SX1262 IRQ
#define LORA_DIO2 2  // SX1262 BUSY
#endif

#define SX126X_CS LORA_CS
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY LORA_DIO2
#define SX126X_RESET LORA_RESET
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 3.3
