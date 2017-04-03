


/*****************************************************************************************
 * Interfaccia da specializzare per l'utilizzo di plugin esterni.
 *****************************************************************************************/


#ifndef _ISPECIALIZED_PLUGIN_H

	#define _ISPECIALIZED_PLUGIN_H

#ifndef MOBILE_BUILD
	//
	// include tutto ciò che server per il corretto funzionamento del software.
    #include "Solomon.h"
    //
    // forward declaration:
    class TInfoConnection;
	//
	// 
	// 
	// ---------------------- INTERFACCE UTILIZZATE PER L'IMPLEMENTAZIONE DEGLI OGGETTI DI INTERFACCIAMENTO CON LA FONTE DATI ---------------
    //
	// Interfaccia per la creazione dell'oggetto che permetterà di effettuare periodicamente operazioni varie:
	class DLL_ACTION ISpecializedPlugin {
		public:
            //
            // recupera connessione verso il database:
            virtual void *              GetConnection(void) = 0;
            virtual void                ReleaseConnection(void *conn) = 0;
			//
            // Funzioni per la configurazione di avvio del server di gioco (parametri recuperati dal file xml di configurazione):
            virtual TInfoConnection * 	GetServerInfo(void) = 0;
			virtual u_short				GetWorkersNumber(void) = 0;
			virtual u_short				GetPoolThreadsNumber(void) = 0;
            virtual u_short             GetMaxSecsToCloseInactiveConn() = 0; // secondi dopo i quali la connessione viene considerata inattiva e quindi chiusa
            virtual u_short             GetSecondsToStartGarbage() = 0; // secondi dopo i quali parte il check sulle connessioni per effettuare pulizia (indica valore a intevalli)
            virtual buffer_pointer      GetCommandsPath(void) = 0;
            virtual buffer_pointer      GetSystemUploadRoot(void) = 0;
            virtual buffer_pointer      GetLinkDownloadRoot(void) = 0;
            virtual buffer_pointer      GetTrustedPassword(void) = 0;
            virtual boolean             GetPermissionToUploadFile() = 0;
            virtual boolean             GetKeepConnectionPermanent() = 0; // returns if the connection needs to be permanent (no analisys by the GC) as default value
            virtual boolean             GetHotLoadPluginState() = 0; // return status indicating if the server has to enable the hot-load plugin support            
            virtual u_longer            GetMaxBytesFileUpload() = 0;
            virtual buffer_pointer      GetSslCertificate() = 0; // returns path+filename of the certificate the server will use for ssl connections; if empty, ssl is not supported
            //
			//
			// Distruttore:
            virtual						~ISpecializedPlugin() {} // distruttore dell'interfaccia
	};

#endif
	
#endif // _ISPECIALIZED_MULTICAST_H
