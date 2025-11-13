subdir('utc-graph')

catch2_dep = dependency('catch2', required: true)

utc_exe = executable(
  'utc',
  'utc_main.cpp',
  dependencies : [catch2_dep, utc_graph_dep]
)

test('utc', utc_exe)