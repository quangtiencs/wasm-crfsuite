emcc -O3 --bind -Icrfsuite/lib/cqdb/include -Icrfsuite/include -Iliblbfgs/include crfsuite/lib/crf/src/*.c crfsuite/swig/*.cpp crfsuite/lib/cqdb/src/cqdb.c crfsuite/lib/cqdb/src/lookup3.c liblbfgs/lib/*.c  main.cpp --use-preload-plugins -o wasm-crfsuite.js
