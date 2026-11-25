subdir('logger')

json_dep = dependency('jsoncpp', required: true)

util_lib = static_library(
  'util',
  include_directories: inc,
  dependencies: [logger_dep, json_dep]
)

util_dep = declare_dependency(
    link_with: util_lib,
    include_directories : inc
)
