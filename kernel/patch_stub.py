import sys
import struct
import os

crcs_12_5_10 = {
    b"__crc_ps_enable_register_notifier": 0x19bf875d,
    b"__crc_alsps_driver_add": 0x25d4edbc,
    b"__crc_ps_tpd": 0x47608a38,
    b"__crc_ps_register_recive_touch_event_callback": 0x555e3ed4,
    b"__crc_ps_register_data_path": 0x8e095863,
    b"__crc_ps_register_control_path": 0x9f6a0647,
}

crcs_15_6_6 = {
    b"__crc_ps_enable_register_notifier": 0xdae3234b,
    b"__crc_alsps_driver_add": 0x74197156,
    b"__crc_ps_tpd": 0x44dbb88d,
    b"__crc_ps_register_recive_touch_event_callback": 0x555e3ed4,
    b"__crc_ps_register_data_path": 0x8e095863,
    b"__crc_ps_register_control_path": 0x9f6a0647,
    b"__crc_register_hq_notify": 0xaa60d83c,
    b"__crc_unregister_hq_notify": 0xd7ea9bc3,
}

def patch_elf_symtab(ko_path, kmi):
    if kmi == "android15-6.6":
        target_crcs = crcs_15_6_6
    else:
        target_crcs = crcs_12_5_10
        
    with open(ko_path, 'rb') as f:
        data = bytearray(f.read())
        
    if data[:4] != b'\x7fELF':
        print("Not an ELF file")
        return False
        
    e_shoff, = struct.unpack('<Q', data[40:48])
    e_shentsize, = struct.unpack('<H', data[58:60])
    e_shnum, = struct.unpack('<H', data[60:62])
    e_shstrndx, = struct.unpack('<H', data[62:64])
    
    shstrndx_off = e_shoff + e_shstrndx * e_shentsize
    sh_offset, sh_size = struct.unpack('<QQ', data[shstrndx_off+24:shstrndx_off+40])
    
    symtab_off, symtab_size = 0, 0
    strtab_off, strtab_size = 0, 0
    
    for i in range(e_shnum):
        sec_hdr = e_shoff + i * e_shentsize
        sh_name, sh_type = struct.unpack('<II', data[sec_hdr:sec_hdr+8])
        name = data[sh_offset + sh_name:].split(b'\0')[0]
        
        offset, size = struct.unpack('<QQ', data[sec_hdr+24:sec_hdr+40])
        
        if name == b'.symtab':
            symtab_off, symtab_size = offset, size
        elif name == b'.strtab':
            strtab_off, strtab_size = offset, size
            
    if not symtab_off or not strtab_off:
        print("No symtab or strtab")
        return False
        
    print(f".symtab offset: {hex(symtab_off)}, size: {symtab_size}")
    print(f".strtab offset: {hex(strtab_off)}, size: {strtab_size}")
    
    num_syms = symtab_size // 24
    patched = 0
    
    for i in range(num_syms):
        sym_off = symtab_off + i * 24
        st_name, = struct.unpack('<I', data[sym_off:sym_off+4])
        
        if st_name == 0:
            continue
            
        name_start = strtab_off + st_name
        name_bytes = bytes(data[name_start:].split(b'\0')[0])
        
        if name_bytes in target_crcs:
            old_val, = struct.unpack('<Q', data[sym_off+8:sym_off+16])
            new_val = target_crcs[name_bytes]
            data[sym_off+8:sym_off+16] = struct.pack('<Q', new_val)
            print(f"Patched {name_bytes.decode()}: {hex(old_val)} -> {hex(new_val)}")
            patched += 1
            
    print(f"Total patched: {patched}")
    
    with open(ko_path, 'wb') as f:
        f.write(data)
        
    return patched > 0

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage: patch_stub.py <path_to_ko> <kmi>")
        sys.exit(1)
        
    patch_elf_symtab(sys.argv[1], sys.argv[2])
