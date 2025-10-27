build(){
        # clean build directory
    rm -rf build

    # reconfigure and build
    cmake -S . -B build
    cmake --build build -j

    # run tests
    ctest --test-dir build --timeout 5 -V

}
build