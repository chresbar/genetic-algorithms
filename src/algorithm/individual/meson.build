individual_sources = files(
    'individual.h',
    'individual.cpp'
)

individual_lib = static_library(
  'individual',
  sources: individual_sources,
  include_directories: inc
)

individual_dep = declare_dependency(
  link_with: individual_lib,
  include_directories : inc
)
