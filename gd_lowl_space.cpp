#include "gd_lowl_space.h"

void GdLowlSpace::_bind_methods() {
    ClassDB::bind_method(D_METHOD("play_audio", "space_id"), &GdLowlSpace::play_audio);
    ClassDB::bind_method(D_METHOD("play_audio_ex", "space_id", "volume", "panning"), &GdLowlSpace::play_audio_ex);
    ClassDB::bind_method(D_METHOD("stop_audio", "space_id"), &GdLowlSpace::stop_audio);
    ClassDB::bind_method(D_METHOD("add_audio_path", "path"), &GdLowlSpace::add_audio_path);
    ClassDB::bind_method(D_METHOD("add_audio_data", "data"), &GdLowlSpace::add_audio_data);
    ClassDB::bind_method(D_METHOD("set_audio_volume", "space_id", "volume"), &GdLowlSpace::set_audio_volume);
    ClassDB::bind_method(D_METHOD("set_audio_panning", "space_id", "panning"), &GdLowlSpace::set_audio_panning);
    ClassDB::bind_method(D_METHOD("reset_audio", "space_id"), &GdLowlSpace::reset_audio);
    ClassDB::bind_method(D_METHOD("seek_audio_time", "space_id", "time_seconds"), &GdLowlSpace::seek_audio_time);
    ClassDB::bind_method(D_METHOD("seek_audio_frame", "space_id", "frame"), &GdLowlSpace::seek_audio_frame);
}

GdLowlSpace::GdLowlSpace(int p_channel, double p_sample_rate)
        : GdLowlAudioSource(std::make_shared<Lowl::Space>(p_sample_rate, Lowl::get_channel(p_channel))) {
    space = std::dynamic_pointer_cast<Lowl::Space>(get_audio_source());
}

GdLowlSpace::GdLowlSpace()
        : GdLowlAudioSource(nullptr) {
    space = nullptr;
}

Lowl::SpaceId GdLowlSpace::add_audio_data(const Ref<GdLowlAudioData> &p_audio_data) {
    Lowl::Error err;
    std::shared_ptr<Lowl::AudioData> audio_data = p_audio_data->get_audio_data();
    if (!audio_data) {
        return Lowl::Space::InvalidSpaceId;
    }
    std::unique_ptr<Lowl::AudioData> audio_data_copy = std::make_unique<Lowl::AudioData>(
            audio_data->get_frames(),
            audio_data->get_sample_rate(),
            audio_data->get_channel()
    );
    Lowl::SpaceId id = space->add_audio(std::move(audio_data_copy), err);
    if (err.has_error()) {
        //   error = GdLowlError::convert(err.get_error());
        return Lowl::Space::InvalidSpaceId;
    }
    // error = GdLowlError::NoError;
    return id;
}

Lowl::SpaceId GdLowlSpace::add_audio_path(const String &p_path) {
    Lowl::Error err;
    if (p_path.is_empty()) {
        return Lowl::Space::InvalidSpaceId;
    }
    Lowl::SpaceId id = space->add_audio(p_path.utf8().get_data(), err);
    if (err.has_error()) {
        //  error = GdLowlError::convert(err.get_error());
        return Lowl::Space::InvalidSpaceId;
    }
    //error = GdLowlError::NoError;
    return id;
}

void GdLowlSpace::play_audio_ex(Lowl::SpaceId p_id, double p_volume, double p_panning) {
    space->play(p_id, p_volume, p_panning);
}

void GdLowlSpace::play_audio(Lowl::SpaceId p_id) {
    space->play(p_id);
}

void GdLowlSpace::stop_audio(Lowl::SpaceId p_id) {
    space->stop(p_id);
}

void GdLowlSpace::set_audio_volume(Lowl::SpaceId p_id, double p_volume) {
    space->set_volume(p_id, p_volume);
}

void GdLowlSpace::set_audio_panning(Lowl::SpaceId p_id, double p_panning) {
    space->set_panning(p_id, p_panning);
}

void GdLowlSpace::reset_audio(Lowl::SpaceId p_id) {
    space->reset(p_id);
}

void GdLowlSpace::seek_audio_time(Lowl::SpaceId p_id, double p_seconds) {
    space->seek_time(p_id, p_seconds);
}

void GdLowlSpace::seek_audio_frame(Lowl::SpaceId p_id, int p_frame) {
    space->seek_frame(p_id, p_frame);
}