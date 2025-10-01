project('mosh', 'c', default_options: ['c_std=c2x'])

# enter src/ and process meson.build file there
subdir('src') # to access all variables and targets declared in src/meson.build

# inc_dir points to include/ directory
inc_dir = include_directories('include')

# executable name: mosh, var difined in src/meson.build, check include/ for header files
executable('mosh', src_dir, include_directories: inc_dir)
