#include "gd_lowl_audio_data.h"
#include "lowl_audio_reader.h"

void GdLowlAudioData::_bind_methods() {
    ClassDB::bind_method(D_METHOD("cancel_read"), &GdLowlAudioData::cancel_read);
    ClassDB::bind_method(D_METHOD("reset_read"), &GdLowlAudioData::reset_read);
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

GdLowlAudioData GdLowlAudioData::create_slice(double begin_sec, double end_sec) {
    Lowl::AudioData slice = audio_data->create_slice(begin_sec, end_sec);
    return GdLowlAudioData(std::make_shared<Lowl::AudioData>(slice));
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

GdLowlAudioData::GdLowlAudioData(String p_audio_path) :
        GdLowlAudioSource(Lowl::AudioReader::create_data(p_audio_path.utf8().get_data(), err)) {
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