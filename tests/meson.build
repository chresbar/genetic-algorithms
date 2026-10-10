subdir('utc-graph')
subdir('utc-genetic-algorithms')
subdir('utc-util')

catch2_dep = dependency('catch2', required: true)

utc_exe = executable(
  'utc',
  'utc_main.cpp',
  dependencies : [catch2_dep, utc_graph_dep, utc_genetic_algorithms_dep, utc_util_dep]
)

test('utc', utc_exe)