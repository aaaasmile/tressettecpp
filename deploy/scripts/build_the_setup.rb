#file: build_the_setup

require 'rubygems'
require 'yaml'
require 'setup_creator'


if $0 == __FILE__
  # Create the setup.exe in one step:
  # - copy the app code into the deploy dir (Invido version is used implicitely)
  # - copy othe stuff like License, help and create the nsis file
  # - copile the nsis file
  # Requisites: nsis (version used 2.48). 
  # Write these full paths into the target_deploy_info.yaml
  puts "== Create the setup for InvidoCpp ==="
  dep = SetupCreator.new
  options_filename = 'target_deploy_info.yaml'
  opt = YAML::load_file( options_filename )
  if opt == nil or opt.class != Hash
    puts "Target file not recognized"
    exit
  end
  dep.read_sw_version()
  ver_suffix = dep.get_version_suffix
  root_version_dir = File.join(opt[:root_deploy], "invido_" + ver_suffix)

  puts "-------- Delete current deploy dir"
  if File.directory?(root_version_dir)
    FileUtils.rm_rf(root_version_dir)
    puts "Old deploy dir removed"
  end
  puts "-------- Create deploy directory #{root_version_dir}"
  FileUtils.mkdir_p(root_version_dir)

  puts "------- Copy app stuff "
  app_dir = 'Installer'
  dst_app_dir = File.join(root_version_dir, "#{app_dir}")
  src_app = opt[:source_bin]
  puts "Source is #{src_app}"
  puts "Destination is #{dst_app_dir}"
  dep.prepare_src_in_deploy(src_app, dst_app_dir)
  
  puts "--------- Prepare installer files and compile it"
  installer_dir = dst_app_dir
  nsi_out_name = dep.create_nsi_installer_script(installer_dir, dst_app_dir)
  nsi_cmd = "#{opt[:nsi_exe]}  #{nsi_out_name}"
  dep.exec_mycmd(nsi_cmd)
  puts "Setup #{nsi_out_name} successfully created"
end