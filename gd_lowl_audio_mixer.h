#ifndef GD_LOWL_AUDIO_MIXER_H
#define GD_LOWL_AUDIO_MIXER_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "gd_lowl_error.h"

#include "lowl_audio_mixer.h"

#include <memory>


class GdLowlAudioMixer : public Reference {
GDCLASS(GdLowlAudioMixer, Reference);
OBJ_CATEGORY("Lowl Audio");

private:
    std::shared_ptr<Lowl::AudioMixer> audio_mixer;
    GdLowlError::Code error_code;
    bool constructed;

protected:
    static void _bind_methods();

public:
    std::shared_ptr<Lowl::AudioMixer> get_audio_mixer() const;

    void construct(Lowl::SampleRate p_sample_rate, size_t p_channel);

    GdLowlAudioMixer();

    GdLowlAudioMixer(std::shared_ptr<Lowl::AudioMixer> p_audio_mixer);

    ~GdLowlAudioMixer();
};


#endif //GD_LOWL_AUDIO_MIXER_H
