graph_sources = files(
    'graph.h',
    'graph.cpp'
)

json_dep = dependency('jsoncpp', required: true)

graph_lib = static_library(
  'graph',
  sources: graph_sources,
  include_directories: include_directories('.'),
  dependencies: [json_dep, util_dep]
)

graph_dep = declare_dependency(
  link_with: graph_lib,
  include_directories : include_directories('.')
)
