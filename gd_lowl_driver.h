#ifndef GD_LOWL_DRIVER_H
#define GD_LOWL_DRIVER_H

#include "gd_lowl_error.h"
#include "gd_lowl_device.h"

#include <lowl.h>

#include "core/object/reference.h"

class GdLowlDriver : public Reference {
GDCLASS(GdLowlDriver, Reference);
OBJ_CATEGORY("Lowl Audio");

private:
    GdLowlDriver() {
        // ClassDB::register_class<GdLowlDriver>();
        driver = nullptr;
    };

private:
    Lowl::Driver *driver;
    std::vector<Ref<GdLowlDevice>> devices;

protected:
    static void _bind_methods();

public:
    Array bind_get_devices() const;
    String bind_get_name() const;

public:
    GdLowlError::Code initialize();

    std::vector<Ref<GdLowlDevice>> get_devices() const;

    std::string get_name() const;

    GdLowlDriver(Lowl::Driver *p_driver);

    ~GdLowlDriver();
};

#endif //GD_LOWL_DRIVER_H
