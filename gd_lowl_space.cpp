#include "gd_lowl_space.h"

void GdLowlSpace::_bind_methods() {
    ClassDB::bind_method(D_METHOD("play", "space_id"), &GdLowlSpace::play);
    ClassDB::bind_method(D_METHOD("stop", "space_id"), &GdLowlSpace::stop);
    ClassDB::bind_method(D_METHOD("get_mixer"), &GdLowlSpace::get_mixer);
    ClassDB::bind_method(D_METHOD("load"), &GdLowlSpace::load);
    ClassDB::bind_method(D_METHOD("add_audio_path", "path"), &GdLowlSpace::add_audio_path);
    ClassDB::bind_method(D_METHOD("add_audio_data", "data"), &GdLowlSpace::add_audio_data);
    ClassDB::bind_method(D_METHOD("set_sample_rate", "sample_rate"), &GdLowlSpace::set_sample_rate);
    ClassDB::bind_method(D_METHOD("set_channel", "channel"), &GdLowlSpace::set_channel);
}

void GdLowlSpace::load() {
    space->load();
    mixer = Ref<GdLowlAudioMixer>(memnew(GdLowlAudioMixer(space->get_mixer())));
}

void GdLowlSpace::play(Lowl::SpaceId p_id) {
    space->play(p_id);
}

void GdLowlSpace::stop(Lowl::SpaceId p_id) {
    space->stop(p_id);
}

Ref<GdLowlAudioMixer> GdLowlSpace::get_mixer() {
    return mixer;
}

GdLowlError::Code GdLowlSpace::get_error() {
    return error;
}

void GdLowlSpace::set_sample_rate(Lowl::SampleRate p_sample_rate) {
    space->set_sample_rate(p_sample_rate);
}

void GdLowlSpace::set_channel(uint16_t p_channel) {
    space->set_channel(Lowl::get_channel(p_channel));
}

Lowl::SpaceId GdLowlSpace::add_audio_data(const Ref<GdLowlAudioData> &p_audio_data) {
    return Lowl::Space::InvalidSpaceId;
    // Lowl::Error err;
    //space->add_audio(std::move(p_audio_data), err);
    // error = GdLowlError::convert(err.get_error());
}

Lowl::SpaceId GdLowlSpace::add_audio_path(const String &p_path) {
    Lowl::Error err;
    if (p_path.is_empty()) {
        return Lowl::Space::InvalidSpaceId;
    }
    Lowl::SpaceId id = space->add_audio(p_path.utf8().get_data(), err);
    if (err.has_error()) {
        error = GdLowlError::convert(err.get_error());
        return Lowl::Space::InvalidSpaceId;
    }
    error = GdLowlError::NoError;
    return id;
}

GdLowlSpace::GdLowlSpace() {
    error = GdLowlError::NoError;
    space = std::make_unique<Lowl::Space>();
}

GdLowlSpace::~GdLowlSpace() {

}