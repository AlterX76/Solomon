
/******************************************************************************
 * viene utilizzata in tutte le intestazioni delle varie classi per prevedere *
 * la possibile esportazione/importazione della libreria.                     *
 ******************************************************************************/

#ifndef _SOLOMON_H

	#define _SOLOMON_H
	//
	// compilazione condizionale utilizzata per importare/esportare simboli:
	#if defined (BUILD_DLL) && defined(WIN32)
        #define DLL_ACTION		//__declspec(dllexport)
        #define STDCALL			//__stdcall // usata per l'esportazione di eventuali funzioni
	#elif defined (WIN32)
        #define DLL_ACTION		//__declspec(dllimport)
        #define STDCALL			//__stdcall // utilizzata per l'esportazione di eventuali funzioni
	#else
		#define DLL_ACTION // non valida per ambienti diversi, in particolare linux
		#define STDCALL // non valida per ambienti diversi, in particolare linux
	#endif	
    //
    // condizione da includere se si tratta di codice wrapper managed .net:
    #if defined (WRAPPER)
        #include "Stdafx.h" // presente nella directory del progetto wrapper
    #endif
	//
	// inclusioni per uso generale all'interno del software:
    #include "SyncronizeDefinition.h"
	#include <iostream>
	#include <sstream>
	#include <list>		
	#include <string.h>
	#include <errno.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <stddef.h>
	#include <time.h>
	//
	// rende visibile il namespace std per l'oggetto STL string:
	using namespace std;
	//
	// definizione di costanti simboliche:
    #define FALSE                           (0)
    #define TRUE							!(FALSE)

#if defined (LINUX)
    #include <arpa/inet.h>
#elif defined (WIN32)
	#pragma warning(disable:4251) // disabilita i warnings derivati dall'uso delle STL in DLL
#endif

	#define MAX_IP_CHAR						16  // (es: xxx.xxx.xxx.xxx)
	#define MAX_BUFFER_SOCK					(1024 + 1)
	#define MAX_SEND_RECEIVE_TIMEOUT		4 // attesa di 4 secondi
	#define MAX_BUFFER_DATA_CONTAINERS		1024 // da utilizzare per indicare la dimensione dei DataContainerXXXXXX
	#define CRLF							"\r\n"
	#define EMPTY_STRING					""
    #define DIM_DEFAULT_BUFFER_RCV          (64 + 1) // dimensione default consentita per un pacchetto UDP in ricezione
	//
	// definizione di costante simbolica da utilizzare per il fill del buffer:
	#define DEFAULT_CHAR_TO_RPAD			' '	 // spazio da utiliizare come carattere
	#define CHAR_BUFFER_CLOSER				'\0' // rappresenta la chiusura di un buffer di caratteri
    //
    // servizio 255 riservato per le comunicazioni interne del server:
    #define SERVICE_RESERVED_COMMUNICATION  255 // comunicazione riservata    
    //
    // messaggi riservati al server centrale verso i satelliti:
    #define MESSAGE_TICKET_ID               255 // ticket inviato al client a connessione eseguita
    #define MESSAGE_START_FILE_UPLOAD       254 // invia al client notifica di avviare upload
    #define MESSAGE_RECEIVED_FILE_UPLOAD    253 // inviato dal server per indicare al client che un file e' stato ricevuto correttamente
    #define MESSAGE_DENIED_FILE_UPLOAD      252 // invia al client notifica di accesso negato per invio file (o mancanza di permesso o dimensione superiore al consentito)
    #define MESSAGE_CONN_CLOSED_BY_SERVER   251 // inviata al client per notificare chiusura di connessione da parte del server
    //
    // messaggi riservati alle comunicazioni interne tra server:
    #define MESSAGE_SERVER_CLUSTER_NOT      50 // notifica inviata da un server verso un altro server per inoltrare messaggio ad un client
    //
	//
	// definizione di tipi primitivi:	
	typedef unsigned char					byte;
    typedef char							caracter;
    typedef int								integer;
    typedef long							longer;
    typedef unsigned long                   u_longer;
    typedef	short							shorter;
    typedef unsigned long					u_long;
    typedef double							currency;
	typedef float							geo;
    typedef unsigned int					u_integer;
    typedef unsigned short					u_short;
    typedef unsigned char					u_char;
    typedef u_char							boolean;
	//
	// definizione di tipi per il funzionamento su più sistemi:
	typedef integer							sock; 
#if defined (WIN32)
    typedef u_long                          in_addr_t;
#endif
	//
	// operazioni su caratteri:
	typedef caracter *						buffer_pointer;
	typedef byte *							u_buffer_pointer;
	typedef caracter						ip_string[MAX_IP_CHAR];	
	
#endif  //_SOLOMON_H
