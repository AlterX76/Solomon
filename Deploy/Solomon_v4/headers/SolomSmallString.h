


/******************************************************************************
 * Nome classe: SolomString													  *
 * ---------------------------------------------------------------------------*
 * Descrizione: oggetto per memorizzare informazioni stringa con operazioni   *
 *				necessarie in base alle specifiche dei protocolli.			  *
 * Data:		15/02/2007													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _SOLOMSMALLSTRING_H

    #define _SOLOMSMALLSTRING_H

	#include "Solomon.h"
    #include "SolomStringBuffer.h"
    //
    //
    class DataContainerWriter;
    class DataContainerReader;
    //
    //
    class DLL_ACTION SolomSmallString {
		private:
			byte					data_len; // Conterrà la lunghezza della stringa interna
            SolomStringBuffer		*data; // Conterrà la stringa assegnata
			DataContainerWriter		*m_buffer; // buffer interno utilizzato per restituire la rappresentazione in bytes dell'oggetto in questione
			//
			// membri statici:
            static const u_short	NumberOfBytesToRead;

			u_buffer_pointer		GetBytes(void); // Proprietà che restituisce la rappresentazione della stringa in formato array di bytes

		public:
			//
			// costruttori/distruttore:
            SolomSmallString(DataContainerReader *reader);
            SolomSmallString(buffer_pointer testo);
            ~SolomSmallString();
			//
			// funzioni:
            u_short					GetSizeOfSolomString(void); // Restituisce la lunghezza della stringa memorizzata secondo le specifiche dell'oggetto
            u_short                 GetLength(); // Restituisce la lunghezza della stringa memorizzata
			u_buffer_pointer		GetText(void); // restituisce il testo memorizzato nella struttura
			void					WriteIn(DataContainerWriter *writer); // memorizza nel buffer il contenuto stringa (secondo le specifiche) 
	};

#endif // _SOLOMSMALLSTRING_H
