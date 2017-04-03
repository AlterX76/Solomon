


/******************************************************************************
 * Nome classe: SolomLargeString												  *
 * ---------------------------------------------------------------------------*
 * Descrizione: oggetto per memorizzare informazioni stringa con operazioni   *
 *				necessarie in base alle specifiche dei protocolli.			  *
 *				Simile a ConiString, ma gestisce vettori più lunghi di 256    *
 *				caratteri.													  *
 * Data:		03/02/2007													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/



#ifndef _SOLOMLARGESTRING_H

    #define _SOLOMLARGESTRING_H

	#include "Solomon.h"
	#include "SolomStringBuffer.h"

    class DataContainerWriter;


    class DLL_ACTION SolomLargeString {
		private:
            u_short                     data_len; // Conterrà la lunghezza della stringa interna
            SolomStringBuffer           *data; // Conterrà la stringa assegnata
            DataContainerWriter         *m_buffer; // buffer interno utilizzato per restituire la rappresentazione in bytes dell'oggetto in questione
			//
			// membri statici:
            static const u_short        NumberOfBytesToRead; // secondo le specifiche dei protocolli (2 byte)

		public:
			//
			// costruttori/distruttore:
            SolomLargeString(DataContainerReader *reader);
            SolomLargeString(const buffer_pointer testo);
            ~SolomLargeString();
			//
			// funzioni:
            u_short						GetSizeOfSolomString(void); // Restituisce la dimensione interna (compresa la stringa)
			u_buffer_pointer			GetBytes(void); // Proprietà che restituisce la rappresentazione della stringa in formato array di bytes
			u_buffer_pointer			GetText(void); // restituisce il testo memorizzato nella struttura
            u_short                     GetTextLength(); // restituisce la lunghezza della stringa contenuta nell'oggetto
            void                        WriteIn(DataContainerWriter *writer);
	};

#endif // _SOLOMLARGESTRING_H
