assert_test = executable(
  'simple_test',
  'assert_test.c',
  include_directories: inc_dir,
)
test('assert test', assert_test)

parser_test = executable(
  'parser_test',
  'parser_test.c',
  include_directories: inc_dir,
  link_with: mosh_lib,
)
test('parser test', parser_test)
