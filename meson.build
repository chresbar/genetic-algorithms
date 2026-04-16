project(
  'genetic-algorithms',
  'cpp',
  version : '0.1.0',
  default_options : [
    'cpp_std=c++17',
    'warning_level=3',
    'optimization=2'
  ]
)

res_dir = join_paths(meson.source_root(), 'res')

configure_file(
    output : 'config.h',
    configuration : {'RES_DIR' : '"' + res_dir + '/"'}
)

add_global_arguments('-I' + meson.current_build_dir(), language : 'cpp')

inc = include_directories('src')

subdir('src')
if get_option('tests')
    subdir('tests')
endif
