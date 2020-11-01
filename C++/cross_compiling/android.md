# Cross compiling Linux => Android
This document is dedicated to cross compiling C/C++ applications for android OS. Below are the steps how you do that.

#### 1. Base steps to install tools, compile program, and run that into device.

 1.1 The first thing we want to do is fetch the Android NDK. Not the SDK, the NDK.
```
foo@bar:~$ curl -O http://dl.google.com/android/repository/android-ndk-r12b-linux-x86_64.zip
foo@bar:~$ unzip android-ndk-r12b-linux-x86_64.zip
```

1.2. It would be helpful to install adb and fastboot, too. This might be different for your distro’s package manager. Better yet may be to just build from source.
```
foo@bar:~$ sudo apt-get install android-tools-adb android-tools-fastboot
```

1.3. Now for you Android device that you want to target, you’ll want to know the ISA. Let’s say I want to target my Nexus 6P, which has an ARMv8-A ISA (the first 64b ARM ISA).
```
foo@bar:~$ ./android-ndk-r12b/build/tools/make_standalone_toolchain.py --arch arm64 --install-dir ~/arm
```

1.4. This will create a nice standalone bundle in ~/arm. It will contain our cross compiler, linker, headers, libs, and sysroot (crt.o and friends). Most Android devices are ARMv7-A, so you’d use --arch arm. 
Now we can compile application:
```
foo@bar:~$ cat hello_world.c
#include <stdio.h>
int main () {
  puts("hello world");
}
foo@bar:~$ ~/arm/bin/clang -pie hello_world.c
```

1.5. Connect your phone, enable remote debugging, and accept the prompt for remote debugging.
```
foo@bar:~$ adb push a.out /data/local/tmp/.
foo@bar:~$ adb shell "./data/local/tmp/a.out"
hello world
```

#### 2. Shared library

2.1. Compile code to shared library included libgcc and stdc++
```
foo@bar:~$ ~/arm/bin/clang++ --shared -static-libgcc -static-libstdc++ lib_mylib.cpp -o lib_mylib.so
foo@bar:~$ adb push lib_mylib.so /data/local/tmp/
```

2.2. Compile application with shared library path `../mylib/lib_mylib.so`. Next we set rpath (run path) into binnary application. Our application has all needed items in one folder `/data/local/tmp`.
```
foo@bar:~$ ~/arm/bin/clang++ -pie main.cpp -I../mylib -L../mylib -l_mylib
foo@bar:~$ patchelf --set-rpath '/data/local/tmp' a.out
```

2.3. Connect your phone, enable remote debugging, and accept the prompt for remote debugging
```
foo@bar:~$ adb push a.out /data/local/tmp/
foo@bar:~$ adb shell "/data/local/tmp/a.out"
SomeName
```

#### Others
Some standard compilation flags does not work in android. 
RPATH: `-Wl,-rpath=<path>` | `patchelf --set-rpath '/data/local/tmp' a.out`

#### Source pages:
http://nickdesaulniers.github.io/blog/2016/07/01/android-cli/

