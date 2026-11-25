subdir('util') # graph uses util so it need to be first
subdir('algorithm')

executable(
  'genetic-algorithms',
  'main.cpp',
  dependencies : [genetic_algorithm_dep, util_dep],
  include_directories : inc,
  install : true,
)
