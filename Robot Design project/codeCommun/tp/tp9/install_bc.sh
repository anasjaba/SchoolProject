progmem -v -o sequence.bin sequence.bc
make -C src/writeUsb
make install -C src/writeUsb
sleep 1
serieViaUSB -e -f sequence.bin
make
make install