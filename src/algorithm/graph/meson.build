graph_sources = files(
    'graph.cpp'
)

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
