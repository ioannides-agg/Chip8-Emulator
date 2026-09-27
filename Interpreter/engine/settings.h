#ifndef SETTINGS_H
#define SETTINGS_H

class DisplaySettings {
public:
    explicit DisplaySettings(int scale) : scale(scale < 1 ? 1 : scale) {}
    int width()  const { return chip8_width  * scale; }
    int height() const { return chip8_height * scale; }
    int tile_size() const { return scale; } // since each pixel is one tile

private:
    int scale;
    static constexpr int chip8_width  = 64;
    static constexpr int chip8_height = 32;
};

#endif
