CALL emcc "main.cpp" "bin-packer-master/src/box.cpp" "bin-packer-master/src/boxinfo.cpp" "bin-packer-master/src/container.cpp" "bin-packer-master/src/layer.cpp" "bin-packer-master/src/node.cpp" "bin-packer-master/src/pack.cpp" "bin-packer-master/src/packer.cpp" "bin-packer-master/src/vec3usi.cpp" -s EXPORT_ES6=1 -s MODULARIZE=1 -s USE_ES6_IMPORT_META=0 -s ENVIRONMENT='web' -o "dist/packer.js" -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s "EXPORTED_RUNTIME_METHODS=[\"ccall\", \"cwrap\"]" -I "./bin-packer-master/include/" -Os
COPY ".\dist\packer.js" "../src/packer.js"
COPY ".\dist\packer.wasm" "../public/packer.wasm"