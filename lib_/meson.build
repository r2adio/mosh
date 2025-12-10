lib_ = static_library(
  'lib_',
  files(
    'strcmp_.c',
    'strlen_.c',
  ),
  include_directories: inc_dir,
)

mosh_deps = declare_dependency(
  link_with: lib_,
  include_directories: inc_dir,
)
