#include "gd_lowl_audio_source.h"

void GdLowlAudioSource::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_sample_rate"), &GdLowlAudioSource::get_sample_rate);
    ClassDB::bind_method(D_METHOD("get_channel"), &GdLowlAudioSource::get_channel);
    ClassDB::bind_method(D_METHOD("get_sample_format"), &GdLowlAudioSource::get_sample_format);
}

std::shared_ptr<Lowl::AudioSource> GdLowlAudioSource::get_audio_source() const {
    return audio_source;
}

GdLowlAudioSource::GdLowlAudioSource(std::shared_ptr<Lowl::AudioSource> p_audio_source) {
    audio_source = p_audio_source;
}

int GdLowlAudioSource::get_channel() const {
    return audio_source->get_channel_num();
}

double GdLowlAudioSource::get_sample_rate() const {
    return audio_source->get_sample_rate();
}

GdLowlAudioSource::SampleFormat GdLowlAudioSource::get_sample_format() const {
    return convert_sample_format(audio_source->get_sample_format());
}

GdLowlAudioSource::SampleFormat GdLowlAudioSource::convert_sample_format(Lowl::SampleFormat sample_format) {
    return (SampleFormat) sample_format;
}

Lowl::SampleFormat GdLowlAudioSource::convert_sample_format(GdLowlAudioSource::SampleFormat sample_format) {
    return (Lowl::SampleFormat) sample_format;
}
