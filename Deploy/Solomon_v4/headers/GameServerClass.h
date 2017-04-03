

/***********************************************************************************
 * Nome classe: GameServerClass                                                    *
 * ---------------------------------------------------------------------------     *
 * Descrizione: Oggetto che implementa server astratto: esegue caricamento dei     *
 *              commands per il server e gestisce le richieste ricevute.           *
 *              Utilizzare per la creazione del server applicazione.               *
 * Data:                01/03/2012                                                 *
 * Revisione:           12/01/2014                                                 *
 * Autore:              Giovanni Romano                                            *
 ***********************************************************************************/

#ifndef _GAME_SERVER_CLASS_H
    #define _GAME_SERVER_CLASS_H

#ifndef MOBILE_BUILD

    #include "Solomon.h"
    #include "AbstractServerGame.h"
    #include <limits.h>
    //
    // forward declarations:
    class IChainCommand;
    //
    //
    // Implementa il client che verrà utilizzato per la completa gestione server game
    class GameServerClass : public AbstractServerGame {
        private:            
            IChainCommand                   *m_shortcutToPositionUpdater; // conterra' eventuale shortcut
            byte                            m_idServiceShortcut, m_idMessageShortcut;

        public:
            //
            // Costrutture/distruttore:
            // maxPacketSize: max dimension of udp/tcp requests (not considered for file); if you overtake limit of udp, unexpected behaviour can occur for udp requests
            GameServerClass(IServerBridgeProvider *bridge, byte idServiceShortcut = 0, byte idMessageShortcut = 0, u_integer maxPacketSize = USHRT_MAX);
            ~GameServerClass();
            //
            // funzione che avvia il client per la ricezione delle notifiche:
            boolean                         StartServerListener(void);

        private:
            //
            // Costruttori:
            GameServerClass(const GameServerClass&);
            GameServerClass& operator=(const GameServerClass&);

        protected:
            //
            // funzioni virtuali da implementare:
            void                            BackgroundParser(const ClientContainer *tmpDataContainerReader); // rappresenta la funzione che sarà richiamata automaticamente da più threads
    };

#endif // MOBILE_BUILD

#endif // _GAME_SERVER_CLASS_H
 
