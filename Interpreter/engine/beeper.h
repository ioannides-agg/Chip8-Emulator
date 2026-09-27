#ifndef BEEPER_H
#define BEEPER_H

#include "SDL3/SDL.h"

class Beeper {
public:
    Beeper() {
        SDL_AudioSpec spec{SDL_AUDIO_F32, 1, sample_rate};
        stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, generate, this);
        if (stream == NULL) {
            SDL_Log("Could not open audio device, sound disabled: %s", SDL_GetError());
        }
    }

    ~Beeper() {
        SDL_Log("Destroying Beeper!");
        SDL_DestroyAudioStream(stream);
    }

    Beeper(const Beeper &) = delete;
    Beeper &operator=(const Beeper &) = delete;

    void setPlaying(bool play) {
        if (stream == NULL || play == playing) return;

        if (play) SDL_ResumeAudioStreamDevice(stream);
        else SDL_PauseAudioStreamDevice(stream);

        playing = play;
    }

private:
    static constexpr int sample_rate = 44100;
    static constexpr float frequency = 440.0f;
    static constexpr float volume = 0.1f;

    static void SDLCALL generate(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) {
        Beeper *beeper = static_cast<Beeper *>(userdata);
        float samples[256];
        int remaining = additional_amount / (int)sizeof(float);

        while (remaining > 0) {
            int count = remaining < 256 ? remaining : 256;

            for (int i = 0; i < count; i++) {
                samples[i] = beeper->phase < 0.5f ? volume : -volume;
                beeper->phase += frequency / sample_rate;
                if (beeper->phase >= 1.0f) beeper->phase -= 1.0f;
            }

            SDL_PutAudioStreamData(stream, samples, count * (int)sizeof(float));
            remaining -= count;
        }
    }

    SDL_AudioStream *stream;
    float phase = 0.0f;
    bool playing = false;
};

#endif
