#include "gd_lowl_audio_source.h"

void GdLowlAudioSource::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_sample_rate"), &GdLowlAudioSource::get_sample_rate);
    ClassDB::bind_method(D_METHOD("get_channel"), &GdLowlAudioSource::get_channel);
    ClassDB::bind_method(D_METHOD("get_sample_format"), &GdLowlAudioSource::get_sample_format);
    ClassDB::bind_method(D_METHOD("set_volume", "p_volume"), &GdLowlAudioSource::set_volume);
    ClassDB::bind_method(D_METHOD("set_panning", "p_panning"), &GdLowlAudioSource::set_panning);
    ClassDB::bind_method(D_METHOD("pause"), &GdLowlAudioSource::pause);
    ClassDB::bind_method(D_METHOD("is_pause"), &GdLowlAudioSource::is_pause);
    ClassDB::bind_method(D_METHOD("play"), &GdLowlAudioSource::play);
    ClassDB::bind_method(D_METHOD("is_play"), &GdLowlAudioSource::is_play);
    ClassDB::bind_method(D_METHOD("get_frames_remaining"), &GdLowlAudioSource::get_frames_remaining);
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

void GdLowlAudioSource::set_volume(double p_volume) {
    audio_source->set_volume(p_volume);
}

double GdLowlAudioSource::get_volume() {
    return audio_source->get_volume();
}

void GdLowlAudioSource::set_panning(double p_panning) {
    audio_source->set_panning(p_panning);
}

double GdLowlAudioSource::get_panning() {
    return audio_source->get_panning();
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

bool GdLowlAudioSource::is_pause() {
    return audio_source->is_pause();
}

void GdLowlAudioSource::pause() {
    return audio_source->pause();
}

void GdLowlAudioSource::play() {
    return audio_source->play();
}

bool GdLowlAudioSource::is_play() {
    return audio_source->is_play();
}

int GdLowlAudioSource::get_frames_remaining() {
    return audio_source->get_frames_remaining();
}