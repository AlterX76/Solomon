

#ifndef MOBILE_BUILD

#ifndef _PLUGIN_LOADER_H

	#define _PLUGIN_LOADER_H

	#include "Solomon.h"
    #include "Structures.h"
    #include "Types.h"


    using namespace Solomon::Types;

    class TInfoConnection;
    //
    // struttura contenente i parametri da recuperare tramite il plugin config:
    typedef struct TConfigParameters {
        SmallString     m_dns; // eventuale stringa di connessione, ODBC o altro...dati recuperati dal file di configurazione (nome: nome_plugin.dll.config)
        SmallString     m_username; // username per eventuale accesso database o altro
        SmallString     m_password; // password per eventuale autenticazione con username
        LargeString     m_commandsPath; // percorso in cui sono memorizzati i commands da caricare
        TInfoConnection *m_serverInfo; // dati recuperati dal file di configurazione (nome: nome_plugin.dll.config);
        u_short         m_workerThreadNumber; // numero di code e threadpool che il server deve allocare; dati recuperati dal file di configurazione (nome: nome_plugin.dll.config)
        u_short         m_poolThreadsNumber; // numero di threads da creare per ogni threadpool; dati recuperati dal file di configurazione (nome: nome_plugin.dll.config)
        u_short         m_connTimeout; // attesa massima in secondi verso il database
        u_short         m_intervalGarbage; // intervallo in secondi per l'attivazione della pulizia delle connessioni tcp
        u_short         m_secsInactiveConnection; // secondi di inattivita' per cui una connessione e' considerata spazzatura e puo' essere terminata
        LargeString     m_systemUploadRoot; // percorso su file system in cui salvare i file inviati come richiesta
        LargeString     m_linkDownloadRoot; // percorso pubblico da cui e' possibile eseguire download di file ricevuti come richiesta
        boolean         m_permissionToUploadFile; // autorizzazione all'invio di file verso il server (valore di default iniziale per tutti i clients)
        boolean         m_keepConnectionPermanent; // valore di default per una nuova connessione: true connessione non soggetta alla GC
        boolean         m_hotLoadPluginEnabled; // indica se il server deve attivare il monitor sui plugin per eseguire aggiunta/rimozione a caldo        
        u_longer        m_maxSizeBytesFile; // dimensione massima in bytes dei file che il server accetta (valore di default iniziale per tutti i clients)
        SmallString     m_internalTrustedPassswd; // password interna per eseguire commands solo dall'interno o per altre attivita' di sicurezza
        LargeString     m_ssl_certificate; // if ssl is required on the server, this will contain path and certificate filename to be loaded

        TConfigParameters();
        ~TConfigParameters();
    } TConfigParameters;
    //
	//
	// dichiarazione del tipo puntatore a funzione per il caricamento del plugin:
    class ISpecializedPlugin;
    typedef ISpecializedPlugin *	(*PluginPointerFunction)(TConfigParameters *);
    typedef void *                  SimpleXmlParser;
    //
	//
	// Dichiarazione della classe che permette di caricare i plugin
	class DLL_ACTION PluginLoader {
		private:
			void					*m_LibraryPointer;	// contiene il riferimento alla libreria del plugin
            PluginPointerFunction	m_function; // puntatore alla funzione di ingresso del plugin
            LargeString             m_filename; // percorso del plugin selezionato
            TConfigParameters       configParameters; // parametri letti dal file config e passati all'istanza specializzata del plugin
			//
			// funzioni:
			void					LoadConfigFile(void); // legge le informazioni per la creazione dell'environment
			//
			// funzioni amiche:
            friend void *			ParserXML(SimpleXmlParser parser, ushort event, const buffer_pointer szName, const buffer_pointer szAttribute, const buffer_pointer szValue);

		public:
            PluginLoader(buffer_pointer PercorsoPlugin);
			~PluginLoader();
			//
            // Retriving plugin function:
			ISpecializedPlugin *	GetPlugin(void); // effettua le operazioni necessarie ed estrae il plugin dalla libreria. Restituisce NULL se non riesce nell'operazione
	};

#endif

#endif	// _PLUGIN_LOADER_H
