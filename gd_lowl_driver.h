#ifndef GD_LOWL_DRIVER_H
#define GD_LOWL_DRIVER_H

#include "core/object/class_db.h"
#include "core/object/reference.h"

#include "gd_lowl_error.h"
#include "gd_lowl_device.h"

#include "lowl_driver.h"
#include "lowl_device.h"

#include <memory>

class GdLowlDriver : public Reference {
GDCLASS(GdLowlDriver, Reference);
OBJ_CATEGORY("Lowl Audio");

private:
    GdLowlDriver() {
        //ClassDB::register_class<GdLowlDriver>();
        driver = nullptr;
    };

private:
    std::shared_ptr<Lowl::Driver> driver;
    std::vector<Ref<GdLowlDevice>> devices;

protected:
    static void _bind_methods();

public:
    Array get_devices() const;

    String get_name() const;

    GdLowlError::Code initialize();

    GdLowlDriver(std::shared_ptr<Lowl::Driver> p_driver);

    ~GdLowlDriver();
};

#endif //GD_LOWL_DRIVER_H
