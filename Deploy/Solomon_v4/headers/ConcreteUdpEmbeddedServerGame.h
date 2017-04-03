

/***********************************************************************************
 * Nome classe: ConcreteUdpEmbeddedServerGame                                      *
 * ---------------------------------------------------------------------------     *
 * Descrizione: Oggetto che implementa server lato client: responsabile            *
 *              dell'apertura di connessione per inviare e ricevere informazioni.  *
 *              Versione per udp.                                                  *
 * Data:        04/02/2014                                                         *
 * Autore:      Giovanni Romano                                                    *
 ***********************************************************************************/


#ifndef _CONCRETE_UDP_EMBEDDED_SERVERGAME_H
    #define _CONCRETE_UDP_EMBEDDED_SERVERGAME_H

    #include "Solomon.h"
    #include "AbstractEmbeddedServerGame.h"
    //
    //
    // Implementa il client udp che verrà utilizzato per la completa gestione server game
    class ConcreteUdpEmbeddedServerGame : protected AbstractEmbeddedServerGame {
        private:
            IClientBridgeProvider   *m_bridge;
            integer                 id_client;

        public:
            ConcreteUdpEmbeddedServerGame(IClientBridgeProvider *bridge, buffer_pointer localIp, u_short localPort, buffer_pointer remoteIp, u_short remotePort
                                          , u_short datagramSize, boolean activePing);

            virtual                 ~ConcreteUdpEmbeddedServerGame();
            //
            // funzioni per usufruire della classe:
            void                    Stop();
            void                    Start(u_short pingIntervalInSecs = 20);
            bool                    isServerStarted();
            boolean                 AsyncSendRequest(AbstractHeaderMessage *header, AbstractBodyMessage *body);
            integer                 GetClientTicket();
            void                    SetClientTicket(integer value);

        private:
            //
            // Costruttori:
            ConcreteUdpEmbeddedServerGame(const ConcreteUdpEmbeddedServerGame&);
            ConcreteUdpEmbeddedServerGame& operator=(const ConcreteUdpEmbeddedServerGame&);

        protected:
            //
            // funzioni virtuali da implementare:
            void                    BackgroundParser(void *request); // rappresenta la funzione che sarà richiamata automaticamente da più threads
    };

#endif // _CONCRETE_UDP_EMBEDDED_SERVERGAME_H
 
