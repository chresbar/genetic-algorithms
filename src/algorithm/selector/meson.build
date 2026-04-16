selector_sources = files(
    'selector.h'
)

selector_lib = static_library(
  'selector',
  sources: selector_sources,
  include_directories : inc,
  dependencies: [util_dep]
)

selector_dep = declare_dependency(
  link_with: selector_lib,
  include_directories : inc
)
