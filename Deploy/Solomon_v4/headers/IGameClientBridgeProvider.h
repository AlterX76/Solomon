
#ifndef _IGAME_CLIENTBRIDGEPROVIDER_H
    #define _IGAME_CLIENTBRIDGEPROVIDER_H

    #include "IClientBridgeProvider.h"
    //
    // definizione per il server embedded:
    class AbstractTcpEmbeddedServerGame;
    // ---------------------------------------------------------------------------------------
    // IGameClientBridgeProvider
    // oggetto utilizzato nella pipeline del client unificato per interagire con esso.
    class DLL_ACTION IGameClientBridgeProvider {
        public:
            //
            // implementare in base al proprio protocollo:
            virtual                         ~IGameClientBridgeProvider();
            virtual AbstractHeaderMessage * clientCreateHeaderMessage() = 0;
            //
            // notifica di avvenuta connessione con il server:
            virtual void                    clientConnectedToServer();
            //
            // notifica chiusura connessione con il server:
            virtual void                    clientDisconnectedFromServer();
            //
            // richiamata quando si riceve dal server una richiesta da gestire.
            // ritornare TRUE se la richiesta e' stata gestita dal client perche' notifica; FALSE altrimenti.
            virtual boolean                 clientDidHandleServerRequest(const AbstractHeaderMessage *header, DataContainerReader *binaryBody) = 0;
            //
            // notifiche per l'upload di file verso il server:
            virtual void                    clientWillStartTransfer(const AbstractHeaderMessage *header, u_integer id, const buffer_pointer fileName);
            virtual void                    clientDidFinishTranfer(const AbstractHeaderMessage *header, u_integer id, const buffer_pointer fileName, TFileUploadResult sent);
    };

#endif // _IGAME_CLIENTBRIDGEPROVIDER_H
