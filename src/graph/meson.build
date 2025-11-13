sources = files(
    'graph.h',
    'graph.cpp'
)

# Define includes
inc = include_directories('.')

graph_lib = static_library(
  'graph',
  sources,
  include_directories : inc
)

graph_dep = declare_dependency(
  link_with : graph_lib,
  include_directories : inc
)