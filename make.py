import os
import shutil

os.system("rm -r output")

if not os.path.exists("output"):
	os.makedirs("output")

os.system("nasm -f elf multiboot_header.asm -o output/multiboot_header.o")
os.system("nasm -f elf boot.asm -o output/boot.o")
#os.system("gcc -m32 -c kernel_main.c -o output/kernel_main.o")
os.system("gcc -c kernel_main.c -o output/kernel_main.o")
os.system("ld -n -o output/kernel.bin -T linker.ld output/multiboot_header.o output/boot.o output/kernel_main.o")

isobootpath = "output/iso/boot"
isogrubpath = isobootpath+"/grub"
currentdir =""+ os.getcwd()
if not os.path.exists(isogrubpath):
	os.makedirs(isogrubpath)

shutil.copyfile(currentdir + "/grub.cfg", currentdir+"/"+isogrubpath+"/grub.cfg")
shutil.copyfile(currentdir + "/output/kernel.bin", currentdir+"/"+isobootpath+"/kernel.bin")

os.system("grub-mkrescue -o output/os.iso output/iso")
