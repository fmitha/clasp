    "clang++" -x c++ -O0 -g -H -Warray-bounds -Wno-deprecated-register -mmacosx-version-min=10.7 -fvisibility=default -std=c++11 -stdlib=libc++ -DDEBUG_ASSERTS -DDONT_USE_MPS -DEXPAT -DINCLUDED_FROM_CLASP -DINHERITED_FROM_SRC -DREADLINE -DUSE_GCVECTOR_MALLOC_ALLOCATOR -D_ADDRESS_MODEL_64 -D_DEBUG_BUILD -D_TARGET_OS_DARWIN -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -I"../../src" -I"../../src/core" -I"../../src/core/bin/clang-darwin-4.2.1/debug/link-static/mps-off" -I"/Library/Frameworks/EPD64.framework/Versions/7.2/include/python2.7" -I"/Users/meister/Development/cando/clasp/build/cando.app/Contents/Resources/externals/common/include" -I"/Users/meister/Development/cando/clasp/build/cando.app/Contents/Resources/externals/release/include" -c -o "../../src/core/bin/clang-darwin-4.2.1/debug/link-static/mps-off/lightProfiler.o" "../../src/core/lightProfiler.cc"
