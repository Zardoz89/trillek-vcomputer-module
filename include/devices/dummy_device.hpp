/**
 * \brief       DummyDevice for testing
 * \file        dummy_device.hpp
 * \copyright   LGPL v3
 *
 */
#ifndef __DUMMYDEVICE_HPP_
#define __DUMMYDEVICE_HPP_ 1

#include "../vcomputer.hpp"

namespace trillek {
namespace computer {

/**
 * DummyDevice for testing
 */
class DummyDevice : public Device {
public:

    DummyDevice () {
    }

    virtual ~DummyDevice() {
    }

    virtual void Reset () {
        a = b = c = d = e = 0;
    }

    /**
     * Sends (writes to CMD register) a command to the device
     * @param cmd Command value to send
     */
    virtual void SendCMD (Word cmd) {
        a = cmd;
    }

    virtual void A (Word cmd) {
        a = cmd;
    }

    virtual void B (Word cmd) {
        b = cmd;
    }

    virtual void C (Word cmd) {
        c = cmd;
    }

    virtual void D (Word cmd) {
        d = cmd;
    }

    virtual void E (Word cmd) {
        e = cmd;
    }

    virtual Word A () {
        return a;
    }

    virtual Word B () {
        return b;
    }

    virtual Word C () {
        return c;
    }

    virtual Word D () {
        return d;
    }

    virtual Word E () {
        return e;
    }

    /**
     * Device Type
     */
    virtual Byte DevType() const {
        return 0;
    }

    /**
     * Device SubType
     */
    virtual Byte DevSubType() const {
        return 1;
    }

    /**
     * Device ID
     */
    virtual Byte DevID() const {
        return 0x5A;
    }

    /**
     * Device Vendor ID
     */
    virtual DWord DevVendorID() const {
        return 0xBEEF55AA;
    }

    virtual void GetState (DeviceState* out) const {
        Device::GetState(out);
        out->set_a(this->a);
        out->set_b(this->b);
        out->set_c(this->c);
        out->set_d(this->d);
        out->set_e(this->e);
    }

    virtual bool SetState (const DeviceState* in) {
        if (! Device::SetState(in)) {
            return false;
        }
        this->a = in->a();
        this->b = in->b();
        this->c = in->c();
        this->d = in->d();
        this->e = in->e();

        return true;
    }

    Word a, b, c, d, e;
};

} // End of namespace computer
} // End of namespace trillek

#endif // __DUMMYDEVICE_HPP_
