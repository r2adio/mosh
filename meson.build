project(
  'mosh',
  'c',
  version: '0.10.0',
  license: 'MIT',
  default_options: ['c_std=c23', 'warning_level=3', 'werror=true', 'buildtype=debugoptimized'],
  meson_version: '>=1.2.0',
)

inc_dir = include_directories('include')

subdir('src')
subdir('test')

executable('mosh', src_files, include_directories: inc_dir, link_with: mosh_lib)
