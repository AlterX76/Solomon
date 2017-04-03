

/*****************************************************************************
 * Strutture di vario utilizzo per l'uso interno ed esterno alla libreria.   *
 *****************************************************************************/


#ifndef _ABSTRACT_HEADER_MESSAGE_H

    #define _ABSTRACT_HEADER_MESSAGE_H

	#include "Solomon.h"
    //
    //
    class DataContainerReader;
    class DataContainerWriter;
    //
    //
	// Oggetto che rappresenta l'header per le richieste e le risposte:
    class DLL_ACTION AbstractHeaderMessage {
        private:
            AbstractHeaderMessage(const AbstractHeaderMessage&);
            AbstractHeaderMessage& operator=(const AbstractHeaderMessage&);
            //
            // membri che costituiscono l'header:
            u_integer                       lung_body; // Lunghezza totale del corpo del messaggio che deve essere inviato
            byte                            id_servizio; // Servizio che identifica il tipo di richiesta
            byte                            id_messaggio; // Messaggio che identifica il tipo di richiesta
            integer                         seq_id; // id univoco per intercettare risposta corretta in tcp
            byte                            isBufferFile; // indica se la richiesta e' da trattare come file e memorizzarlo su file system

            integer                         GetSequenceId() const;
            void                            SetSequenceId(integer value); // non usare direttamente (per ora solo in classi che saranno spostate nella core library)
            //
            // garantisce l'accesso esclusivo:
            friend class                    AsyncServerUploadInfo;
            friend class                    AbstractServiceClass;
            friend class                    AbstractTcpServerGame;
            friend class                    AbstractTcpEmbeddedServerGame;
            friend class                    ConcreteTcpEmbeddedServerGame;
            friend class                    GameClientClass;
            friend class                    GameServerClass;
            friend void *                   ClearPendingSocket(void *info);
            friend void *                   StartTcpSupportedServer(void *raw);
            friend void *                   IncomingConnectionAction(void *raw);

        public:
            //
            // costruttore default protetto:
            AbstractHeaderMessage();
            virtual ~AbstractHeaderMessage();
			//
			// membri per interfacciarsi con i membri interni:
            u_integer                       GetBodyLen(void) const;
            void                            SetBodyLen(u_integer value);
            byte                            GetIDService(void) const;
            void                            SetIDService(byte value);
            byte                            GetIDMessage(void) const;
            void                            SetIDMessage(byte value);
            void                            bufferFileAttached(byte value);
            byte                            isBufferFileAttached(void) const;
            void                            WriteIn(DataContainerWriter *writer, DataContainerWriter *body); // scrive tutti i campi header in writer usando body per indicare la lunghezza
			//
            // membri virtual:
            virtual byte                    SizeOfHeader(); // dimensione totale dell'header in numero di bytes            
            virtual void                    WriteIn(DataContainerWriter *writer, size_t lenBody); // uguale all'omonima, ma la lunghezza viene passata come parametro diretto
            virtual void                    ParseReader(DataContainerReader *reader); // richiamata in automatico dal costruttore con parametro (popola l'header recuperando i campi da reader)
	};
	
#endif // _ABSTRACT_HEADER_H
