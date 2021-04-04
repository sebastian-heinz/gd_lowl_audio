#ifndef GD_LOWL_DEVICE_H
#define GD_LOWL_DEVICE_H

#include "core/object/reference.h"

#include "gd_lowl_error.h"
#include "gd_lowl_audio_mixer.h"

#include "lowl_device.h"

class GdLowlDevice : public Reference {
GDCLASS(GdLowlDevice, Reference);
OBJ_CATEGORY("Lowl Audio");

private:
    GdLowlDevice() {
        // ClassDB::register_class<GdLowlDevice>();
        device = nullptr;
    };

private:
    Lowl::Device *device;

protected:
    static void _bind_methods();

public:
    String get_name() const;

    GdLowlError::Code start_mixer(const Ref<GdLowlAudioMixer> &p_mixer);

    GdLowlError::Code stop();

    GdLowlDevice(Lowl::Device *p_device);

    ~GdLowlDevice();
};

#endif //GD_LOWL_DEVICE_H
