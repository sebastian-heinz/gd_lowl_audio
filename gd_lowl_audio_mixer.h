#ifndef GD_LOWL_AUDIO_MIXER_H
#define GD_LOWL_AUDIO_MIXER_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "gd_lowl_error.h"
#include "gd_lowl_audio_source.h"

#include "lowl_audio_mixer.h"

#include <memory>


class GdLowlAudioMixer : public GdLowlAudioSource {
GDCLASS(GdLowlAudioMixer, GdLowlAudioSource);
OBJ_CATEGORY("Lowl Audio");

private:
    std::shared_ptr<Lowl::AudioMixer> audio_mixer;

protected:
    static void _bind_methods();

public:
    void mix(const Ref<GdLowlAudioSource> &p_audio_source);

    std::shared_ptr<Lowl::AudioMixer> get_audio_mixer() const;

    GdLowlAudioMixer();

    GdLowlAudioMixer(std::shared_ptr<Lowl::AudioMixer> p_audio_mixer);

    GdLowlAudioMixer(double p_sample_rate, int p_channel);

    ~GdLowlAudioMixer() = default;
};

#endif //GD_LOWL_AUDIO_MIXER_H
