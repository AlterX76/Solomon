#ifndef ISERVERBRIDGEPROVIDER_H
#define ISERVERBRIDGEPROVIDER_H

#if !defined MOBILE_BUILD

#include "Solomon.h"
#include <fstream>
#include <openssl/ssl.h>



class CUDPSocket;
class AbstractServerGame;
class AbstractTcpServerGame;
class AbstractHeaderMessage;
class AbstractBodyMessage;
class AttachedLinkMessage;
class ISpecializedPlugin;
class BaseInfoClient;
class TInfoConnection;
class GameServerClass;
// ---------------------------------------------------------------------------------------
// TPairMessage
// oggetto coppia per contenere header e/o body:
typedef struct TPairMessage {
    AbstractHeaderMessage   *header;
    AbstractBodyMessage     *body;

    TPairMessage();

} TPairMessage;
// ---------------------------------------------------------------------------------------
// AsyncServerUploadInfo
// utilizzato per contenere informazioni necessarie per l'upload asincrono dei file
class AsyncServerUploadInfo {
public:
    AsyncServerUploadInfo(AbstractHeaderMessage *header, AttachedLinkMessage *body, buffer_pointer pathAndFile, const AbstractServerGame *udpServer);
    ~AsyncServerUploadInfo();

    boolean                     isUploadCompleted() const ; // TRUE se il file e' stato completamente ricevuto; FALSE altrimenti
    void                        EnqueueRequest(BaseInfoClient *infoClient) const ; // accoda richiesta per essere elaborata dal server
    void                        WriteIn(const buffer_pointer buffer, integer buffer_len) const ;
    void                        EraseFile() ; // elimina fisicamente il file dal system
    void                        notifyClient(BaseInfoClient *infoClient, u_integer identifier) const; // notifica il client che il file e' stato correttamente ricevuto dal server
    const TPairMessage *        getRequest() const;

private:
    TPairMessage                _pairRequest;
    mutable ofstream            _streamNewFile;
    const AbstractServerGame    *_udpServer;
    string                      _pathAndFileName;
    mutable integer             _currentUploadedBytes;

    void                        CloseFile() const;
};

// ---------------------------------------------------------------------------------------
// BaseInfoClient
// classe base che verra' utilizzata internamente dal server per eseguire operazioni di manutenzione sulle connessioni.
// EREDITARE PER UTILIZZARE SLOT IN MEMORIA PER LE RICHIESTE.
class BaseInfoClient {
public:
    BaseInfoClient();
    virtual ~BaseInfoClient();

    sock                           getSocketId();
    void                           setSocketId(sock);
    SSL *                          getSslSocket();
    void                           setSslSocket(SSL *);
    void                           extendExpirationTime(); // aggiorna il timer interno per estendere l'inattivita' della connessione
    void                           forceExipirationTime(ISpecializedPlugin *); // forza inattivita' causando chiusura della connessione alla prossima GC
    time_t                         getActiveConnectionTime(); // ritorna il timer interno della connessione
    boolean                        getPermissionToUploadFile();
    void                           setPermissionToUploadFile(boolean active);
    u_integer                      getMaxBytesGrantToUpload();
    void                           setMaxBytesGrantToUpload(u_integer bytes);
    boolean                        getKeepPermanentStatus();   // status indicating if the connection is permanent or is involved in the GC process (that is time limited)
    void                           setKeepPermanentStatus(boolean permanent); // is permanent (true), it is client responsibility to release the connection setting the status to false again
    //
    // this call can affect the result of upload request if user has no upload rights on server: if marked as real connection, user will receive denied policy; if not, user will receive
    // a timeout response; this function is implemented to block fake connections performed sending wrong requests.
    void                           markAsRealConnection(); // mark the connection as real: neither a bot nor a fake connection, but performed by a human user
     boolean                       isRealConnection(); // returns TRUE if it is a real connection; FALSE otherwise
    //
    // classi/funzioni che puo' interagire con questa:
    friend class                   AbstractTcpServerGame;
    friend class                   GameServerClass;
    friend class                   AsyncServerUploadInfo;
    friend void *                  ClearPendingSocket(void *info);
#if defined (WIN32)
    friend void                    IncomingConnectionAction(void *container);
#elif defined (LINUX)
    friend void *                   IncomingConnectionAction(void *container);
#endif
    //
    // funzioni amiche per garantire l'accesso:
    friend void *                  StartTcpSupportedServer(void *raw);

private:
    sock                           sock_num; // id socket univoco assegnato dal sistema
    SSL                            *ssl_sock_num; // ssl socket object
    time_t                         timeActivity; // orario in cui e' avvenuta la connessione
    boolean                        permissionToUploadFile; // permesso di inviare file al server come richieste (true: abilitato; false altrimenti)    
    u_integer                      maxBytesUploadFile; // dimensione massima in bytes che questo client e' autorizzato ad inviare al server
    AsyncServerUploadInfo          *upload; // se diverso da NULL indica upload in corso sullo slot (oggetto aggregato che non viene eliminato dall'oggetto contenitore)
    TInfoConnection                *clientInfo; // conterra' IP e porta del client connesso
    boolean                        realConnection;
    boolean                        keepPermanent; // holds the status of the connection
    boolean                        oldKeepPermanent; // holds the previous value before an upload starts: trasfer a file sets automatically the connection as permanent and then it will restored with the previous value
    //
    // funzioni interne per la gestione del timer connessione:
    void                           setActiveConnectionTime(time_t time);
    //
    // funzione per la gestione degli upload dei files:
    const  AsyncServerUploadInfo * getUploadInfo();
    //
    // funzioni private di utilizzo comune:
    void                           setClientInfo(TInfoConnection *client);
    TInfoConnection *              getClientInfo();
};
// ---------------------------------------------------------------------------------------
// IServerBridgeProvider
// oggetto utilizzato nella pipeline del server per interagire con esso.
class IServerBridgeProvider {
public:
    IServerBridgeProvider();

    ISpecializedPlugin *                getPlugin();
    void                                setPlugin(ISpecializedPlugin *plugin);
    //
    // implementare in base al proprio protocollo:
    virtual                             ~IServerBridgeProvider();
    virtual BaseInfoClient *            createMemorySlot();
    virtual AbstractHeaderMessage *     createHeaderMessage() = 0;
    //
    // notifica prossima chiusura connessione; non eseguire operazioni di lunga durata in questa funzione
    // ritornare NULL se non si desidera che il server esegua operazioni;
    // il container ritornato deve essere allocato dinamicamente (anche i membri) e' sara' eliminato dal server in automatico
    virtual TPairMessage *              serverWillCloseConnection(const BaseInfoClient *info);
    //
    // notifica di avvenuta chiusura connessione
    // la chiusura di connessione avviene sempre dopo la relativa elaborazione della richiesta creata nell'evento serverWillCloseConnection
    virtual void                        serverDidCloseConnection(integer socketId);
    //
    // notifica richiesta non integra (lunghezze body/header non valide); non eseguire operazioni di lunga durata in questa funzione
    virtual void                        serverDidRejectRequest(const AbstractHeaderMessage *header);
    //
    // notifica esito elaborazione richiesta; non eseguire operazioni di lunga durata in questa funzione
    virtual void                        serverDidHandleRequest(const AbstractHeaderMessage *header, boolean handled);
    //
    // classi che possono accedere alla classe:
    friend class                        AbstractTcpServerGame;
    friend class                        AbstractServerGame;

private:
    ISpecializedPlugin                  *_plugin;
    AbstractServerGame                  *server;
    CUDPSocket                          *bgSocketServer;
};
#endif

#endif // ISERVERBRIDGEPROVIDER_H
