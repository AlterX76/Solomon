
/******************************************************************************
 * Nome classe: AbstractTcpServerGame   									  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Server tcp minimale utilizzzato per la sola comunicazione     *
 *              verso i client satelliti per bypassare la limitazione udp.	  *
 * Data:		31/12/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _ABSTRACT_TCP_SERVER_GAME_H

    #define _ABSTRACT_TCP_SERVER_GAME_H

#ifndef MOBILE_BUILD
	//
	// include tutto ciò che server per il corretto funzionamento del software.
	#include "Solomon.h"
    #include "MemorySlotFilter.h"
	//
	// inclusioni relative ad i vari sistemi operativi:
	#if defined (WIN32)
		#include <winbase.h>
	#elif defined (LINUX)
		#include <pthread.h>
        #include <netinet/tcp.h>
        #include <signal.h>

        #if !defined BLACKBERRY && !defined MACOSX
            #include <sys/epoll.h>
        #endif
    #endif
    #include <openssl/ssl.h>
    //
    //
    // definizione per raggiungere membri privati della classe astratta:
    class GameServerClass;
    class AbstractServerGame;
    class AbstractBodyMessage;
    class AbstractHeaderMessage;
    class BaseInfoClient;
    class IServerBridgeProvider;
    class CTCPSocket;
    class TInfoConnection;
	//
	//
	//dichiarazione della classe:
    class DLL_ACTION AbstractTcpServerGame {
        private:
            CTCPSocket                  *m_bgServer; // oggetto principale per la creazione del socket UDP e join nel multicast
            sock                        m_udpServerSocket;
            list<BaseInfoClient *>      *m_acceptedSockList;
            TInfoConnection             *m_connectionInfo; // informazioni di connessione locale
            pthread_t                   m_serverGamePthreadId;
            pthread_t                   m_garbageThreadID;
            pthread_rwlock_t            m_syncPendingSockList;
            pthread_rwlock_t            m_syncTotalSockList;
            pthread_mutex_t             m_mutex;
            pthread_mutex_t             m_mutexUniqueIdFileName;
            pthread_mutex_t             m_mutexUniqueIdSessionToken;
            IServerBridgeProvider       *_bridge;
            const u_integer             _maxPacketSize; // max dimension (header + body) of a request thru tcp
            list<BaseInfoClient *>      totalSockList;
            u_short                     m_headerDimension;
            integer                     efd; // epoll fd
            //
            // costruttori:
            AbstractTcpServerGame(const AbstractTcpServerGame&);
            //
            // redifinizione operatore:
            AbstractTcpServerGame& operator=(const AbstractTcpServerGame&);

            void                        LockQueue(pthread_mutex_t *mutex); // effettua il lock per m_QueueLocker
            void                        UnlockQueue(pthread_mutex_t *mutex); // effettua l'unlock per m_QueueLocker
            AbstractServerGame *        getUdpServer();
            void                        closeSocket(sock idSocket, SSL *ssl_idSocket); // esegue chiusura del socket e invia header con comunicazione di chiusura
            integer                     sendReservedMsgToClient(byte message, sock client_fd, SSL *ssl_client_fd);
            static integer              receiveAll(sock socket, SSL *ssl_socket, u_buffer_pointer *buffer, size_t len, boolean treatAsFile = FALSE, const buffer_pointer fileName = NULL); // buffer viene sempre dinamicamente allocato di dimensione len
            inline void                 cleanFileUploadForClient(BaseInfoClient *info, boolean deleteAttached);
            inline void                 add_epoll(BaseInfoClient *info);
            inline void                 del_epoll(BaseInfoClient *info);
            inline void                 mod_epoll(BaseInfoClient *info);            
            //
            // funzione per l'avvio del server game:
            friend void *               StartTcpSupportedServer(void *info); // avvia il server per la ricezione richieste
            friend void *               ClearPendingSocket(void *info); // loop per la pulizia delle connessioni rimaste in CLOSE_WAIT
            friend void                 hdl_server_tcp(int sig, siginfo_t *siginfo, void *context);
            friend void *               IncomingConnectionAction(void *container);
        #if defined (WIN32)
            friend void                 InternalExecutionQueue(void *threadInfo);
        #elif defined (LINUX)
            friend void *               InternalExecutionQueue(void *threadInfo);
        #endif

            friend class                GameServerClass;
            //
            // funzione statica utilizzata come wrapper per richiamare funzione membro virtuale:
        #if defined (WIN32)
            static void                 DownloadTcpRequest(void *container);
            static void                 HotPluginAction(void *container);
        #elif defined (LINUX)
            static void	*               DownloadTcpRequest(void *container);
            static void *               HotPluginAction(void *container);
        #endif

        public:
            //
            // costruttore:
            AbstractTcpServerGame(IServerBridgeProvider *bridge, u_integer maxPacketSize);
            //
            // Distruttore virtuale:
            virtual                     ~AbstractTcpServerGame();
            //
            // funzioni per la sincronizzazione delle informazioni:
            void                        startListenServer(); // avvia il server e ritorna immediatamente (avvia il server su un nuovo thread)
            u_integer                   stopServer();
            ssize_t                     sendMessage(SSL *ssl_id_socket, integer id_client, AbstractHeaderMessage *header, AbstractBodyMessage *body) const;
            BaseInfoClient *            findMemorySlot(sock id); // esegue ricerca tramite socket per identificare l'area di memoria personalizzata

            template <typename T>
            BaseInfoClient *            findMemorySlot(BaseMemorySlotFilter<T>& filterObject, T& key);
            buffer_pointer              createUniqueSessionToken(); // crea session token univoco per server (max lunghezza: 30 bytes)
	};

#endif
	
#endif // _ABSTRACT_SERVER_GAME_H
