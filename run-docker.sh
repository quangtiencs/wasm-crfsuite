docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) emscripten/emsdk sh build.sh
