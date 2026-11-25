logger_sources = files(
    'logger.cpp'
)

logger_lib = static_library(
  'logger',
  sources: logger_sources,
  include_directories: inc
)

logger_dep = declare_dependency(
    link_with: logger_lib,
    include_directories : inc
)