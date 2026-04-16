subdir('util') # graph uses util so it need to be first
subdir('graph')
subdir('algorithm')

executable(
  'genetic-algorithms',
  'main.cpp',
  dependencies : [genetic_algorithm_dep, graph_dep, util_dep],
  include_directories : inc,
  install : true,
)
