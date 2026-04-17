#include <iostream>
#include <cstdint>  // For uint32_t (Standard 32-bit integers)
#include <cmath>    // For log2
#include <iomanip>  // For hex printing

using namespace std;

// ==========================================
// 1. SYSTEM CONFIGURATION
// ==========================================
struct SystemConfig {
    uint32_t ram_size_kb;
    uint32_t page_size_bytes;
    
    // Derived values (Calculated automatically)
    uint32_t num_frames;
    uint32_t offset_bits;
    uint32_t offset_mask;

    // Constructor to initialize and calculate derived values
    SystemConfig(uint32_t ram_kb, uint32_t page_bytes) {
        ram_size_kb = ram_kb;
        page_size_bytes = page_bytes;
        
        // Calculate Total Physical Frames available
        num_frames = (ram_size_kb * 1024) / page_size_bytes;
        
        // Calculate Bitwise Shift Amount (e.g., log2(4096) = 12 bits)
        offset_bits = log2(page_size_bytes);
        
        // Calculate Bitmask (e.g., (1 << 12) - 1 = 4095 or 0xFFF)
        offset_mask = (1 << offset_bits) - 1;
    }
};

// ==========================================
// 2. PAGE TABLE ENTRY (PTE) STRUCTURE
// ==========================================
// This is what will be stored inside your Hash Map later.
struct PTE {
    bool valid = false;       // 1 if in RAM, 0 if Page Fault
    bool dirty = false;       // 1 if modified (needs disk write-back)
    uint32_t frame_number = 0; // Where is it in physical RAM?
};

// ==========================================
// 3. ADDRESS TRANSLATOR (The Math Engine)
// ==========================================
class AddressTranslator {
private:
    SystemConfig config;

public:
    // Pass the config into the translator
    AddressTranslator(SystemConfig c) : config(c) {}

    void translate(uint32_t virtual_address) {
        // FAST O(1) BITWISE OPERATIONS [WK3 Requirement]
        // 1. Shift right to drop the offset and get the VPN
        uint32_t vpn = virtual_address >> config.offset_bits;
        
        // 2. Bitwise AND to mask out the VPN and keep the offset
        uint32_t offset = virtual_address & config.offset_mask;

        // Print results to verify our math
        cout << "Virtual Address: 0x" << setfill('0') << setw(8) << hex << uppercase << virtual_address 
             << " | VPN: " << dec << vpn 
             << " | Offset: " << offset << "\n";
    }
};

// ==========================================
// 4. MAIN FUNCTION (For Testing Module 1)
// ==========================================
int main() {
    cout << "=== MMU Module 1: Bitwise Translator Booting ===" << "\n\n";

    // Setup: 256 KB RAM, 4 KB (4096 bytes) Page Size
    SystemConfig config(256, 4096);

    cout << "[System Setup]\n";
    cout << "Total Physical Frames: " << config.num_frames << "\n";
    cout << "Bit Shift Amount: " << config.offset_bits << " bits\n";
    cout << "Offset Mask: 0x" << hex << config.offset_mask << dec << "\n\n";

    AddressTranslator mmu(config);

    // Let's test with 3 sample 32-bit addresses
    cout << "[Translation Test]\n";
    mmu.translate(0x0001A3F2); // Expected VPN: 26, Offset: 1010 (0x3F2)
    mmu.translate(0x00001000); // Expected VPN: 1,  Offset: 0 (exactly 4096 in decimal)
    mmu.translate(0xFFFFFFFF); // Edge case: Max 32-bit address

    return 0;
}