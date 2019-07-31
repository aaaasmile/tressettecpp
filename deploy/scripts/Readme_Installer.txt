== creare il setup dopo un aggiornamento
- crea la versione release x64 in visual studio 2015
- Il file target_deploy_info.yaml punta già a quella directory, quindi basta lanciare il build_the_setup.rb con powershell (vedi sotto).
  Non occorre cancellare i vari pdb e similari in quanto sono filtrati al momento della creazione del setup.

== Creare il setup la prima volta
- mettere in target_deploy_info.yaml la directory dove vengono messe tutte le versioni
- Occorre 7zip e nsis installer. Questi path vanno messi in target_deploy_info.yaml
- La versione, che si trova in cMenuMgr.cpp, decide i nomi delle directory e dei files zip
- Lanciare lo script build_the_setup.rb, esso crea il setup.exe in un colpo solo. 


== ruby
In Powershell:
$env:path = "D:\ruby\ruby_1_8_6\bin;"+$env:path
cd deploy\scripts
ruby .\build_the_setup.rb

Nota che ho usato 1.8.6 che quindi funziona anche con arachno. Con ruby 2.3.1 non sono riuscito a 
fare andare il comando: 
Exec C:\Program Files (x86)\NSIS\makensis.exe  D:\Projects\from_sf_net_to_github\tressettecpp\Resources_not_used\deployed/tressette_2_1_0/Installer/tressette_gen.nsi
qualcosa non deve essere corretto in IO.popen(cmd, "r") do |io| di setup_creator.rb