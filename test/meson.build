fs = import('fs')
test_src = files(
  'builtin_test.c',
  'parser_test.c',
  'printf_test.c',
  'strcmp_test.c',
  'strlen_test.c',
)

foreach t : test_src
  name = fs.stem(t)
  exe = executable(
    name,
    t,
    include_directories: inc_dir,
    link_with: mosh_lib,
    dependencies: mosh_deps,
  )
  test(name, exe)
endforeach
