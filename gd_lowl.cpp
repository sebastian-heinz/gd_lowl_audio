#include "gd_lowl.h"

#include "lowl.h"

GdLowl *GdLowl::singleton = nullptr;

GdLowl *GdLowl::get_singleton() {
    return singleton;
}

void GdLowl::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_drivers"), &GdLowl::get_drivers);
    ClassDB::bind_method(D_METHOD("init"), &GdLowl::init);
    ClassDB::bind_method(D_METHOD("finish"), &GdLowl::finish);
    ClassDB::bind_method(D_METHOD("create_mixer", "channel", "sample_rate"), &GdLowl::create_mixer);
    ClassDB::bind_method(D_METHOD("create_data", "channel", "sample_rate", "audio_frames"), &GdLowl::create_data);
    ClassDB::bind_method(D_METHOD("create_space", "channel", "sample_rate"), &GdLowl::create_space);
    ClassDB::bind_method(D_METHOD("create_data_from_path", "p_audio_path"), &GdLowl::create_data_from_path);
    ClassDB::bind_method(D_METHOD("get_default_device"), &GdLowl::get_default_device);
}

GdLowl::GdLowl() {
    drivers = std::vector<Ref<GdLowlDriver>>();
    singleton = this;
}

GdLowl::~GdLowl() {

}

Array GdLowl::get_drivers() {
    Array gd_drivers = Array();
    for (Ref<GdLowlDriver> driver : drivers) {
        gd_drivers.push_back(driver);
    }
    return gd_drivers;
}

GdLowlError::Code GdLowl::finish() {
    Lowl::Error error;
    Lowl::Lib::terminate(error);
    if (error.has_error()) {
        print_error(vformat("GdLowl::~GdLowl: error: %d", error.get_error_code()));
        return GdLowlError::convert(error.get_error());
    }
    return GdLowlError::NoError;
}

GdLowlError::Code GdLowl::init() {
    Lowl::Error error;
    Lowl::Lib::initialize(error);
    if (error.has_error()) {
        print_error(vformat("GdLowl::GdLowl:initialize: error: %d", error.get_error_code()));
        return GdLowlError::convert(error.get_error());
    }
    std::vector<std::shared_ptr<Lowl::Driver>> lowl_drivers = Lowl::Lib::get_drivers(error);
    if (error.has_error()) {
        print_error(vformat("GdLowl::GdLowl:get_drivers: error: %d", error.get_error_code()));
        return GdLowlError::convert(error.get_error());
    }
    for (std::shared_ptr<Lowl::Driver> lowl_driver : lowl_drivers) {
        GdLowlDriver *gd_driver = memnew(GdLowlDriver(lowl_driver));
        Ref<GdLowlDriver> gd_driver_ref = Ref<GdLowlDriver>(gd_driver);
        drivers.push_back(gd_driver_ref);
    }
    return GdLowlError::Code::NoError;
}

Ref<GdLowlAudioMixer> GdLowl::create_mixer(int p_channel, double p_sample_rate) {
    return Ref<GdLowlAudioMixer>(memnew(GdLowlAudioMixer(p_channel, p_sample_rate)));
}

Ref<GdLowlAudioData> GdLowl::create_data(int p_channel, double p_sample_rate, Array p_audio_frames) {
    return Ref<GdLowlAudioData>(memnew(GdLowlAudioData(p_audio_frames, p_sample_rate, p_channel)));
}

Ref<GdLowlSpace> GdLowl::create_space(int p_channel, double p_sample_rate) {
    return Ref<GdLowlSpace>(memnew(GdLowlSpace(p_channel, p_sample_rate)));
}

Ref<GdLowlAudioData> GdLowl::create_data_from_path(String p_audio_path) {
    Lowl::Error error;
    std::unique_ptr<Lowl::AudioData> data = Lowl::Lib::create_data(p_audio_path.utf8().get_data(), error);
    if (error.has_error()) {
        return Ref<GdLowlAudioData>();
    }
    return Ref<GdLowlAudioData>(memnew(GdLowlAudioData(std::move(data))));
}

Ref<GdLowlDevice> GdLowl::get_default_device() const {
    for (auto it = drivers.rbegin(); it != drivers.rend(); ++it) {
        Ref<GdLowlDevice> default_device = (*it)->get_default_device();
        if (default_device.is_valid()) {
            return default_device;
        }
    }
    return Ref<GdLowlDevice>();
}
