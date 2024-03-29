#include "gd_lowl_audio_mixer.h"

void GdLowlAudioMixer::_bind_methods() {
    ClassDB::add_virtual_method(get_class_static(), MethodInfo("_init"));
    ClassDB::bind_method(D_METHOD("mix", "audio_source"), &GdLowlAudioMixer::mix);
    ClassDB::bind_method(D_METHOD("remove", "audio_source"), &GdLowlAudioMixer::remove);
}

std::shared_ptr<Lowl::Audio::AudioMixer> GdLowlAudioMixer::get_audio_mixer() const {
    return audio_mixer;
}

GdLowlAudioMixer::GdLowlAudioMixer(std::shared_ptr<Lowl::Audio::AudioMixer> p_audio_mixer)
        : GdLowlAudioSource(p_audio_mixer) {
    audio_mixer = p_audio_mixer;
}

GdLowlAudioMixer::GdLowlAudioMixer(int p_channel, double p_sample_rate) :
        GdLowlAudioSource(std::make_shared<Lowl::Audio::AudioMixer>(p_sample_rate, Lowl::Audio::get_channel(p_channel))) {
    audio_mixer = std::dynamic_pointer_cast<Lowl::Audio::AudioMixer>(get_audio_source());
}

void GdLowlAudioMixer::mix(const Ref<GdLowlAudioSource> &p_audio_source) {
    audio_mixer->mix(p_audio_source->get_audio_source());
}

void GdLowlAudioMixer::remove(const Ref<GdLowlAudioSource> &p_audio_source) {
    audio_mixer->remove(p_audio_source->get_audio_source());
}

GdLowlAudioMixer::GdLowlAudioMixer() : GdLowlAudioSource(nullptr) {
    audio_mixer = nullptr;
}
