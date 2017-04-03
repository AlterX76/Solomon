

/***********************************************************************************
 * Nome classe: ConcreteTcpEmbeddedServerGame                                      *
 * ---------------------------------------------------------------------------     *
 * Descrizione: Oggetto che implementa server lato client: responsabile            *
 *              dell'apertura di connessione per inviare e ricevere informazioni.  *
 *              Versione per tcp.                                                  *
 * Data:        01/02/2014                                                         *
 * Autore:      Giovanni Romano                                                    *
 ***********************************************************************************/


#ifndef _CONCRETE_TCP_EMBEDDED_SERVERGAME_H
    #define _CONCRETE_TCP_EMBEDDED_SERVERGAME_H

    #include "Solomon.h"
    #include "AbstractTcpEmbeddedServerGame.h"
    //
    //
    // Implementa il client tcp che verrà utilizzato per la completa gestione server game
    class ConcreteTcpEmbeddedServerGame : public AbstractTcpEmbeddedServerGame {
        private:
            IClientBridgeProvider   *m_bridge;
            integer                 m_idTicket; // ticket univoco assegnato dal server tcp centrales
            boolean                 m_connected;

        public:
            ConcreteTcpEmbeddedServerGame(IClientBridgeProvider *bridge, buffer_pointer localIp, u_short localPort, buffer_pointer remoteIp, u_short remotePort);

            virtual                 ~ConcreteTcpEmbeddedServerGame();
            //
            // funzioni per usufruire della classe:
            integer                 getClientTicket();
            void                    Stop();
            void                    Start(boolean require_SSL_TLS);
            bool                    isConnected();
            bool                    isServerStarted();
            boolean                 AsyncSendRequest(AbstractHeaderMessage *header, AbstractBodyMessage *body);
            boolean                 AsyncSendFile(AbstractHeaderMessage *header, u_integer id, const buffer_pointer file);

        private:
            //
            // Costruttori:
            ConcreteTcpEmbeddedServerGame(const ConcreteTcpEmbeddedServerGame&);
            ConcreteTcpEmbeddedServerGame& operator=(const ConcreteTcpEmbeddedServerGame&);

            static void *           startProfileFileSend(void *);

        protected:
            //
            // funzioni virtuali da implementare:
            void                    BackgroundParser(void *request); // rappresenta la funzione che sarà richiamata automaticamente da più threads
            void                    ConnectionDown();
    };

#endif // _CONCRETE_TCP_EMBEDDED_SERVERGAME_H
 
