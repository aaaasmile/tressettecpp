# script used to generate the class cSettings

require 'erb'

#check if the target was given
which_plat = "EXPAT"
ARGV.each do |plat_target|
  puts "Argument is: #{plat_target}"
  if plat_target == "libini" 
    which_plat = "LIBINI"
  elsif plat_target == "registry"
    which_plat = "REGISTRY"
  end
end


#data definitions

#used to generate c++ class  files

#template filename and associated extension. If you wan to produce more files, 
#add a new template - extension pair
#default template
templ_list = [
                ["settings_expat_h.rtemp", ".h"],
                ["settings_expat_cpp.rtemp", ".cpp"]
             ]


if which_plat == "REGISTRY"
  templ_list = [
                ["settings_reg_h.rtemp", ".h"],
                ["settings_reg_cpp.rtemp", ".cpp"]
             ]
             
elsif which_plat == "LIBINI"
  templ_list = [
                ["settings_libini_h.rtemp", ".h"],
                ["settings_libini_cpp.rtemp", ".cpp"]
             ]
end


#general info
@comment      = "Settings definition. Settings uses a persintence and a global access method."
@nameClass    = "cSettings"
@define       = "__CUSTOMSETTINGS_INI_H_"
@globalObj    = "g_Options"


#sections (Name, used name access in @globalObj )
# add a new section also here
@sect_coll = [ 
                ["SubAll", "All"],
                ["SubNetwork", "Net" ],
                ["SubMatch", "Match"]
             ]

#hash uses the same section name as the variable @sect_coll
# defines items: type, name, default, comment
@items_coll = {
                "SubAll" => [ #section - begin
  ["STRING",   "strPlayerName", "Remigio", "The name of the player"],
  ["int"     , "iDelayTimer", "300", "Delay animation timer"],
  ["int"     , "bAutoterminate", "1", "Automatic termination hand"],
  ["int"     , "iLevel", "1", "CPU level engine"],
  ["int"     , "iTipoMazzo", "0", "Kind of deck"],
  ["int"     , "iLanguageID", "0", "Language ID"],
  ["int"     , "bMusicOn", "1", "Music enabled"],
  ["int"     , "iMusicVolume", "80", "Music volume"],
  ["int"     , "iDebugLevel", "2", "Debug level"],
  ["int"     , "bUsePythonAsInit", "0", "Flag for using python as init script"],
  ["int"     , "bUsePythonNotification", "0", "Flag for using python notification"],
  ["int"     , "bUsePythonConsole", "0", "Flag for using python console"],
  ["STRING",   "strPythonInitScriptName", "", "python init script name"],
  ["int"     , "iVerbose", "3", "Verbose level"],
  ["int"     , "bMyCallEcho", "1", "Player calls echo"],
  ["int"     , "bSoundEffect", "1", "Enable sound effect"],
  ["int"     , "bFotoBack", "1", "Enable foto on background"],
  ["int"     , "bAnimatePlayCard", "1", "Enable animation on play card"],
  ["int"     , "iAniSpeedLevel", "0", "Animation speed level (0 slow, 5 fast)"],
  ["int"     , "bBlockOnManoEnd", "0", "Pause game after mano end"],
  ["int"     , "bSignalWithRMouse", "1", "Make signals with right mouse button"]
                            ], #section - end
                "SubNetwork" => [ #section - begin
  ["STRING",    "strServerName", "127.0.0.1", "Server name"],
  ["STRING",    "strPeerName", "127.0.0.1", "Peer name"],
  ["int"     ,  "iPortServer", "8790", "Port server value"],
  ["int"     ,  "iPortClient", "8791", "Port client value"],
  ["STRING",    "strLogin", "", "Login name"],
  ["STRING",    "strPassw", "", "login password"]
                            ], #section - end
                "SubMatch" => [ #section - begin
  ["int"     , "iLocalGameType", "1", "Localization of the game"],
  ["int"     , "bUseGoodGameDecla", "1", "Flag for using good game declaration"],
  ["int"     , "iScoreGoal", "33", "Points target to terminate a  match"],
  ["STRING", "strPlayerName_2","Bombolo","Player name index 2"],
  ["STRING", "strPlayerName_3","Socio","Player name index 3"],
  ["STRING", "strPlayerName_4","Cucciolo","Player name index 4"],
  ["int"     , "iLevel_Pl_1", "4", "Level of player 1"],
  ["int"     , "iLevel_Pl_2", "0", "Level of player 2"],
  ["int"     , "iLevel_Pl_3", "0", "Level of player 3"],
  ["int"     , "iLevel_Pl_4", "0", "Level of player 4"],
  ["STRING", "strAlgPlugin_Pl_1", "", "Algorithm plugin name player 1"],
  ["STRING", "strAlgPlugin_Pl_2", "", "Algorithm plugin name player 2"],
  ["STRING", "strAlgPlugin_Pl_3", "", "Algorithm plugin name player 3"],
  ["STRING", "strAlgPlugin_Pl_4", "", "Algorithm plugin name player 4"],
  ["STRING", "strPluginDll_Pl_1", "", "Dll plugin name player 1"],
  ["STRING", "strPluginDll_Pl_2", "", "Dll plugin name player 2"],
  ["STRING", "strPluginDll_Pl_3", "", "Dll plugin name player 3"],
  ["STRING", "strPluginDll_Pl_4", "", "Dll plugin name player 4"],
  
                            ] #section - end
              }


# generator part ( NO CHANGES NEEDED HERE)
#template = ERB.new("ciao <%= @nome %>")

templ_list.each do |n_templ|
  #process the template
  fullname = File.dirname(__FILE__) + "/"+ n_templ[0]
  file = File.new(fullname, "r")
  template = ERB.new(file.read)
  file.close
  aString = template.result(binding)
  #save the result in a file
  file_out = File.dirname(__FILE__) + "/../" + @nameClass + n_templ[1]
  File.open(file_out , "w"){ |f| f  <<  aString}
  puts "File created: #{file_out}"
end