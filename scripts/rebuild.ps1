cd projectfina
npm run build

cd ..

rm -r build
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr/local/fina-web
cmake --build . --target install
