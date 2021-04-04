#include "gd_lowl_audio_mixer.h"

void GdLowlAudioMixer::_bind_methods() {
  //  ClassDB::bind_method(D_METHOD("construct"), &GdLowlAudioMixer::construct);
}

void GdLowlAudioMixer::construct(Lowl::SampleRate p_sample_rate, size_t p_channel) {
    if (constructed) {
        return;
    }
    audio_mixer = std::make_shared<Lowl::AudioMixer>(p_sample_rate, Lowl::get_channel(p_channel));
    constructed = true;
}

GdLowlAudioMixer::GdLowlAudioMixer(std::shared_ptr<Lowl::AudioMixer> p_audio_mixer) {
    audio_mixer = p_audio_mixer;
    constructed = true;
}

GdLowlAudioMixer::GdLowlAudioMixer() {
    constructed = false;
}

GdLowlAudioMixer::~GdLowlAudioMixer() {

}

std::shared_ptr<Lowl::AudioMixer> GdLowlAudioMixer::get_audio_mixer() const {
    return audio_mixer;
}
