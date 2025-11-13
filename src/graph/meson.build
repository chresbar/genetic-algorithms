sources = files(
    'graph.h',
    'graph.cpp'
)

inc = include_directories('.')

json_dep = dependency('jsoncpp', required: true)

graph_lib = static_library(
  'graph',
  sources,
  dependencies : json_dep,
  include_directories : inc
)

graph_dep = declare_dependency(
  link_with : graph_lib,
  include_directories : inc
)