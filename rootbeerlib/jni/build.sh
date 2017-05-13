#!/bin/bash
# build.sh uses the android ndk to compile and then copies the shared object into the correct place
# written by Matthew Rollings 2015
ndk-build

pushd ../libs &> /dev/null
for arch in `ls -d -- *`; do
    dest="../src/main/jniLibs/${arch}"
    mkdir -p "${dest}"
    cp "${arch}/libandroid-logger.so" "${dest}/libandroid-logger.so"
    echo "Copied ${arch} lib to ${dest}"
done
popd &> /dev/null

