#include "gd_lowl_audio_mixer.h"

void GdLowlAudioMixer::_bind_methods() {
    ClassDB::add_virtual_method(get_class_static(), MethodInfo("_init"));
    ClassDB::bind_method(D_METHOD("mix", "audio_source"), &GdLowlAudioMixer::mix);
}

std::shared_ptr<Lowl::AudioMixer> GdLowlAudioMixer::get_audio_mixer() const {
    return audio_mixer;
}

GdLowlAudioMixer::GdLowlAudioMixer(std::shared_ptr<Lowl::AudioMixer> p_audio_mixer)
        : GdLowlAudioSource(p_audio_mixer) {
    audio_mixer = p_audio_mixer;
}

GdLowlAudioMixer::GdLowlAudioMixer(double p_sample_rate, int p_channel) :
        GdLowlAudioSource(std::make_shared<Lowl::AudioMixer>(p_sample_rate, Lowl::get_channel(p_channel))) {
    audio_mixer = std::dynamic_pointer_cast<Lowl::AudioMixer>(get_audio_source());
}

void GdLowlAudioMixer::mix(const Ref<GdLowlAudioSource> &p_audio_source) {
    audio_mixer->mix(p_audio_source->get_audio_source());
}

GdLowlAudioMixer::GdLowlAudioMixer() : GdLowlAudioSource(nullptr) {
    audio_mixer = nullptr;
}
