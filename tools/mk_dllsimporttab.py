import argparse
from pathlib import Path
import shutil
import struct
from typing import TextIO
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import SymbolTableSection
from io import BufferedWriter

class ScriptException(Exception):
    pass

def make(core_elf: ELFFile, output: BufferedWriter, output_txt: TextIO, dll_dir: Path, dlls: list[Path]):
    dll_dir.mkdir(parents=True, exist_ok=True)

    # Collect imports and finalize DLLs
    symbols_index_map: dict[str, int] = {}
    combined_imports: list[str] = []

    # TODO: this assumes DLLs are passed in order on the command line
    dllno = 1
    for dll_path in dlls:
        # Read import list for DLL
        imports_txt_path = dll_path.with_suffix(f"{dll_path.suffix}.imports.txt")
        if not imports_txt_path.exists():
            raise ScriptException(f"Missing DLL imports file: {imports_txt_path.as_posix()}")

        imports: list[tuple[int, str]] = []
        with open(imports_txt_path, "r", encoding="utf-8") as imports_txt:
            lineno = 0
            for line in imports_txt.readlines():
                parts = line.split(",")
                if len(parts) == 2:
                    imports.append((int(parts[0]), parts[1].strip()))
                elif len(parts) != 0:
                    raise ScriptException(f"Invalid DLL imports line '{line}' @ {imports_txt_path.as_posix()} line {lineno}")

                lineno += 1
        
        # Assign import indices to DLL
        dll_out_path = dll_dir.joinpath(f"{dllno}.dll")
        shutil.copyfile(dll_path, dll_out_path)
        with open(dll_out_path, "r+b") as dll:
            # Find GOT and calculate its length for bounds checking
            got_len = 0
            dll.seek(0x8)
            rodata_offset = struct.unpack(">I", dll.read(4))[0]
            if rodata_offset != 0xFFFF_FFFF:
                dll.seek(rodata_offset)
                while struct.unpack(">I", dll.read(4))[0] != 0xFFFF_FFFE:
                    got_len += 1
            
            # Assign imports
            for (idx, sym_name) in imports:
                if idx < 0 or idx >= got_len:
                    raise ScriptException(f"DLL import file {imports_txt_path.as_posix()} has out of bounds import GOT index: {idx} ({sym_name})")
                
                import_idx = symbols_index_map.get(sym_name)
                if import_idx == None:
                    # New symbol, add it to list
                    import_idx = len(combined_imports)
                    combined_imports.append(sym_name)
                    symbols_index_map[sym_name] = import_idx
                dll.seek(rodata_offset + (idx * 4))
                dll.write(struct.pack(">I", 0x8000_0000 + import_idx + 1))
        
        dllno += 1

    # Get core code symbols
    symtab = core_elf.get_section_by_name(".symtab")
    assert isinstance(symtab, SymbolTableSection)

    # Build DLLSIMPORTTAB.bin
    i = 1
    for sym_name in combined_imports:
        sym = symtab.get_symbol_by_name(sym_name)
        if sym == None:
            raise ScriptException(f"Unknown symbol to import: '{sym_name}'")
        if len(sym) > 1:
            raise ScriptException(f"Import symbol '{sym_name}' is ambiguous.")
        sym = sym[0]
        if sym.entry["st_shndx"] == "SHN_UNDEF":
            raise ScriptException(f"Import symbol '{sym_name}' is undefined.")

        output.write(struct.pack(">I", sym.entry["st_value"]))
        output_txt.write(f"{sym_name} = 0x{0x80000000 + i:X};\n")
        i += 1

def main():
    parser = argparse.ArgumentParser(description="Assigns import indices to DLL global offset tables and creates DLLSIMPORTTAB.bin.")
    parser.add_argument("-e", "--elf", type=str, help="Path to the core code ELF file, to resolve symbols from.", required=True)
    parser.add_argument("-o", "--output", type=str, help="Path to output DLLSIMPORTTAB.bin to.", required=True)
    parser.add_argument("-d", "--dll-dir", dest="dll_dir", type=str, help="Directory to emit individual finalized DLL files to.", required=True)
    parser.add_argument("dll", type=str, nargs="+", help="DLL files.")
    args = parser.parse_args()

    try:
        with open(args.elf, "rb") as elf_file, \
             open(args.output, "wb") as output, \
             open(f"{args.output}.txt", "w", encoding="utf-8") as output_txt, \
             ELFFile(elf_file) as elf:
            make(elf, output, output_txt, Path(args.dll_dir), [Path(p) for p in args.dll])
    except ScriptException as ex:
        print(f"ERROR: {ex}")
        exit(1)

if __name__ == "__main__":
    main()
