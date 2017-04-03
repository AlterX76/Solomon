
#ifndef UTILITY_H
    #define UTILITY_H

    #include "Solomon.h"
    //
    //
    // classe di utilita':
    class DLL_ACTION Utility {
        private:
            Utility();

        public:
            //
            // funzioni statiche:
            static u_integer    CreateLoginSession(void); // Crea un login_session di 8 numeri random; eseguire la funzione Randomize() una sola volta prima di utilizzare questa funzione
            static void         Randomize(void); // avvia il generatore casuale di numeri (AUTOMATICALLY CALLED BY GAMESERVERCLASS OBJECT)
    };

#endif // UTILITY_H
