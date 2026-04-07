# merge_to_simulide.py
from SCons.Script import Import
Import("env")

import os, sys, glob, subprocess

PROJ_DIR  = env["PROJECT_DIR"]
BUILD_DIR = env.subst("$BUILD_DIR")
APP_BIN   = os.path.join(BUILD_DIR, env.subst("${PROGNAME}.bin"))
ENV_NAME  = env.subst("$PIOENV")

if APP_BIN.lower().endswith(".elf"):
    APP_BIN = APP_BIN[:-4] + ".bin"

simulide_outdir = os.path.normpath(os.path.join(PROJ_DIR, "simulIDE"))
os.makedirs(simulide_outdir, exist_ok=True)
out_name = f"firmware_{ENV_NAME}_4MB.bin"
out_path = os.path.join(simulide_outdir, out_name)

bootloader = os.path.join(BUILD_DIR, "bootloader.bin")
partitions = os.path.join(BUILD_DIR, "partitions.bin")
boot_app0  = os.path.join(BUILD_DIR, "boot_app0.bin")

if not os.path.exists(boot_app0):
    cand = glob.glob(os.path.join(env["PROJECT_PACKAGES_DIR"],
                                  "framework-arduinoespressif32",
                                  "tools", "partitions", "boot_app0.bin"))
    boot_app0 = cand[0] if cand else None


def do_merge(target, source, env):
    esptool_py = os.path.join(env["PROJECT_PACKAGES_DIR"], "tool-esptoolpy", "esptool.py")
    py_exe = sys.executable

    cmd = [
        py_exe, esptool_py, "--chip", "esp32", "merge_bin",
        "-o", out_path,
        "--flash_mode", "dio",
        "--flash_size", "4MB",
        "0x1000", bootloader,
        "0x8000", partitions,
    ]
    if boot_app0 and os.path.exists(boot_app0):
        cmd += ["0xe000", boot_app0]
    cmd += ["0x10000", APP_BIN]

    print("[merge_to_simulide] Executando:", " ".join(cmd))
    subprocess.run(cmd, check=True)

    # 🔧 Corrige o tamanho final (QEMU exige 4.194.304 bytes)
    TARGET_SIZE = 4 * 1024 * 1024  # 4MB
    size = os.path.getsize(out_path)
    if size < TARGET_SIZE:
        with open(out_path, "ab") as f:
            f.write(b"\xFF" * (TARGET_SIZE - size))
        print(f"[merge_to_simulide] Corrigido tamanho do arquivo: {size} → {TARGET_SIZE} bytes (preenchido com 0xFF)")
    elif size > TARGET_SIZE:
        raise RuntimeError(f"[merge_to_simulide] Arquivo excede 4MB ({size} bytes)!")

    print(f"[merge_to_simulide] OK! Arquivo mesclado salvo em {out_path}")


env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", do_merge)