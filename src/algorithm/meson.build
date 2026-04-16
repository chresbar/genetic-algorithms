subdir('individual')
subdir('selector')

genetic_algorithm_sources = files(
    'geneticAlgorithm.h',
    'geneticAlgorithm.cpp'
)

genetic_algorithm_lib = static_library(
  'genetic_algorithm',
  sources: genetic_algorithm_sources,
  include_directories: inc,
  dependencies: [graph_dep, individual_dep, selector_dep]
)

genetic_algorithm_dep = declare_dependency(
  link_with: genetic_algorithm_lib,
  include_directories : inc
)
