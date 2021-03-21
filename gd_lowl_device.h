#ifndef GD_LOWL_DEVICE_H
#define GD_LOWL_DEVICE_H

#include "gd_lowl_error.h"
#include "lowl_device.h"

#include "core/object/reference.h"

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
    String bind_get_name() const;

public:
    GdLowlError::Code play();

    GdLowlError::Code start();

    GdLowlError::Code stop();

    std::string get_name() const;

    GdLowlDevice(Lowl::Device *p_device);

    ~GdLowlDevice();
};


#endif //GD_LOWL_DEVICE_H
