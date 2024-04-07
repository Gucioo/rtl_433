/** @file
    Audi e-tron TPMS sensor (Huf / Autel MX-2)
    https://triq.net/bitbench#c=BMW%20Huf%20Gen5&c=555554b2aab4b2b552acb4d332accb32b552aaacd334d32ad334&c=555554b2aab4b2b552acb4d332acb4cab54caaacd4cad32b4b55&c=Audi%20Huf&c=rtl_433%20-s%201000000%20-X%20%22name%3Dnew%2Cm%3DFSK_PCM%2Cs%3D25%2Cl%3D25%2Cr%3D100%22%20-S%20All&c=%7B167%7D5555552caaaaacaad2aab532b3352aab32d34cacfe&c=%7B149%7D2aaaaa59a5565955a5556a65666a9655a969f8%20-----Invalid&c=%7B166%7D5555552caaaaacaad2aab532b3352b54b2d352ad7c&c=%7B166%7D2aaaaa5955555955a5556a65666a56aa65a65999fc&c=%7B165%7D2aaaaa5955555955a5556a65666a56aa65a65999f8&c=%7B167%7D5555552caaaaacaad2aab532b3352b5532d32cccfe&c=%7B166%7D2aaaaa5955555955a5556a65666a56aa65a65999fc&c=%7B151%7D5555552cd2ab2caad2aab532b3354b2ad4b4fe%20-----Invalid&c=%7B166%7D2aaaaa5955555955a5556a65666a555665a69959fc&c=%7B167%7D5555552caaaaacaad2aab532b3352aab32d34cacfe&f=BRAND%20%3D%208h%20%7C%20SENSOR_ID%20%3D%2032h%20%20%20%20%20%20%7C%20PRESS%20%3D%208d%20%20%7C%20TEMP%20%3D%208d%20%20%7C%20FLAGS1%20%3D%208h%20%7C%20FLAGS2%20%3D%208h%20%7C%20FLAGS3%20%3D%208d%20%20%7C%20CRC%20%3D%208h%0A%0ABRAND%20%3D%208h%20%7C%20SENSOR_ID%20%3D%2032h%20%20%20%20%20%20%7C%20PRESS%20%3D%208d%20%20%7C%20TEMP%20%3D%208d%20%20%7C%20CRC%20%3D%208h&z=1&a=Preamble&m=aa59&d=MC&cw=4
    https://community.openhab.org/t/tutorial-rtl-433-brings-433mhz-sensors-to-openhab/81018/26?page=2
    
    BMW Gen5 TPMS sensor.

    Copyright (C) 2024 Bruno OCTAU (ProfBoc75), \@petrjac, Christian W. Zuckschwerdt <christian@zuckschwerdt.org>, Gucioo.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
*/
/**
BMW Gen5 TPMS sensor.

issue #2821 BMW Gen5 TPMS support open by \@petrjac

Samples raw :
BMW:
     555554b2aab4b2b552acb4d332accb32b552aaacd334d32ad334
     555554b2aab4b2b552acb4d332acb4cab54caaacd4cad32b4b55
Audi:    
{166}2aaaaa5955555955a5556a65666a56aa65a65999fc
{165}2aaaaa5955555955a5556a65666a56aa65a65999f8
{167}5555552caaaaacaad2aab532b3352b5532d32cccfe

- Preamble {16} 0xaa59 before MC
- MC Zero bit coded, 11 bytes - BMW
- MC Zero bit coded, 7 bytes - Audi

Samples after MC Inverted:

     0  1  2  3  4  5  6  7  8  9 10
    MM II II II II PP TT F1 F2 F3 CC
    03 23 e1 36 a1 4a 3e 01 6b 68 6b
    03 23 e1 36 a1 34 3d 01 74 68 cf
Audi:
     0  1  2  3  4  5  6  7
    MM II II II II PP TT CC
    00 20 c0 74 57 1f 4d 2a
    00 20 c0 74 57 01 4d a2
    

- MM : Brand BRAND ID, 0x00 = Audi e-tron, 0x03 = HUF Gen 5, 0x23 = Schrader/Sensata, 0x80 = Continental
- II : Sensor ID
- PP : Pressure * 2.45 kPa
- TT : Temp - 52 C
- F1* : Warning Flags , battery, fast deflating ... not yet guess
- F2* : Sequence number, to be confirmed
- F3* : Target Nominal Pressure * 0.0245 for 0x03
- CC : CRC 8 of 10 byte, init 0xaa , poli 0x2f

* - Only for BMW, not available with Audi

Data layout after MC for HUF Gen 5:

    BRAND = 8h | SENSOR_ID = 32h      | PRESS = 8d  | TEMP = 8d  | FLAGS1 = 8h | FLAGS2 = 8h | FLAGS3 = 8d  | CRC = 8h - BMW
    BRAND = 8h | SENSOR_ID = 32h      | PRESS = 8d  | TEMP = 8d  | CRC = 8h    - AUDI

    BRAND = 03 | SENSOR_ID = 23e136a1 | PRESS = 074 | TEMP = 062 | FLAGS1 = 01 | FLAGS2 = 6b | FLAGS3 = 104 | CRC = 6b
    BRAND = 03 | SENSOR_ID = 23e136a1 | PRESS = 052 | TEMP = 061 | FLAGS1 = 01 | FLAGS2 = 74 | FLAGS3 = 104 | CRC = cf
    BRAND = 00 | SENSOR_ID = 20c07457 | PRESS = 031 | TEMP = 077 | CRC = 2a
    BRAND = 00 | SENSOR_ID = 20c07457 | PRESS = 001 | TEMP = 077 | CRC = a2
    BRAND = 00 | SENSOR_ID = 20c07457 | PRESS = 030 | TEMP = 077 | CRC = c3

Continental model:

    F1, F2, F3 to guess

Schrader/Sensata model:

    F1, F2, F3 to guess

Audi:
time      : 2024-04-07 18:34:36
model     : Audi/BMW-GEN5 type      : TPMS         Brand     : 0             id        : 20c07457
Pressure  : 46.5 kPa     Temperature: 24.0 C       msg       : 0020c07457134c55                        Integrity : CRC
*** Saving signal to file g015_433.92M_1000k.cu8 (37098 samples, 131072 bytes)
^CSignal caught, exiting!
Reattached kernel driver


*/

#include "decoder.h"

static int tpms_bmw_decode(r_device *decoder, bitbuffer_t *bitbuffer)
{
    bitbuffer_t decoded = { 0 };
    uint8_t *b;
    // preamble is aa59
    uint8_t const preamble_pattern[] = {0xaa, 0x59};

    if (bitbuffer->num_rows != 1) {
        decoder_logf(decoder, 2, __func__, "row error");
        return DECODE_ABORT_EARLY;
    }

    int pos = 0;
    pos = bitbuffer_search(bitbuffer, 0, 0, preamble_pattern, sizeof(preamble_pattern) * 8);
    if (pos >= bitbuffer->bits_per_row[0]) {
        decoder_logf(decoder, 2, __func__, "Preamble not found");
        return DECODE_ABORT_EARLY;
    }

    decoder_log_bitrow(decoder, 2, __func__, bitbuffer->bb[0], bitbuffer->bits_per_row[0], "MSG");

    bitbuffer_manchester_decode(bitbuffer, 0, pos + sizeof(preamble_pattern) * 8, &decoded, 8 * 8);

    decoder_log_bitrow(decoder, 2, __func__, decoded.bb[0], decoded.bits_per_row[0], "MC");

    if (decoded.bits_per_row[0] < 64) {
        decoder_logf(decoder, 1, __func__, "Too short");
        return DECODE_ABORT_LENGTH;
    }

    bitbuffer_invert(&decoded); // MC Zerobit
    decoder_log_bitrow(decoder, 2, __func__, decoded.bb[0], decoded.bits_per_row[0], "MC inverted");
    b = decoded.bb[0];
    // CRC for AUDI Huf
    if (crc8(b, 8, 0x2f, 0xaa)) {
        decoder_logf(decoder, 1, __func__, "crc error, expected %02x, calculated %02x", b[8], crc8(b, 8, 0x2f, 0xaa));
        return DECODE_FAIL_MIC; // crc mismatch
    }
    decoder_log(decoder, 2, __func__, "Audi/BMW found");
    int brand_id            = b[0]; // 0x00 = Audi, 0x03 = HUF Gen 5, 0x80 = Continental, 0x23 = Sensata, 0x88 = ??
    float pressure_kPa      = b[5] * 2.45;
    int temperature_C       = b[6] - 52;
    //int flags1              = b[7]; // depends on brand_id, could be pressure or SEQ ID and other WARM flags Battery , fast deflating ...
    //int flags2              = b[8]; // depends on brand_id, could be pressure and other WARM flags Battery , fast deflating ...
    //int flags3              = b[9]; // Nominal Pressure for brand HUF 0x03, depends on brand_id, could be SEQ ID and other WARM flags Battery , fast deflating ...

    char id_str[9];
    snprintf(id_str, sizeof(id_str), "%02x%02x%02x%02x", b[1], b[2], b[3], b[4]);
    char msg_str[17]; // was 23
    //snprintf(msg_str, sizeof(msg_str), "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10]);
    snprintf(msg_str, sizeof(msg_str), "%02x%02x%02x%02x%02x%02x%02x%02x", b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]); //, b[8], b[9], b[10]);
    /* clang-format off */
    data_t *data = data_make(
            "model",               "",                DATA_STRING, "Audi/BMW-GEN5",
            "type",                "",                DATA_STRING, "TPMS",
            "brand",               "Brand",           DATA_INT,    brand_id,
            "id",                  "",                DATA_STRING, id_str,
            "pressure_kPa",        "Pressure",        DATA_FORMAT, "%.1f kPa", DATA_DOUBLE, (double)pressure_kPa,
            "temperature_C",       "Temperature",     DATA_FORMAT, "%.1f C",   DATA_DOUBLE, (double)temperature_C,
            //"flags1",              "",                DATA_INT,    flags1,
            //"flags2",              "",                DATA_INT,    flags2,
            //"flags3",              "",                DATA_INT,    flags3, // Nominal Pressure for brand HUF 0x03
            "msg",                 "msg",             DATA_STRING, msg_str, // To remove after guess all tags
            "mic",                 "Integrity",       DATA_STRING, "CRC",
            NULL);
    /* clang-format on */

    decoder_output_data(decoder, data);
    return 1;
}

static char const *const output_fields[] = {
        "model",
        "type",
        "id",
        "brand",
        "battery_ok",
        "pressure_kPa",
        //"flags1",
        //"flags2",
        //"flags3",
        "msg",
        "mic",
        NULL,
};

r_device const tpms_bmw = {
        .name        = "BMW Gen5 TPMS, multi-brand HUF, Continental, Schrader/Sensata",
        .modulation  = FSK_PULSE_PCM,
        .short_width = 25,
        .long_width  = 25,
        .reset_limit = 100,
        .decode_fn   = &tpms_bmw_decode,
        .fields      = output_fields,
};
