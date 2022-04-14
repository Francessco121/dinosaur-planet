#!/usr/bin/env python3

import argparse
import os
from pathlib import Path
import shutil
import subprocess
import sys

TARGET = "dino"

SCRIPT_DIR = Path(os.path.dirname(os.path.realpath(__file__)))
ASM_PATH = SCRIPT_DIR.joinpath("asm/")
BIN_PATH = SCRIPT_DIR.joinpath("bin/")
BUILD_PATH = SCRIPT_DIR.joinpath("build/")
TOOLS_PATH = SCRIPT_DIR.joinpath("tools/")

BUILD_SCRIPT_PATH = SCRIPT_DIR.joinpath("build.ninja")

# Paths to directories/files to delete when cleaning
CLEAN_PATHS = [
    ASM_PATH,
    BIN_PATH,
    BUILD_PATH,
    BUILD_SCRIPT_PATH,
    SCRIPT_DIR.joinpath(".ninja_log"),
    SCRIPT_DIR.joinpath(f"{TARGET}.ld"),
    SCRIPT_DIR.joinpath("undefined_funcs_auto.txt"),
    SCRIPT_DIR.joinpath("undefined_syms_auto.txt"),
]

BUILD_ARTIFACTS = [
    BUILD_PATH,
    SCRIPT_DIR.joinpath(".ninja_log"),
]

SPLIT_PY = TOOLS_PATH.joinpath("splat/split.py")
DINO_DLL_PY = TOOLS_PATH.joinpath("dino_dll.py")
CONFIGURE_PY = TOOLS_PATH.joinpath("configure.py")
DIFF_PY = TOOLS_PATH.joinpath("asm_differ/diff.py")
M2CTX_PY = TOOLS_PATH.joinpath("m2ctx.py")

class DinoCommandRunner:
    def __init__(self, verbose: bool) -> None:
        self.verbose = verbose

    def clean(self):
        print("Cleaning...")
        for path in CLEAN_PATHS:
            if not path.exists():
                continue
            
            if self.verbose:
                print(f"  Removing {path.relative_to(SCRIPT_DIR)}...")
            if path.is_dir():
                shutil.rmtree(path)
            else:
                path.unlink()

    def update_submodules(self):
        print("Updating Git submodules...")
        self.__run_cmd(["git", "submodule", "update", "--init", "--recursive"])

    def extract(self):
        print("Extracting...")

        if ASM_PATH.exists():
            shutil.rmtree(ASM_PATH)
        if BIN_PATH.exists():
            shutil.rmtree(BIN_PATH)
        
        self.__run_cmd([
            "python3", str(SPLIT_PY), 
            "--target", "baserom.z64", 
            "--basedir", str(SCRIPT_DIR), 
            "splat.yaml"
        ])
        
        self.__run_cmd([
            "python3", str(DINO_DLL_PY), 
            "unpack",
            str(BIN_PATH.joinpath("assets/dlls")),
            str(BIN_PATH.joinpath("assets/DLLS.bin")),
            str(BIN_PATH.joinpath("assets/DLLS_tab.bin"))
        ])

    def configure(self, skip_dlls: bool):
        print("Configuring build script...")

        self.__assert_project_built()
        
        args = [
            "python3", str(CONFIGURE_PY), 
            "--base-dir", str(SCRIPT_DIR),
            "--target", TARGET
        ]
        if skip_dlls:
            args.append("--skip-dlls")

        self.__run_cmd(args)

    def build(self, configure: bool, force: bool):
        if configure or not BUILD_SCRIPT_PATH.exists():
            # TODO: build --configure doesn't respect --skip-dlls
            self.configure(skip_dlls=False)
            print()
        
        if force:
            for path in BUILD_ARTIFACTS:
                if not path.exists():
                    continue
                
                if path.is_dir():
                    shutil.rmtree(path)
                else:
                    path.unlink()

        print("Building ROM...")
        
        args = ["ninja"]
        if SCRIPT_DIR != Path.cwd():
            args.extend(["-C", str(SCRIPT_DIR)])
        if self.verbose:
            args.append("-v")
        
        self.__run_cmd(args)

        print()
        self.verify()

    def baseverify(self):
        print("Verifying base ROM...")

        baserom_path = SCRIPT_DIR.joinpath("baserom.z64")
        if not baserom_path.exists():
            print(f"Missing base ROM! Ensure the real Dinosaur Planet ROM exists at {baserom_path.relative_to(SCRIPT_DIR)}.")
            sys.exit(1)
        
        self.__run_cmd(["md5sum", "-c", "baserom.md5"])

    def verify(self):
        print("Verifying re-built ROM...")

        rom_path = SCRIPT_DIR.joinpath(f"build/{TARGET}.z64")
        if not rom_path.exists():
            print(f"Missing re-built ROM! Ensure the project has been built and that {rom_path.relative_to(SCRIPT_DIR)} exists.")
            sys.exit(1)
        
        self.__run_cmd(["md5sum", "-c", "checksum.md5"])

    def setup(self):
        print("Welcome to the Dinosaur Planet decompilation project!")
        print()
        self.update_submodules()
        print()
        self.baseverify()
        print()
        self.extract()
        print()
        invoked_as = sys.argv[0]
        if not invoked_as.endswith(".py"):
            # Assume the script was invoked via something like a path symlink,
            # just print the name instead of the potentially full path
            invoked_as = Path(invoked_as).name
        print(f"Done! Run '{invoked_as} build' to build the ROM.")
    
    def diff(self, show_help: bool, args: "list[str]"):
        self.__assert_project_built()

        # Need to run diff from the project root where diff_settings.py is
        os.chdir(SCRIPT_DIR)

        if show_help:
            args.append("-h")

        args.insert(0, str(DIFF_PY))
        self.__run_cmd(args)
    
    def make_context(self, file: str):
        self.__run_cmd([str(M2CTX_PY), file])
        print(f"Created context file at {SCRIPT_DIR.joinpath('ctx.c')}")
    
    def __assert_project_built(self):
        linker_script_path = SCRIPT_DIR.joinpath(f"{TARGET}.ld")
        if not linker_script_path.exists():
            print(f"Could not find linker script at {linker_script_path}. Is the ROM extracted?")
            sys.exit(1)

    def __run_cmd(self, args: "str | list[str]"):
        if self.verbose:
            print(">", " ".join(args))
        subprocess.check_call(args)

def main():
    parser = argparse.ArgumentParser(description="Quick commands for working on the Dinosaur Planet decompilation.")
    parser.add_argument("-v", "--verbose", action="store_true", help="Show actual commands being ran.", default=False)

    subparsers = parser.add_subparsers(dest="command", required=True)
    subparsers.add_parser("setup", help="Initialize/update Git submodules, verify the base ROM, and extract the ROM.")
    subparsers.add_parser("extract", help="Split ROM and unpack DLLs.")
    build_cmd = subparsers.add_parser("build", help="Build ROM and verify that it matches.")
    build_cmd.add_argument("-c", "--configure", action="store_true", help="Re-configure the build script before building.", default=False)
    build_cmd.add_argument("-f", "--force", action="store_true", help="Force a full rebuild.", default=False)
    configure_cmd = subparsers.add_parser("configure", help="Re-configure the build script.")
    configure_cmd.add_argument("--skip-dlls", dest="skip_dlls", action="store_true", help="Don't recopile DLLs (use original)", default=False)
    subparsers.add_parser("verify", help="Verify that the re-built ROM matches the base ROM.")
    subparsers.add_parser("baseverify", help="Verify that the base ROM is correct.")
    subparsers.add_parser("clean", help="Remove extracted files, build artifacts, and build scripts.")
    subparsers.add_parser("submodules", help="Initialize and update Git submodules.")
    diff_cmd = subparsers.add_parser("diff", help="Diff the re-rebuilt ROM with the original (redirects to asm-differ).", conflict_handler="resolve")
    diff_cmd.add_argument("-h", "--help", action="store_true", default=False)
    diff_cmd.add_argument("args", nargs=argparse.REMAINDER)
    ctx_cmd = subparsers.add_parser("context", help="Create a context file that can be used for mips2c/decomp.me.")
    ctx_cmd.add_argument("file", help="The C file to create context for.")

    args, unk_args = parser.parse_known_args()
    cmd = args.command

    try:
        runner = DinoCommandRunner(args.verbose)
        if cmd == "setup":
            runner.setup()
        elif cmd == "extract":
            runner.extract()
        elif cmd == "build":
            runner.build(configure=args.configure, force=args.force)
        elif cmd == "configure":
            runner.configure(skip_dlls=args.skip_dlls)
        elif cmd == "verify":
            runner.verify()
        elif cmd == "baseverify":
            runner.baseverify()
        elif cmd == "clean":
            runner.clean()
        elif cmd == "submodules":
            runner.update_submodules()
        elif cmd == "diff":
            full_args = args.args
            full_args.extend(unk_args)
            runner.diff(show_help=args.help, args=full_args)
        elif cmd =="context":
            runner.make_context(args.file)
    except subprocess.CalledProcessError:
        pass

if __name__ == "__main__":
    main()
