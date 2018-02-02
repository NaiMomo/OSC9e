# Meson a build system in python.
# Build instruction:
# > meson . build
# > ninja -C build

project('bad_memory', 'c', default_options: ['strip=true'])

add_global_arguments('-Wall', '-Wno-format-truncation', '-Werror', language : 'c')

executable('buffer-overflow', 'buffer-overflow.c')
executable('invalid-pointer', 'invalid-pointer.c')

