project('mosh', 'c', default_options: ['c_std=c2x'])

inc_dir = include_directories('include')

# enter src/ and process meson.build file there
subdir('src')

# executable name: mosh, var difined in src/meson.build, check include/ for header files
executable('mosh', src_dir, include_directories: inc_dir, link_with: mosh_lib)

subdir('test')
