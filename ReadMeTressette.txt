== TressetteCpp
14.04.2019. Progetto attuale per la conversione del tressette in SDL 2.0 con visual studio 2015.

In questa repository ho cercato di attualizzare il progetto tressette. 
Lo scopo è quello di avere la stessa applicazione compilata con visual studio 2015 (nota 2015 e no duemila diciasette) e sdl 2.0.
La tagione per usare vs2015 è che sdl2.0 è stato compilato con vs2015.
Sono partito con i srgenti dell'invido per poi aggiornarli con quelli del tressette.
Piattaforma supportata è x64 e solo questa.
Nella directory release ho solo gli obj, l'exe viene messo in out, dove ci sono i dati e anche le dll.
Per debug il discorso è diverso, ho messo tutto in debug. La ragione è che non voglio un mix debug/release nella stessa dir.


== SDL
Versioni:
SDL2-devel-2.0.8-VC
SDL2_mixer-devel-2.0.2-VC
SDL2_image-devel-2.0.3-VC
SDL2_ttf-devel-2.0.14-VC

Ho sempre usato tutte dll in versione x64.

Nota:
Ho messo tutti i files in include e lib senza distinguere le versioni.

Esempi di sdl 2 si trovano su https://www.libsdl.org/projects/

Un esempio di porting sdl 1.2 a 2.0 si trova su: https://github.com/yquake2/yquake2/blob/master/src/backends/sdl/refresh.c
La guida per la migrazione è su:
https://wiki.libsdl.org/MigrationGuide

Come riferimento guarda il progetto: D:\Projects\from_sf_net_to_github\Sdl_example\TextImput

Il problema del linker che non trova l'entry point:
Right click on project name -> Properties -> Expand Linker tab -> System -> SubSystem: make sure that it is Console (/SUBSYSTEM:CONSOLE)

Nel porting tutte le chiamate a 
SDL_SetAlpha (m_pSymbols, SDL_SRCALPHA, 120);
vanno sostituite con SDL_SetSurfaceAlphaMod

== Codice cambiato durante il porting
Ho tolto la console in quanto il porting su 2.0 era troppo oneroso e non era bella da vedere.
Ho tolto tutti i riferimenti al gioco di rete così come allo scripting di python.

= Short Key 
Autoformat Code: CTRL + K + D
Delete line: CTRL + L
Compile: CTRL + F7

== Runtime error in pnglib
Der Prozedureinsprungpunkt "inflateValidate" wurde in der DLL "D:\Projects\from_sf_net_to_github\invidocpp\src\VisualStudio\x64\Debug\libpng16-16.dll" nicht gefunden. 
L'errore sopra riportato è dovuto al fatto che zlib1.dll non è della versione corretta. Va usata quella della SDL_Image a x64

== Stringhe in UTF8
Per il render delle stringhe in formato UTF8 si usa la funzione TTF_RenderUTF8_Blended, per le ISO West si usa la TTF_RenderText_Blended.
Nota che le stringhe che provengono dalla classe Languages.cpp sono tutte in formato ascii. Quelle invece che provengono dall'input dell'utente, invece,
sono in formato UTF8. Quindi la funzione DrawString con il parametro UTF8 le usa solo i controlli che devono mostrare un testo proveniente dall'utente.

== TODO
- EngineApp.cpp è il file da mettere compile clean. Guarda il file AppGfx.cpp del progetto invidocpp per avere un riferimento delle parti cambiate per
sdl 2.0


== Autore
Igor Sarzi Sartori
Home page: invido.it
Email: 6colpiunbucosolo@gmx.net 
