#include "gd_lowl_audio_data.h"

void GdLowlAudioData::_bind_methods() {
    ClassDB::bind_method(D_METHOD("cancel_read"), &GdLowlAudioData::cancel_read);
    ClassDB::bind_method(D_METHOD("reset_read"), &GdLowlAudioData::reset_read);
    ClassDB::bind_method(D_METHOD("create_slice", "begin_sec", "end_sec"), &GdLowlAudioData::create_slice);
}

void GdLowlAudioData::cancel_read() {
    audio_data->cancel_read();
}

void GdLowlAudioData::reset_read() {
    audio_data->reset_read();
}

std::shared_ptr<Lowl::AudioData> GdLowlAudioData::get_audio_data() const {
    return audio_data;
}

Ref<GdLowlAudioData> GdLowlAudioData::create_slice(double p_begin_sec, double p_end_sec) {
    std::shared_ptr<Lowl::AudioData> slice = audio_data->create_slice(p_begin_sec, p_end_sec);
    return Ref<GdLowlAudioData>(memnew(GdLowlAudioData(slice)));
}

GdLowlAudioData::GdLowlAudioData(Array p_audio_frames, double p_sample_rate, int p_channel) :
        GdLowlAudioSource(std::make_shared<Lowl::AudioData>(
                convert_frames(p_audio_frames, p_channel), p_sample_rate, Lowl::get_channel(p_channel)
        )) {
    audio_data = std::dynamic_pointer_cast<Lowl::AudioData>(get_audio_source());
}

GdLowlAudioData::GdLowlAudioData(std::shared_ptr<Lowl::AudioData> p_audio_data) :
        GdLowlAudioSource(p_audio_data) {
    audio_data = std::dynamic_pointer_cast<Lowl::AudioData>(get_audio_source());
}

GdLowlAudioData::GdLowlAudioData() :
        GdLowlAudioSource(nullptr) {
    audio_data = nullptr;
}

std::vector<Lowl::AudioFrame> GdLowlAudioData::convert_frames(Array p_audio_frames, int p_channel) {
    std::vector<Lowl::AudioFrame> frames = std::vector<Lowl::AudioFrame>();
    for (int i = 0; i < p_audio_frames.size(); i++) {
        Lowl::AudioFrame frame;
        Variant v = p_audio_frames[i];
        if (v.get_type() != Variant::PACKED_FLOAT32_ARRAY) {
            continue;
        }
        PackedFloat32Array entry = v;
        for (int j = 0; j < p_channel && j < entry.size() && j < Lowl::AudioFrame::MAX_CHANNEL; j++) {
            frame[j] = entry[j];
        }
    }
    return frames;
}