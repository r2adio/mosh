parser_test = executable(
  'parser_test',
  'parser_test.c',
  include_directories: inc_dir,
  link_with: mosh_lib,
)
test('parser test', parser_test)

builtin_test = executable(
  'builtin_test',
  'builtin_test.c',
  include_directories: inc_dir,
  link_with: mosh_lib,
)
test('builtin test', builtin_test)
