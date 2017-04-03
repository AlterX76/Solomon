
#ifndef ICLIENTBRIDGEPROVIDER_H
    #define ICLIENTBRIDGEPROVIDER_H

    #include "Solomon.h"
    //
    //
    // stati per verificare il risultato dell'upload di un file:
    typedef enum TFileUploadResult {
        fileUploadSuccess = 0,
        fileUploadConnectionError,          // problemi nell'inviare richiesta al server
        fileUploadTimeoutFromServerError,   // il server non ha risposto alla richiesta di invio file da parte del client
        fileUploadOpenLocalFileError,       // problemi con l'apertura del file da inviare al server
        fileUploadDeniedError,              // il server ha risposto con una negazione di upload
        fileUploadExceedFileSizeError       // dimensione del file superiore alla capacita' consentita dalle specifiche del protocollo
    } TFileUploadResult;
    //
    // definizione per il server embedded:
    class AbstractTcpEmbeddedServerGame;
    class AbstractHeaderMessage;
    class DataContainerReader;
    // ---------------------------------------------------------------------------------------
    // IClientBridgeProvider
    // oggetto utilizzato nella pipeline del client per interagire con esso.
    class DLL_ACTION IClientBridgeProvider {
        public:
            IClientBridgeProvider();
            //
            // implementare in base al proprio protocollo:
            virtual                         ~IClientBridgeProvider();
            virtual AbstractHeaderMessage * createHeaderMessage() = 0;
            //
            // notifica di avvenuta connessione con il server:
            virtual void                    clientDidStartTcpConnection();
            virtual void                    clientDidStartUdpConnection();
            //
            // notifica chiusura connessione con il server:
            virtual void                    clientDidCloseTcpConnection();
            virtual void                    clientDidCloseUdpConnection();
            //
            // richiamata quando si riceve dal server una richiesta da gestire.
            // ritornare TRUE se la richiesta e' stata gestita dal client; FALSE altrimenti.
            virtual boolean                 clientDidHandleServerTcpRequest(const AbstractHeaderMessage *header, DataContainerReader *binaryBody) = 0;
            //
            // richiamata quando si riceve dal server una richiesta da gestire:
            virtual void                    clientDidHandleServerUdpRequest(const AbstractHeaderMessage *header, DataContainerReader *binaryBody) = 0;
            //
            // notifiche per l'upload di file verso il server (solo per tcp):
            virtual void                    clientWillStartFileUpload(const AbstractHeaderMessage *header, u_integer id, const buffer_pointer fileName);
            virtual void                    clientDidFinishFileUpload(const AbstractHeaderMessage *header, u_integer id, const buffer_pointer fileName, TFileUploadResult sent);
            virtual void                    serverDidReceiveFile(u_integer identifier);
            //
            // accesso riservato per la classe:
            friend class                    AbstractTcpEmbeddedServerGame;
    };

#endif // ICLIENTBRIDGEPROVIDER_H
