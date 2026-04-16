util_sources = files(
    'logger.h',
    'rng.h',
    'utils.h',
    'logger.cpp'
)

util_lib = static_library(
  'util',
  sources: util_sources,
  include_directories: inc
)

util_dep = declare_dependency(
    link_with: util_lib,
    include_directories : inc
)
