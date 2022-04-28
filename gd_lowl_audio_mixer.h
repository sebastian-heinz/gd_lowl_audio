#ifndef GD_LOWL_AUDIO_MIXER_H
#define GD_LOWL_AUDIO_MIXER_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"

#include "gd_lowl_error.h"
#include "gd_lowl_audio_source.h"

#include "audio/lowl_audio_mixer.h"

#include <memory>


class GdLowlAudioMixer : public GdLowlAudioSource {
GDCLASS(GdLowlAudioMixer, GdLowlAudioSource);

private:
    std::shared_ptr<Lowl::Audio::AudioMixer> audio_mixer;

protected:
    static void _bind_methods();

public:
    void mix(const Ref<GdLowlAudioSource> &p_audio_source);

    void remove(const Ref<GdLowlAudioSource> &p_audio_source);

    std::shared_ptr<Lowl::Audio::AudioMixer> get_audio_mixer() const;

    GdLowlAudioMixer();

    GdLowlAudioMixer(std::shared_ptr<Lowl::Audio::AudioMixer> p_audio_mixer);

    GdLowlAudioMixer(int p_channel, double p_sample_rate);

    ~GdLowlAudioMixer() = default;
};

#endif //GD_LOWL_AUDIO_MIXER_H
