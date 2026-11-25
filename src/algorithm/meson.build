subdir('individual')
subdir('selector')
subdir('graph')

genetic_algorithm_sources = files(
    'geneticAlgorithm.cpp'
)

genetic_algorithm_lib = static_library(
  'genetic_algorithm',
  sources: genetic_algorithm_sources,
  include_directories: inc,
  dependencies: [json_dep, graph_dep, individual_dep, selector_dep]
)

genetic_algorithm_dep = declare_dependency(
  link_with: genetic_algorithm_lib,
  include_directories : inc
)
