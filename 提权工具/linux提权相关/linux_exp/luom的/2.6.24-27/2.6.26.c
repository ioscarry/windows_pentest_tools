root@localhost asus_acpi]# make clean
rm -f *.o *.ko .*.cmd .*.flags *.mod.c Module.symvers
rm -rf .tmp_versions
[root@localhost asus_acpi]# make
Building ASUS ACPI driver...
make[1]: Entering directory `/usr/src/linux-2.6.24.2-laptop-4mdv'
  CC [M]  /home/stephane/Desktop/acpi/asus_acpi/asus_acpi.o
/home/stephane/Desktop/acpi/asus_acpi/asus_acpi.c:164: warning: initialization from incompatible pointer type
/home/stephane/Desktop/acpi/asus_acpi/asus_acpi.c:550: warning: initialization from incompatible pointer type
/home/stephane/Desktop/acpi/asus_acpi/asus_acpi.c: In function ‘asus_hotk_notify’:
/home/stephane/Desktop/acpi/asus_acpi/asus_acpi.c:1181: error: implicit declaration of function ‘acpi_bus_generate_event’
make[2]: *** [/home/stephane/Desktop/acpi/asus_acpi/asus_acpi.o] Error 1
make[1]: *** [_module_/home/stephane/Desktop/acpi/asus_acpi] Error 2
make[1]: Leaving directory `/usr/src/linux-2.6.24.2-laptop-4mdv'
make: *** [asus_acpi] Error 2
[root@localhost asus_acpi]#