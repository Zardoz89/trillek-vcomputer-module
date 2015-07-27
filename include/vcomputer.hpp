/**
 * \brief       Virtual Computer
 * \file        vcomputer.hpp
 * \copyright   LGPL v3
 *
 * Virtual Computer class itself
 */
#ifndef __VCOMPUTER_HPP_
#define __VCOMPUTER_HPP_ 1

#include "types.hpp"

#include "cpu.hpp"
#include "device.hpp"
#include "addr_listener.hpp"
#include "enum_and_ctrl_blk.hpp"
#include "devices/timer.hpp"
#include "devices/rng.hpp"
#include "devices/rtc.hpp"
#include "devices/nvram.hpp"
#include "devices/beeper.hpp"

#include "computer_state.pb.h"

#include <map>
#include <set>
#include <memory>
#include <cassert>

namespace trillek {
namespace computer {

const unsigned MAX_N_DEVICES = 32; /// Max number of devices attached

const std::size_t MAX_ROM_SIZE = 32*1024;   /// Max ROM size
const std::size_t MAX_RAM_SIZE = 1024*1024; /// Max RAM size

const unsigned EnumCtrlBlkSize = 20; /// Enumeration and Control registers blk size

const unsigned BaseClock = 1000000; /// Computer Base Clock rate

DECLDIR unsigned GetMajorVersion();      /// Library Major version
DECLDIR unsigned GetMinorVersion();      /// Library Minor version
DECLDIR unsigned GetPatchVersion();      /// Library Patch/Revision version
DECLDIR const char* GetBuildVersion();   /// Library "build" version

class EnumAndCtrlBlk;

/**
 * To work the virtual computer have 3 different "clock ticks" :
 *  - base clock -> at BaseClock hz (1MHz)
 *  - devices clock -> at 100KHz
 *  - cpu clock -> depend of the CPU, but <= base clock
 *
 * All public API that does in/out clock ticks on this class, are refered to base clock.
 * A device clock tick happens every 10 base clock ticks (1MHz/10 = 100KHz)
 * A CPU clock tick happens every X base clock ticks. X = BaseClock / cpu clock
 */
class VComputer {
public:

    /**
     * Creates a Virtual Computer
     * \param ram_size RAM size in BYTES
     */
	DECLDIR VComputer(std::size_t ram_size = 128 * 1024);

	DECLDIR ~VComputer();

    /**
     * Sets the CPU of the computer
     * \param cpu New CPU in the computer
     */
	DECLDIR void SetCPU(std::unique_ptr<ICPU> cpu);

    /**
     * Removes the CPU of the computer
     * \return Returns the ICPU
     */
	DECLDIR std::unique_ptr<ICPU> RmCPU();

    /**
     * Returns true if the computer have a CPU plugged
     */
	DECLDIR bool haveCpu() const;

    /**
     * Adds a Device to a slot
     * \param slot Were plug the device
     * \param dev The device to be pluged in the slot
     * \return False if the slot have a device or the slot is invalid.
     */
	DECLDIR bool AddDevice(unsigned slot, std::shared_ptr<Device> dev);

    /**
     * Gets the Device plugged in the slot
     */
	DECLDIR std::shared_ptr<Device> GetDevice(unsigned slot);

    /**
     * Remove a device from a slot
     * \param slot Slot were unplug the device
     */
	DECLDIR void RmDevice(unsigned slot);

    /**
     * CPU clock speed in Hz
     */
	DECLDIR unsigned CPUClock() const;

    /**
     * Writes a copy of the whole computer state
     * \param[out] out ComputerState object to be write
     */
	DECLDIR void GetState(ComputerState* out) const;

    /**
     * Loads state from a ComputerState object
     * \param ptr[in] ComputerState with the state information
     * \return True if can read the State data from the pointer.
     */
    DECLDIR bool SetState (const ComputerState* in);

    /**
     * Writes a copy of CPU state in a chunk of memory pointer by ptr.
     * @param ptr Pointer were to write
     * @param size Size of the chunk of memory were can write. If is
     * sucesfull, it will be set to the size of the write data.
     */
    DECLDIR void GetCPUState (void* ptr, std::size_t& size) const;

    /**
     * Sets the CPU state.
     * @param ptr Pointer were read the state information
     * @param size Size of the chunk of memory were will read.
     * @return True if can read the State data from the pointer.
     */
    DECLDIR bool SetCPUState (const void* ptr, std::size_t size);

    /**
     * Gets a pointer were is stored the ROM data
     * \param *rom Ptr to the ROM data
     * \param rom_size Size of the ROM data that must be less or equal to 32KiB.
     *******Big sizes will be ignored
     */
	DECLDIR void SetROM(const Byte* rom, std::size_t rom_size);

    /**
     * Resets the virtual machine (but not clears RAM!)
     */
	DECLDIR void Reset();

    /**
     * Power On the computer
     */
	DECLDIR void On();

    /**
     * Power Off the computer
     */
	DECLDIR void Off();

    /**
     * Return if the computer is power up
     */
	DECLDIR bool isOn() const;

    /**
     * Executes the apropaited number of Virtual Computer base clock cycles
     * in function of the elapsed time since the last call (delta time)
     *
     * \param delta Number of seconds since the last call
     * \return Number of base clock cycles executed
     */
	DECLDIR unsigned Update(const double delta);

    /**
     * Executes one instruction
     * \param delta Number of seconds since the last call
     * \return number of base clock ticks needed
     */
	DECLDIR unsigned Step(const double delta = 0);

    /**
     * Executes N clock ticks
     * \param n nubmer of base clock ticks, by default 1
     * \param delta Number of seconds since the last call
     */
	DECLDIR void Tick(unsigned n = 1, const double delta = 0);

	DECLDIR Byte ReadB(DWord addr) const {
        addr = addr & 0x00FFFFFF; // We use only 24 bit addresses

        if ( addr < ram_size ) {
            // RAM address (0x000000-0x0FFFFF)
            return ram[addr];
        }

        if ( (addr & 0xFF0000) == 0x100000 ) {
            // ROM (0x100000-0x10FFFF)
            return rom[addr & 0x00FFFF];
        }

        Range r(addr);
        auto search = listeners.find(r);
        if ( search != listeners.end() ) {
            return search->second->ReadB(addr);
        }

        return 0;
    } // ReadB

	DECLDIR Word ReadW(DWord addr) const {
        addr = addr & 0x00FFFFFF; // We use only 24 bit addresses
        size_t tmp;

        if ( addr < ram_size-1 ) {
            // RAM address
            tmp = ( (size_t)ram ) + addr;
            return ( (Word*)tmp )[0];
        }

        if ( (addr & 0xFF0000) == 0x100000 ) {
            // ROM (0x100000-0x10FFFF)
            addr &= 0x00FFFF; // Dirty tricks with pointers
            tmp   = ( (size_t)rom ) + addr;
            return ( (Word*)tmp )[0];
        }

        Range r(addr);
        auto search = listeners.find(r);
        if ( search != listeners.end() ) {
            return search->second->ReadW(addr);
        }

        return 0;
    } // ReadW

	DECLDIR DWord ReadDW(DWord addr) const {
        addr = addr & 0x00FFFFFF; // We use only 24 bit addresses
        size_t tmp;

        if ( addr < ram_size-3 ) {
            // RAM address
            tmp = ( (size_t)ram ) + addr;
            return ( (DWord*)tmp )[0];
        }

        if ( (addr & 0xFF0000) == 0x100000 ) {
            // ROM (0x100000-0x10FFFF)
            addr &= 0x00FFFF; // Dirty tricks with pointers
            tmp   = ( (size_t)rom ) + addr;
            return ( (DWord*)tmp )[0];
        }

        Range r(addr);
        auto search = listeners.find(r);
        if ( search != listeners.end() ) {
            return search->second->ReadDW(addr);
        }

        return 0;
    } // ReadDW

	DECLDIR void WriteB(DWord addr, Byte val) {
        addr = addr & 0x00FFFFFF; // We use only 24 bit addresses

        if (addr < ram_size) {
            // RAM address
            ram[addr] = val;
        }

        Range r(addr);
        auto search = listeners.find(r);
        if ( search != listeners.end() ) {
            search->second->WriteB(addr, val);
        }
    } // WriteB

	DECLDIR void WriteW(DWord addr, Word val) {
        size_t tmp;

        addr = addr & 0x00FFFFFF; // We use only 24 bit addresses

        if (addr < ram_size-1 ) {
            // RAM address
            tmp                 = ( (size_t)ram ) + addr;
            ( (Word*)tmp )[0] = val;
        }
        // TODO What hapens when there is a write that falls half in RAM and
        // half outside ?
        // I actually forbid these cases to avoid buffer overun, but should be
        // allowed and only use the apropiate portion of the data in the RAM.

        Range r(addr);
        auto search = listeners.find(r);
        if ( search != listeners.end() ) {
            search->second->WriteW(addr, val);
        }
    } // WriteW

	DECLDIR void WriteDW(DWord addr, DWord val) {
        size_t tmp;

        addr = addr & 0x00FFFFFF; // We use only 24 bit addresses

        if (addr < ram_size-3 ) {
            // RAM address
            tmp                  = ( (size_t)ram ) + addr;
            ( (DWord*)tmp )[0] = val;
        }
        // TODO What hapens when there is a write that falls half in RAM and
        // half outside ?

        Range r(addr);
        auto search = listeners.find(r);
        if ( search != listeners.end() ) {
            search->second->WriteDW(addr, val);
        }
    } // WriteDW

    /**
     * Adds an AddrListener to the computer
     * \param range Range of addresses that the listerner listens
     * \param listener AddrListener using these range
     * \return And ID oif the listener or -1 if can't add the listener
     */
	DECLDIR int32_t AddAddrListener(const Range& range, AddrListener* listener);

    /**
     * Removes an AddrListener from the computer
     * \param id ID of the address listener to remove (ID from AddAddrListener)
     * \return True if can find these listener and remove it.
     */
	DECLDIR bool RmAddrListener(int32_t id);

    /**
     * Size of the RAM in bytes
     */
	DECLDIR std::size_t RamSize() const {
        return ram_size;
    }

    /**
     * Size of the ROM in bytes
     */
	DECLDIR std::size_t RomSize() const {
        return rom_size;
    }

    /**
     * Returns a pointer to the RAM for reading raw values from it
     * Use only for GetState methods or dump a snapshot of the computer state
     */
	DECLDIR const Byte* Ram() const {
        return ram;
    }

	DECLDIR const Byte* Rom() const {
        return rom;
    }

    /**
     * Returns a pointer to the RAM for writing raw values to it
     * Use only for SetState methods or load a snapshot of the computer state
     */
	DECLDIR Byte* Ram() {
        return ram;
    }

    /**
     * /brief Assing a function to be called when Beeper freq is changed
     * /param f_changed function to be called
     */
	DECLDIR void SetFreqChangedCB(std::function<void(DWord freq)> f_changed) {
        beeper.SetFreqChangedCB(f_changed);
    }

    /**
     * Returns true if NVRAM have a unsaved changed
     */
	DECLDIR bool isDirtyNVRAM();

    /**
     * Fills NVRAM with data from a input stream
     * \param stream Stream were to read the data
     * \return True if read data from the strean
     */
	DECLDIR bool LoadNVRAM(std::istream& stream);

    /**
     * Saves NVRAM data to a output stream
     * \param stream Stream were to write the data
     * \return True if writed data to the stream
     */
	DECLDIR bool SaveNVRAM(std::ostream& stream);

    /**
     * Add a breakpoint at the desired address
     * \param addr Address were will be the breakpoint
     */
	DECLDIR void SetBreakPoint(DWord addr);

    /**
     * Erase a breakpoint at the desired address
     * \param addr Address were will be the breakpoint
     */
	DECLDIR void RmBreakPoint(DWord addr);

    /**
     * Remove all breakpoints
     */
	DECLDIR void ClearBreakPoints();

    /**
     * Check if there isa breakpoint at an particular address
     * \param addr Address to verify
     * \return True if there is a breakpoint in these address
     */
	DECLDIR bool isBreakPoint(DWord addr);

    /**
     * Check if the Virtual Computer is halted by a breakpoint
     * \return True if a breakpoint happened
     */
	DECLDIR bool isHalted();

    /**
     * Allows to continue if a Breakpoint happened
     */
	DECLDIR void Resume();

private:

    bool is_on;                               /// Is PowerOn the computer ?
    Byte* ram;                              /// Computer RAM
    const Byte* rom;                        /// Computer ROM chip (could be
                                              // shared between some
                                              // VComputers)
    std::size_t ram_size;                     /// Computer RAM size
    std::size_t rom_size;                     /// Computer ROM size
    std::unique_ptr<ICPU> cpu;                /// Virtual CPU
    device_t devices[MAX_N_DEVICES];          /// Devices atached to the
                                              // virtual computer
    std::map<Range, AddrListener*> listeners; /// Container of AddrListeners

    Timer pit;     /// Programable Interval Timer
    RNG rng;       /// Random Number Generator
    RTC rtc;       /// Real Time Clock
    NVRAM nvram;   /// No Volatile RAM (NVRAM)
    Beeper beeper; /// Real Time Clock

    std::set<DWord> breakpoints; /// Breakpoints list
    bool breaking;               /// The Virtual Computer is halted in a
                                 // BreakPoint ?

    DWord last_break;   /// Address of the last breakpoint finded
    bool recover_break; /// Flag to know if a recovered the temporaly erases
                        // break
};

} // End of namespace computer
} // End of namespace trillek

#endif // __VCOMPUTER_HPP_

