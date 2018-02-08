# Use meson et ninja.
# meson est installé par pip le python package manager.
project('demo4', 'c')
nasm_compiler = find_program('nasm')
nasm_gen = generator(nasm_compiler,
    output : '@BASENAME@.o',
    arguments : ['-f', 'elf64', '@INPUT@', '-o', '@OUTPUT@'])
c_compiler = meson.get_compiler('c')

pthread_lib = c_compiler.find_library('pthread', needed: false)

obj_files = nasm_gen.process(['swap.s'])

executable('compare_and_swap',
    'compare_and_swap.c', dependencies : [pthread_lib])

executable('mutex_swap',
  'mutex_swap.c', obj_files,
  dependencies : [pthread_lib])

