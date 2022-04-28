#ifndef GD_LOWL_DRIVER_H
#define GD_LOWL_DRIVER_H

#include "core/object/class_db.h"
#include "core/object/ref_counted.h"

#include "gd_lowl_error.h"
#include "gd_lowl_device.h"

#include "audio/lowl_audio_driver.h"
#include "audio/lowl_audio_device.h"

#include <memory>

class GdLowlDriver : public RefCounted {
GDCLASS(GdLowlDriver, RefCounted);

private:
    GdLowlDriver() {
        //ClassDB::register_class<GdLowlDriver>();
        driver = nullptr;
    };

private:
    std::shared_ptr<Lowl::Audio::AudioDriver> driver;
    std::vector<Ref<GdLowlDevice>> devices;
    Ref<GdLowlDevice> default_device;

protected:
    static void _bind_methods();

public:
    Array get_devices() const;

    Ref<GdLowlDevice> get_default_device() const;

    String get_name() const;

    GdLowlError::Code initialize();

    GdLowlDriver(std::shared_ptr<Lowl::Audio::AudioDriver> p_driver);

    ~GdLowlDriver();
};

#endif //GD_LOWL_DRIVER_H
