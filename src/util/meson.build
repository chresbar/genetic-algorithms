subdir('logger')

util_lib = static_library(
  'util',
  include_directories: inc,
  dependencies: [logger_dep]
)

util_dep = declare_dependency(
    link_with: util_lib,
    include_directories : inc
)
