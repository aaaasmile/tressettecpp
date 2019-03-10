== Genaratore della classe cSettings (h/cpp)

Ci sono due modi per generare i files ../cSettings.h e ../cSettings.cpp, 
ruby e la trasformazione del file xml via xsl.
Il metodo xml è obsoleto e non viene più supportato, vale a dire viene generato
un file cSettings.cpp che non corrisponde più alla versione attuale del tressette.

== Generatore attuale (12.11.2011)
Per generare cSettings.h ho usato ruby con i templates: settings_expat_cpp.rtemp
settings_expat_h.rtemp. I settings vengono salvati in un file xml che poi viene
riconosciuto usando expath

== ruby
Usando ruby si migliora di molto la compattezza del generatore.
Poi non è più necessario avere un trasformatore xml, xsl, basta
avere ruby.  
I settings sono in array definiti in gensettings.rb.  
Una nuova sezione va aggiunta in @sect_coll.
Gli elementi della sezione vanno inseriti nell'hash
@items_coll.
Lo script usa il modulo ruby ERB che va a sostituire nel template
settings_reg_h.rtemp e settings_reg_cpp.rtemp
i valori delle variabili definite in gensettings.rb.
Con il template settings_expat_h.rtemp si ottine la classe cSettings
che esporta i settings in un file xml. Il parsing avviene con la 
libreria expat, disponibile sia su windows che su linux.

== xml (non  più attuale)
Il primo prevede la trasformazione del file  xml in codice sorgente
per mezzo di una trasformazione xslt.
Nel caso di windows, sono settings.xml con registry_settings_h.xsl e
con registry_settings_cpp.xsl.  
I vari files xsl permettono di implementare la stessa classe usando però 
librerie diverse per salvare o leggere i dati.
Le librerie supportate sono, windows registry, libini e windows api.
Il programma che esegue la trasformazione xml => .h non è fornito.
Il motivo? Uso un programma messo su alla buona che è più di 15 Mb, buggy e
difficile da usare.
In rete ci sono programmi, specialmente java, che eseguono la conversione in modo più elegante
e compatta. Quali? Non lo so di preciso (vedi google), ma è meglio usare ruby 
descritto nella sezione successiva.
I settings, molto probabilmente, verranno generati solo con ruby e il file settings.xml
diventerà obsoleto.

== Linux
Se si genera la classe cSettings che utilizza expat, si può usare la stessa classe sia in linux che in windows.
Nel sistema operativo linux non vi è il registro, come alternativa si può usare anche la libreria
libini. I sorgenti si trovano su:
http://sourceforge.net/projects/libini
Per la compilazione ho usato la versione 1.1.10
Con ubuntu hoary essa non si lascia compilare, bisogna prima installare la libreria
tcl versione 8.0.


