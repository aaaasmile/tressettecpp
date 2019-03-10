#file: setup_creator.rb


$:.unshift File.dirname(__FILE__) + '/../..'

require 'rubygems'
require 'yaml'
require 'erubis'
require 'fileutils'
require 'filescandir'

class SetupCreator
  
  def initialize
    @ver_sw = [0,0,0]
  end
  
  def read_sw_version()
    script_fname = File.expand_path('../../src/InvidoClient/cMenuMgr.cpp')
    File.open(script_fname, "r").each_line do |line|
      #p line
      # search line with VER_PRG_STR it is something like:
      # VER_PRG_STR = \"Ver 0.5.4 14042008\"
      if line =~ /lpszVersion(.*)/
        arr_tmp =  $1.split("\"")
        arr_tmp.each do |tmp_str|
          if tmp_str =~ /Ver(.*)/
            # we expect here something like " 0.5.4 14042008"
            p ver_str_arr = $1.strip.split(" ")
            @ver_sw =  ver_str_arr[0].split(".")
            log "recognized version: #{@ver_sw[0]}-#{@ver_sw[1]}-#{@ver_sw[2]}"
            log "File parsed is #{script_fname}"
            return 
          end
        end
        log("Error on parsing lpszVersion")
        return 
      end
    end
    log("Error lpszVersion not found")
  end
  
  def prepare_src_in_deploy(src_app, target_dir)
    FileUtils.rm_rf(target_dir)
    FileUtils.mkdir_p(target_dir) unless File.directory?(target_dir)
    copy_app_subdir(src_app, target_dir)
  end
  
  def create_nsi_installer_script(target_dir, app_data_fullpath)
    FileUtils.mkdir_p(target_dir) unless File.directory?(target_dir)
    
    #@start_script = startscript
    # copy some extra file
    license_name = "License.txt"
    manual_filename = "Invido-help.pdf"
    #readme_filename = "Readme.txt"
    #ruby_dirname = 'Ruby'
    #app_dirname = 'App'
    
     # copy license file
    log "Copy license"
    file_src = File.join(File.dirname(__FILE__), "../help/#{license_name}")
    dest_full = File.join(target_dir, license_name)
    FileUtils.cp(file_src, dest_full)
    # copy manual file
    #log "Copy manual"
    #file_src = File.join(File.dirname(__FILE__), "../help/#{manual_filename}")
    #dest_full = File.join(target_dir, manual_filename)
    #FileUtils.cp(file_src, dest_full)
   
    #copy app
    #copy_package(File.join(target_dir, app_dirname), app_data_fullpath)
    #copy_package(target_dir, app_data_fullpath)
     
    # list of all files
    list_app_files = list_of_app_deployed_files(target_dir, target_dir + '/')
    # merge with app file list
    file_to_be_installed = list_app_files
     
    # generate nsi using template
    template_name = 'nsi_install/setup_muster.nsi_tm'
    nsi_out_name = File.join(target_dir, 'invido_gen.nsi')
    
    aString = ""
    # use template and eruby
    File.open(template_name, "r") do |file|
      input = file.read
      eruby_object= Erubis::Eruby.new(input)
      aString = eruby_object.result(binding)
      File.open(nsi_out_name, "w"){|f| f << aString } 
    end
    return nsi_out_name
  end
  
  def exec_mycmd(cmd)
    puts "Exec #{cmd}"
    IO.popen(cmd, "r") do |io|
      io.each_line do |line|
        puts line
      end
    end
  end
  
  def get_version_suffix
    return "#{get_int_pad1(@ver_sw[0])}_#{get_int_pad1(@ver_sw[1])}_#{get_int_pad1(@ver_sw[2])}"
  end
  
private

  def log(str)
    puts str
  end
  
  def copy_package(out_dir, full_src)
    FileUtils.mkdir_p(out_dir) unless File.directory?(out_dir)
    #tmp = File.split(full_src)
    #dest_full = File.join(out_dir, tmp[1])
    p "copy #{full_src} to #{out_dir}"
    #FileUtils.cp(full_src, dest_full)
    FileUtils.cp(full_src, out_dir)
    log "Copy #{dest_full}"
    return tmp[1]
  end
  
  # name_to_cut: path to be cut in the result beacuse we need a releative filename list
  def list_of_app_deployed_files(root_dir, name_to_cut)
    fscd = FileScanDir.new
    fscd.is_silent = true
    fscd.scan_dir(root_dir)
    res_names = []
    #each file need to be specified like without keyword File:
    #   File "app\\src\\cuperativa_gui.rb"
    old_rel_dir_path = nil
    fscd.result_list.each do |file_src|
      name =  file_src.gsub(name_to_cut, "")
      rel_dir_path = File.dirname(name) # note: not work with \ intead of / on the path
      
      name.gsub!('/', "\\")
      puts str_path_file = "#{name}"
      if rel_dir_path != old_rel_dir_path
        puts "Path changed to: #{rel_dir_path}"
        adptrel_dir_path = "\\#{rel_dir_path.gsub('/', "\\")}" # need: \app\src\network
        res_names << { :filename => str_path_file, :out_path => adptrel_dir_path, 
                       :delete_path => old_rel_dir_path  }
        old_rel_dir_path = rel_dir_path
      else
        res_names << { :filename => str_path_file }
      end
    end
    p res_names.last[:delete_path] = old_rel_dir_path
    return res_names
  end
  
  def get_int_pad2(val)
    return "0#{val}" if val.to_i < 10
    return "#{val}"
  end
  
  def get_int_pad1(val)
    return "#{val}"
  end
  
  def copy_app_subdir(src_app_dir, target_dir)
    fscd = FileScanDir.new
    fscd.add_extension_filter([".yaml", ".yml", ".log"])
    fscd.is_silent = true
    start_dir = src_app_dir
    fscd.scan_dir(start_dir)
    copy_appl_to_dest(fscd.result_list, start_dir, target_dir)
  end

  def copy_appl_to_dest(file_list, start_dir, dst_dir)
    file_list.each do |src_file|
      # name without start_dir
      rel_file_name = src_file.gsub(start_dir, "")
      log "Copy #{rel_file_name}"
      # calculate destination name
      dest_name_full = File.join(dst_dir, rel_file_name)
      dir_dest = File.dirname(dest_name_full)
      # make sure that a directory destination exist because cp don't create a new dir
      FileUtils.mkdir_p(dir_dest) unless File.directory?(dir_dest)
      FileUtils.cp(src_file, dest_name_full)
    end
  end
  
end

if $0 == __FILE__
  dep = SetupCreator.new
  dep.read_sw_version()
end
