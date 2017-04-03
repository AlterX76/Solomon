

/***********************************************************************************
 * Nome classe: GameClientClass                                                    *
 * --------------------------------------------------------------------------------*
 * Descrizione: Oggetto che implementa server unificato udp/tcp.                   *
 *              Utilizzare per la creazione del server lato client.                *
 * Data:        04/02/2014                                                         *
 * Autore:      Giovanni Romano                                                    *
 ***********************************************************************************/


#ifndef _GAME_CLIENT_CLASS_H
    #define _GAME_CLIENT_CLASS_H

    #define FALSE   0
    #define TRUE    !(FALSE)

    #include "Solomon.h"
    #include "AbstractServiceClass.h"
    #include "IClientBridgeProvider.h"
    //
    // forward declarations:
    class ConcreteTcpEmbeddedServerGame;
    class ConcreteUdpEmbeddedServerGame;
    class IGameClientBridgeProvider;
    //
    // NDO NOT USE IN MULTI-THREAD CONTEXT
    // Implementa client unificato per gestire richieste udp/tcp per il server embedded:
    class GameClientClass : private IClientBridgeProvider, protected AbstractServiceClass {
        private:
            ConcreteTcpEmbeddedServerGame   *_tcpServerGame;
            ConcreteUdpEmbeddedServerGame   *_udpServerGame;
            IGameClientBridgeProvider       *_clientBridge;

        public:
            //
            // Costrutture/distruttore:
            GameClientClass(IGameClientBridgeProvider *bridge, buffer_pointer localIP, u_short localPort, buffer_pointer remoteIP, u_short remotePort, u_short datagramSize = 1024);
            ~GameClientClass();
            //
            // funzione che avvia il client per la ricezione delle notifiche:
            void                            StartEmbeddedServer(boolean require_SSL_TLS);
            void                            StopEmbeddedServer();
            //
            // funzioni per eseguire richieste in modo asincrono:
            boolean                         AsyncSendRequestOverTcp(AbstractHeaderMessage *header, AbstractBodyMessage *body);
            boolean                         AsyncSendRequestOverUdp(AbstractHeaderMessage *header, AbstractBodyMessage *body);
            boolean                         AsyncSendFileStream(AbstractHeaderMessage *header, u_integer id, const buffer_pointer file); // uploads a file: the connection is marked as permanent on the server till the end of transfer
                                                                                                                                        // after the transfer the connection might got cleaned by the GC on the next iteration.
            //
            // funzioni per eseguire richieste in modo sincrono:
            ResponseGenericMessage *        SyncSendRequestOverUdp(ClientEnvironment *clientEnv, AbstractHeaderMessage *header, AbstractBodyMessage *body);
            AbstractResponseMessage *       SyncSendRequestOverUdp(AbstractBodyMessage *body, AbstractHeaderMessage *checker, u_short timeout);
            AbstractResponseMessage *       SyncSendRequestOverTcp(ClientEnvironment *clientEnv, AbstractBodyMessage *body, AbstractHeaderMessage *header, u_short timeout);
            integer                         getClientTicket();
            bool                            isConnected();
            bool                            isServerStarted();

        private:
            //
            // Costruttori:
            GameClientClass(const GameClientClass&);
            GameClientClass& operator=(const GameClientClass&);

            // IClientBridgeProvider interface
            virtual AbstractHeaderMessage * createHeaderMessage();
            virtual void                    clientDidStartTcpConnection();
            virtual void                    clientDidStartUdpConnection();
            virtual void                    clientDidCloseTcpConnection();
            virtual void                    clientDidCloseUdpConnection();
            virtual boolean                 clientDidHandleServerTcpRequest(const AbstractHeaderMessage *header, DataContainerReader *binaryBody);
            virtual void                    clientDidHandleServerUdpRequest(const AbstractHeaderMessage *header, DataContainerReader *binaryBody);
            virtual void                    clientWillStartFileUpload(const AbstractHeaderMessage *header, u_integer id, const buffer_pointer fileName);
            virtual void                    clientDidFinishFileUpload(const AbstractHeaderMessage *header, u_integer id, const buffer_pointer fileName, TFileUploadResult sent);
            virtual void                    serverDidReceiveFile(u_integer identifier);
    };

#endif // _GAME_CLIENT_CLASS_H
 
