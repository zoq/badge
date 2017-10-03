/**
 * @file base.ino
 * @author Marcus Edel
 *
 * Implementation of the base routine.
 */

#include <DigiUSB.h>
#include <avr/pgmspace.h>

// MOSI is the "master-out/slave-in" line and also known as DATA, DO, DOUT, and LOAD.
#define MOSI_HIGH() PORTB |= (1<<PB0)
#define MOSI_LOW()  PORTB &= ~(1<<PB0)

// SS is the "slave select" line and also known as CS.
#define SS_HIGH()   PORTB |= (1<<PB1)
#define SS_LOW()    PORTB &= ~(1<<PB1)

// SCK is the "serial clock" line and also known as SCLK, and CLK.
#define SCK_HIGH()  PORTB |= (1<<PB2)
#define SCK_LOW()   PORTB &= ~(1<<PB2)

// This sets PB0, PB1, and PB2 to output mode.
#define INIT_PORT() DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2)

#define NUM_FRAMES 67

const byte frames[NUM_FRAMES][8] PROGMEM = {
  {
    // space
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    // !
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00000000,
    B00010000,
    B00000000
  },
  {
    // "
    B00101000,
    B00101000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    // #
    B00000000,
    B00101000,
    B01111100,
    B00101000,
    B01111100,
    B00101000,
    B00000000,
    B00000000
  },
  {
    // $
    B00010000,
    B00111000,
    B01000000,
    B00110000,
    B00001000,
    B01110000,
    B00100000,
    B00000000
  },
  {
    // %
    B00010000,
    B00111000,
    B01000000,
    B00110000,
    B00001000,
    B01110000,
    B00100000,
    B00000000
  },
  {
    // &
    B00010000,
    B00101000,
    B00101000,
    B00010000,
    B00101010,
    B00100100,
    B00011010,
    B00000000
  },
  {
    // '
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    // (
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000,
    B00010000,
    B00001000,
    B00000000
  },
  {
    // )
    B00100000,
    B00010000,
    B00001000,
    B00001000,
    B00001000,
    B00010000,
    B00100000,
    B00000000
  },
  {
    // *
    B00000000,
    B00000000,
    B00010000,
    B00111000,
    B00010000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    // +
    B00000000,
    B00010000,
    B00010000,
    B01111100,
    B00010000,
    B00010000,
    B00000000,
    B00000000
  },
  {
    // ,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000100,
    B00000100,
    B00000000
  },
  {
    // -
    B00000000,
    B00000000,
    B00000000,
    B00111100,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  {
    // .
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000100,
    B00000000
  },
  {
    // /
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B00000000
  },
  {
    // 0
    B00011000,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    // 1
    B00001000,
    B00011000,
    B00001000,
    B00001000,
    B00001000,
    B00001000,
    B00011100,
    B00000000
  },
  {
    // 2
    B00011000,
    B00100100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B00111100,
    B00000000
  },
  {
    // 3
    B00011000,
    B00100100,
    B00000100,
    B00001000,
    B00000100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    // 4
    B00000100,
    B00001100,
    B00010100,
    B00100100,
    B00111110,
    B00000100,
    B00000100,
    B00000000
  },
  {
    // 5
    B00111100,
    B00100000,
    B00111000,
    B00000100,
    B00000100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    // 6
    B00011000,
    B00100000,
    B00100000,
    B00111000,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    // 7
    B00111100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00000000
  },
  {
    // 8
    B00011000,
    B00100100,
    B00100100,
    B00011000,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    // 9
    B00011000,
    B00100100,
    B00100100,
    B00011100,
    B00000100,
    B00000100,
    B00011000,
    B00000000
  },
  {
    // :
    B00000000,
    B00100000,
    B00100000,
    B00000000,
    B00000000,
    B00100000,
    B00100000,
    B00000000
  },
  {
    // ;
    B00000000,
    B00000000,
    B00100000,
    B00000000,
    B00000000,
    B00100000,
    B00100000,
    B00000000
  },
  {
    // <
    B00000000,
    B00000000,
    B00010000,
    B00100000,
    B01000000,
    B00100000,
    B00010000,
    B00000000
  },
  {
    // =
    B00000000,
    B00000000,
    B01111100,
    B00000000,
    B00000000,
    B01111100,
    B00000000,
    B00000000
  },
  {
    // >
    B00000000,
    B00000000,
    B00100000,
    B00010000,
    B00001000,
    B00010000,
    B00100000,
    B00000000
  },
  {
    // ?
    B00011000,
    B00101000,
    B00001000,
    B00011000,
    B00010000,
    B00000000,
    B00010000,
    B00000000
  },
  {
    // @
    B00111000,
    B01000100,
    B01011100,
    B01101100,
    B01011000,
    B01000000,
    B00111000,
    B00000000
  },
  {
    // A
    B00011000,
    B00100100,
    B00100100,
    B00100100,
    B00111100,
    B00100100,
    B00100100,
    B00000000 },
  {
    // B
    B00111000,
    B00100100,
    B00100100,
    B00111000,
    B00100100,
    B00100100,
    B00111000,
    B00000000
  }, {
    // C
    B00011000,
    B00100100,
    B00100000,
    B00100000,
    B00100000,
    B00100100,
    B00011000,
    B00000000
  }, {
    // D
    B00111000,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00111000,
    B00000000
  }, {
    // E
    B00111100,
    B00100000,
    B00100000,
    B00111000,
    B00100000,
    B00100000,
    B00111100,
    B00000000
  }, {
    // F
    B00111100,
    B00100000,
    B00100000,
    B00111000,
    B00100000,
    B00100000,
    B00100000,
    B00000000
  },
  {
    // G
    B00011000,
    B00100100,
    B00100000,
    B00101100,
    B00100100,
    B00100100,
    B00011100,
    B00000000
  },
  {
    // H
    B00100100,
    B00100100,
    B00100100,
    B00111100,
    B00100100,
    B00100100,
    B00100100,
    B00000000
  },
  {
    // I
    B00111000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00111000,
    B00000000
  },
  {
    // J
    B00110000,
    B00010000,
    B00010000,
    B00010000,
    B01010000,
    B01010000,
    B01100000,
    B00000000
  },
  {
    // K
    B00100100,
    B00100100,
    B00101000,
    B00110000,
    B00101000,
    B00100100,
    B00100100,
    B00000000
  },
  {
    // L
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00111100,
    B00000000
  },
  {
    // M
    B01000100,
    B01101100,
    B01010100,
    B01010100,
    B01000100,
    B01000100,
    B01000100,
    B00000000
  },
  {
    // N
    B01000100,
    B01000100,
    B01100100,
    B01010100,
    B01001100,
    B01000100,
    B01000100,
    B00000000
  },
  {
    // O
    B00011000,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    // P
    B00111000,
    B00100100,
    B00100100,
    B00111000,
    B00100000,
    B00100000,
    B00100000,
    B00000000
  },
  {
    // Q
    B00011000,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00110100,
    B00011000,
    B00000100
  },
  {
    // R
    B00111000,
    B00100100,
    B00100100,
    B00111000,
    B00100100,
    B00100100,
    B00100100,
    B00000000
  },
  {
    // S
    B00011000,
    B00100100,
    B00100000,
    B00011000,
    B00000100,
    B00000100,
    B00111000,
    B00000000
  },
  {
    // T
    B01111100,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00000000
  },
  {
    // U
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00011000,
    B00000000
  },
  {
    // V
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B00101000,
    B00101000,
    B00010000,
    B00000000
  },
  {
    // W
    B00100010,
    B00100010,
    B00100010,
    B00101010,
    B00101010,
    B00101010,
    B00010100,
    B00000000
  },
  {
    // X
    B01000100,
    B01000100,
    B00101000,
    B00010000,
    B00101000,
    B01000100,
    B01000100,
    B00000000
  },
  {
    // Y
    B01000100,
    B01000100,
    B00101000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00000000
  },
  {
    // Z
    B00111100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B00111100,
    B00000000
  },
  {
    // Star
    B00010000,
    B01010100,
    B00111000,
    B01111100,
    B00111000,
    B01010100,
    B00010000,
    B00000000
  },
  {
    // Heart 1
    B00110110,
    B01001001,
    B01000001,
    B01000001,
    B00100010,
    B00010100,
    B00001000,
    B00000000
  },
  {
    // Heart 2
    B00110110,
    B01011101,
    B01100011,
    B01000001,
    B00100010,
    B00010100,
    B00001000,
    B00000000
  },
  {
    // Heart 3
    B00110110,
    B01111111,
    B01110111,
    B01000001,
    B00100010,
    B00010100,
    B00001000,
    B00000000
  },
  {
    // Heart 4
    B00110110,
    B01101011,
    B01010101,
    B01100011,
    B00100010,
    B00010100,
    B00001000,
    B00000000
  },
  {
    // Heart 5
    B00110110,
    B01111111,
    B01111111,
    B01110111,
    B00100010,
    B00010100,
    B00001000,
    B00000000
  },
  {
    // Heart 6
    B00110110,
    B01111111,
    B01111111,
    B01111111,
    B00111110,
    B00011100,
    B00001000,
    B00000000
  }
  ,
  {
    // mlpack 1
    B00000000,
    B00001000,
    B00100100,
    B01001010,
    B10100101,
    B00010000,
    B00000000,
    B00000000
  }
};

uint8_t shift = 0;
uint8_t displayA[8];
uint8_t displayB[8];
uint8_t textIdxA = 0;
uint8_t textIdxB = 1;
char message[50] = {0};
bool reset_message = true;
uint8_t frameCounter = 0;
uint8_t messageLen = 0;
bool usbAvailable = false;

void SpiSend(uint8_t data)
{
  uint8_t i;
  for (i = 0; i < 8; i++, data <<= 1)
  {
    SCK_LOW();

    if (data & 0x80)
    {
      MOSI_HIGH();
    }
    else
    {
      MOSI_LOW();
    }

    SCK_HIGH();
  }
}

void Max7219Writec(uint8_t high_byte, uint8_t low_byte)
{
  SS_LOW();
  SpiSend(high_byte);
  SpiSend(low_byte);
  SS_HIGH();
}

void Max7219Clear() {
  uint8_t i;
  for (i = 0; i < 8; i++)
  {
    Max7219Writec(i + 1, 0);
  }
}

void UpdateDisplay()
{
  uint8_t i;
  for (i = 0; i < 8; i++)
  {
    Max7219Writec(i + 1, displayA[i]);
  }
}

void Image(int A, int B)
{
  memcpy_P(displayA, frames[A], 8);
  memcpy_P(displayB, frames[B], 8);

  uint8_t i;
  for (i = 0; i < 8; i++)
  {
    displayA[i] = displayA[i] << shift | displayB[i] >> (7 - shift);
  }
}

void setup()
{
  // MLPACK.ORG-GSOC2017>IRC#MLPACK-.
  message[0] = 'M';
  message[1] = 'L';
  message[2] = 'P';
  message[3] = 'A';
  message[4] = 'C';
  message[5] = 'K';
  message[6] = '.';
  message[7] = 'O';
  message[8] = 'R';
  message[9] = 'G';
  message[10] = ' ';
  message[11] = 'G';
  message[12] = 'S';
  message[13] = 'O';
  message[14] = 'C';
  message[15] = '2';
  message[16] = '0';
  message[17] = '1';
  message[18] = '7';
  message[19] = '>';
  message[20] = 'I';
  message[21] = 'R';
  message[22] = 'C';
  message[23] = '#';
  message[24] = 'M';
  message[25] = 'L';
  message[26] = 'P';
  message[27] = 'A';
  message[28] = 'C';
  message[29] = 'K';
  message[30] = '-';

  messageLen = 30;

  INIT_PORT();

  // Decode mode: none.
  Max7219Writec(0x09, 0);

  // Intensity: (0-15).
  Max7219Writec(0x0A, 1);

  // Scan limit: All "digits" (rows) on.
  Max7219Writec(0x0B, 7);

  // Shutdown register: Display on.
  Max7219Writec(0x0C, 1);

  // Display test: off.
  Max7219Writec(0x0F, 0);

  Max7219Clear();

  DigiUSB.begin();
}

void MlpackAnimation()
{
  Max7219Clear();
  memcpy_P(displayA, frames[66], 8);

  uint8_t i;
  for (i = 0; i < 8; i++)
  {
    Max7219Writec(i + 1, displayA[i]);
    delay(150);
  }
}
void HeartAnimation()
{
    uint8_t i;
    for(i = 0; i < 6; ++i)
    {
      memcpy_P(displayA, frames[60 + i], 8);
      UpdateDisplay();
      delay(130);
    }
}


void loop()
{
  DigiUSB.println("Waiting for input...");
  int lastRead;

  while (true)
  {
    if (DigiUSB.available())
    {
      // Something to read.
      lastRead = DigiUSB.read();
      usbAvailable = true;

      // Check if beginning of a new message.
      if (reset_message)
      {
        messageLen = 0;
        reset_message = false;
      }

      if (lastRead == '\n' || (sizeof(message) - 1 == messageLen))
      {
        reset_message = true;
        textIdxA = 0;
        textIdxB = 1;

        // When we get a newline, break out of loop.
        break;
      }
      else
      {
        if (char(lastRead) == 's')
        {
          message[messageLen] = char(59) + ' ';
        }
        else if (char(lastRead) == 'i')
        {
          message[messageLen] = char(65) + ' ';
        }
        else
        {
          message[messageLen] = char(lastRead);
        }

        messageLen++;
      }
    }

    // Show animation only if the intial message is not changed.
    if (!usbAvailable)
    {
      if (textIdxA == 0 && frameCounter == 0)
      {
        MlpackAnimation();
        MlpackAnimation();

        DigiUSB.delay(5);
      }

      if (textIdxB == 11 && frameCounter == 0)
      {
        HeartAnimation();
        HeartAnimation();

        DigiUSB.delay(5);
      }
    }

    // Set the current text.
    Image(message[textIdxA] - ' ', message[textIdxB] - ' ');

    // Display current frame.
    UpdateDisplay();

    // Update tracking parameter.
    frameCounter++;
    shift = (shift + 1) % 7;

    // Update the index of the upcoming text.
    if (frameCounter > 6)
    {
      textIdxA = (textIdxA + 1) % messageLen;
      textIdxB = (textIdxB + 1) % messageLen;
      frameCounter = 0;
    }

    DigiUSB.delay(200);
  }
}

