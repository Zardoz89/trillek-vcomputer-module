/**
 * \brief       Virtual Computer Text Display Adapter
 * \file        tda.cpp
 * \copyright   LGPL v3
 *
 * Nya Elektriska Text Display Adapter
 * @see https://github.com/trillek-team/trillek-computer/blob/master/TDA.md
 */

#include "devices/tda.hpp"
#include "vs_fix.hpp"

#include <algorithm>
#include <cassert>

namespace trillek {
namespace computer {
namespace tda {

void TDAtoRGBATexture (const TDAScreen& screen, DWord* texture) {
    static unsigned frames = 0;
    TDAtoRGBATexture(screen, texture, frames);
}

void TDAtoBGRATexture (const TDAScreen& screen, DWord* texture) {
    static unsigned frames = 0;
    TDAtoBGRATexture(screen, texture, frames);
}

void TDAtoRGBATexture (const TDAScreen& screen, DWord* texture, unsigned& frames) {
    assert(texture != nullptr);

    const Byte* font = ROM_FONT;
    if (screen.user_font) {
        font = (Byte*) screen.font_buffer;
    }

    // TODO Rewrite this to be more efficient and cache friendly, as now
    // writes "jumping" in the output texture

    // Reads one by one each character of the text buffer
    for (unsigned row = 0; row < HEIGHT_CHARS; row++) {
        for (unsigned col = 0; col < WIDTH_CHARS; col++) {

            std::size_t addr = col + (WIDTH_CHARS * row);
            Byte c         = screen.txt_buffer[addr]; // character

            // Get Ink (fg) and Paper (bg) colors
            DWord fg = (screen.txt_buffer[addr] >> 8) & 0x0F; // Bits 8-11
            DWord bg = (screen.txt_buffer[addr] >> 12)& 0x0F; // bits 12-15

            // Paint the texture
            Byte pixels;
            for (unsigned y = 0; y < 8; y++) {
                pixels = font[c*8 + y];
                for (unsigned x = 0; x < 8; x++) {
                    addr = x + col*8 + ( 40*8 * (y + row*8) ); // Addres of the
                                                               // pixel in the
                                                               // buffer
                    if ( ( pixels & ( 1 << (7-x) ) ) != 0 ) {
                        // Active, uses the Ink (fg)
                        texture[addr] = PALETTE[fg];
                    }
                    else {
                        // Unactive, uses the Paper (bg)
                        texture[addr] = PALETTE[bg];
                    }
                }
            }
        }
    } // End for

    if ( screen.cursor) {
        if (frames++ < 8) {
            // Draw the cursor only when is necesary
            if (screen.cur_start <= screen.cur_end) {
                unsigned char col = screen.cur_col;
                unsigned char row = screen.cur_row;
                DWord color = PALETTE[screen.cur_color]; // Color
                if (row < 30 && col < 40) {
                    // Paints the cursor
                    std::size_t addr = col + (WIDTH_CHARS * row);
                    for (unsigned y = screen.cur_start ; y <= screen.cur_end; y++) {
                        for (unsigned x = 0; x < 8; x++) {
                            addr = x + col*8 + ( 40*8 * (y + row*8) ); // Addres of the
                                                                       // pixel in the
                                                                       // buffer
                            texture[addr] = color;
                        }
                    }
                }
            }
        } else if (frames++ < 16) {
            // Do nothing
        } else {
            frames = 0; // Reset it
        }
    }

} // TDAtoRGBATexture

void TDAtoBGRATexture (const TDAScreen& screen, DWord* texture, unsigned& frames) {
    assert(texture != nullptr);
    TDAtoRGBATexture (screen, texture, frames);

    // We interchanged B and R components
    for (unsigned i=0; i < 320*240 ; i++) {
        DWord g_a   = texture[i] & 0xFF00FF00;
        DWord red   = texture[i] & 0x000000FF;
        DWord blue  = texture[i] & 0x00FF0000;
        texture[i]  = g_a | (red << 16) | (blue >> 16);
    }
} // TDAtoBGRATexture
TDADev::TDADev () : buffer_ptr(0), font_ptr(0), vsync_msg(0), do_vsync(false),
                    cursor(false), blink(false) {
}

TDADev::~TDADev() {
}

void TDADev::Reset () {
    this->buffer_ptr = 0;
    this->font_ptr   = 0;
    this->vsync_msg  = 0;
    this->a          = 0;
    this->b          = 0;
    this->d          = 0;
    this->e          = 0;
    this->do_vsync   = false;
    this->cursor     = false;
    this->blink      = false;
}

void TDADev::SendCMD (Word cmd) {
    DWord tmp;

    switch (cmd) {
    case 0x0000: // Map Buffer
        tmp = ( (b << 16) | a );
        if ( tmp + TXT_BUFFER_SIZE < vcomp->RamSize() ) {
            buffer_ptr = tmp;
        }
        break;

    case 0x0001: // Map Font
        tmp = ( (b << 16) | a );
        if ( tmp + FONT_BUFFER_SIZE <= vcomp->RamSize() ) {
            font_ptr = tmp;
        }
        else if ( tmp - 0x100000 + FONT_BUFFER_SIZE <= vcomp->RomSize()) {
            font_ptr = tmp;
        }
        break;

    case 0x0002: // Set Int
        vsync_msg = a;
        break;

    default:
        break;
    } // switch
}     // SendCMD

bool TDADev::DoesInterrupt(Word& msg) {
    if (do_vsync && vsync_msg != 0x0000) {
        msg = vsync_msg;
        return true;
    }
    return false;
}

void TDADev::IACK () {
    do_vsync = false; // Acepted, so we can forgot now of sending it again
}

bool TDADev::IsSyncDev() const {
    return false;
}

} // End of namespace tda
} // End of namespace computer
} // End of namespace trillek

