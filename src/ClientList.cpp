//
// This file is part of the aMule Project.
//
// Copyright (c) 2003-2005 aMule Team ( admin@amule.org / http://www.amule.org )
// Copyright (c) 2002 Merkur ( devs@emule-project.net / http://www.emule-project.net )
//
// Any parts of this program derived from the xMule, lMule or eMule project,
// or contributed by third-party developers are copyrighted by their
// respective authors.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA, 02111-1307, USA
//

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "ClientList.h"
#endif

#include "amule.h"			// Needed for theApp
#include "ClientList.h"		// Interface declarations.
#include "ListenSocket.h"	// Needed for CClientReqSocket
#include "DownloadQueue.h"	// Needed for CDownloadQueue
#include "UploadQueue.h"	// Needed for CUploadQueue
#include "IPFilter.h"		// Needed for CIPFIlter
#include "ClientCredits.h"
#include "updownclient.h"	// Needed for CUpDownClient
#include "OPCodes.h"
#include "GetTickCount.h"	// Needed for GetTickCount()
#include "OtherFunctions.h" // Needed for IP_FROM_GUI_ID and PORT_FROM_GUI_ID
#include "ServerConnect.h" // Needed for theApp.serverconnect
#include "Preferences.h" // Needed for thePrefs
#include "Logger.h"
#include "Format.h"

#include <algorithm>

#include "kademlia/routing/Contact.h"

#ifdef __COMPILE_KAD__
#include "kademlia/kademlia/Kademlia.h"
#include "kademlia/kademlia/Prefs.h"
#include "kademlia/kademlia/Search.h"
#include "kademlia/net/KademliaUDPListener.h"
#endif

/**
 * CDeletedClient Class
 *
 * This class / list is a bit overkill, but currently needed to avoid any
 * exploit possibtility. It will keep track of certain clients attributes
 * for 2 hours, while the CUpDownClient object might be deleted already.
 * Currently saves: IP, Port, UserHash.
 */
class CDeletedClient
{
public:
	CDeletedClient(CUpDownClient* pClient)
	{
		m_dwInserted = ::GetTickCount();
		PortAndHash porthash = { pClient->GetUserPort(), pClient->Credits()};
		m_ItemsList.push_back(porthash);
	}
	
	struct PortAndHash
	{
		uint16 nPort;
		void* pHash;
	};

	typedef std::list<PortAndHash> PaHList;
	PaHList	m_ItemsList;
	uint32	m_dwInserted;
};



CClientList::CClientList()
	: m_deadSources( true )
{
	m_dwLastBannCleanUp = 0;
	m_dwLastTrackedCleanUp = 0;
	m_dwLastClientCleanUp = 0;
	m_pBuddy = NULL;
	m_nBuddyStatus = Disconnected;
}


CClientList::~CClientList()
{
	std::map<uint32, CDeletedClient*>::iterator it = m_trackedClientsList.begin();
	for ( ; it != m_trackedClientsList.end(); ++it ){
		delete it->second;
	}

	m_trackedClientsList.clear();
}


void CClientList::AddClient( CUpDownClient* toadd )
{
	// Ensure that only new clients can be added to the list
	if ( toadd->GetClientState() == CS_NEW ) {
		// Update the client-state
		toadd->m_clientState = CS_LISTED;
	
 		Notify_ClientCtrlAddClient( toadd );
	
		// We always add the ID/ptr pair, regardles of the actual ID value
		m_clientList.insert( IDMapPair( toadd->GetUserIDHybrid(), toadd ) );

		// We only add the IP if it is valid
		if ( toadd->GetIP() ) {
			m_ipList.insert( IDMapPair( toadd->GetIP(), toadd ) );
		}

		// We only add the hash if it is valid
		if ( toadd->HasValidHash() ) {
			m_hashList.insert( HashMapPair( toadd->GetUserHash(), toadd ) );
		}
	}
}


void CClientList::AddToDeleteQueue(CUpDownClient* client)
{
	// We have to remove the client from the list immediatly, to avoit it getting
	// found by functions such as AttachToAlreadyKnown and GetClientsFromIP, 
	// however, if the client isn't on the clientlist, then it is safe to delete 
	// it right now. Otherwise, push it onto the queue.
	if ( RemoveIDFromList( client ) ) {
		// Also remove the ip and hash entries
		RemoveIPFromList( client );
		RemoveHashFromList( client );
		
		m_delete_queue.push_back( client );
	} else {
		delete client;
	}
}


void CClientList::UpdateClientID( CUpDownClient* client, uint32 newID )
{
	// Sainity check
	if ( ( client->GetClientState() != CS_LISTED ) || ( client->GetUserIDHybrid() == newID ) )
		return;

	// First remove the ID entry
	RemoveIDFromList( client );

	// Add the new entry
	m_clientList.insert( IDMapPair( newID, client ) );
}


void CClientList::UpdateClientIP( CUpDownClient* client, uint32 newIP )
{
	// Sainity check
	if ( ( client->GetClientState() != CS_LISTED ) || ( client->GetIP() == newIP ) )
		return;

	// Remove the old IP entry
	RemoveIPFromList( client );

	if ( newIP ) {
		m_ipList.insert( IDMapPair( newIP, client ) );
	}
}

	
void CClientList::UpdateClientHash( CUpDownClient* client, const CMD4Hash& newHash )
{
	// Sainity check
	if ( ( client->GetClientState() != CS_LISTED ) || ( client->GetUserHash() == newHash ) )
		return;


	// Remove the old entry
	RemoveHashFromList( client );

	// And add the new one if valid
	if ( !newHash.IsEmpty() ) {
		m_hashList.insert( HashMapPair( newHash, client ) );
	}
}


bool CClientList::RemoveIDFromList( CUpDownClient* client )
{
	bool result = false;

	// First remove the ID entry
	std::pair<IDMap::iterator, IDMap::iterator> range = m_clientList.equal_range( client->GetUserIDHybrid() );

	for ( ; range.first != range.second; range.first++ ) {
		if ( client == range.first->second ) {
			m_clientList.erase( range.first );

			result = true;

			break;
		}
	}
	
	return result;
}


void CClientList::RemoveIPFromList( CUpDownClient* client )
{
	// Check if we need to look for the IP entry
	if ( !client->GetIP() )
		return;
		
	// Remove the IP entry
	std::pair<IDMap::iterator, IDMap::iterator> range = m_ipList.equal_range( client->GetIP() );

	for ( ; range.first != range.second; range.first++ ) {
		if ( client == range.first->second ) {
			m_ipList.erase( range.first );
			
			break;
		}
	}
}


void CClientList::RemoveHashFromList( CUpDownClient* client )
{
	// Nothing to remove
	if ( !client->HasValidHash() )
		return;

	// Find all items with the specified hash
	std::pair<HashMap::iterator, HashMap::iterator> range = m_hashList.equal_range( client->GetUserHash() );

	for ( ; range.first != range.second; range.first++ ) {
		if ( client == range.first->second ) {
			m_hashList.erase( range.first );

			break;
		}
	}
}


CUpDownClient* CClientList::FindMatchingClient( CUpDownClient* client )
{
	// LowID clients need a different set of checks
	if ( client->HasLowID() ) {
		// Find all matching entries. First searching for ID.
		std::pair<IDMap::iterator, IDMap::iterator> range = m_clientList.equal_range( client->GetUserIDHybrid() );

		IDMap::iterator it = range.first;
		for ( ; it != range.second; it++ ) {
			// Check if the port ( and server for lowids ) matches
			if ( it->second->GetUserPort() == client->GetUserPort() ) {
				// For lowid, we also have to check the server
				if ( client->GetServerIP() == it->second->GetServerIP() )
					return it->second;
			}
		}
	} else {
		// Find all matching entries. First searching for ID.
		std::pair<IDMap::iterator, IDMap::iterator> range = m_clientList.equal_range( client->GetUserIDHybrid() );

		IDMap::iterator it = range.first;
		for ( ; it != range.second; it++ ) {
			// Check if the port ( and server for lowids ) matches
			if ( it->second->GetUserPort() == client->GetUserPort() )
				return it->second;
		}

	
		// Still nothing? Search for the IP
		if ( client->GetIP() ) {
			// Find all matching entries
			std::pair<IDMap::iterator, IDMap::iterator> range = m_ipList.equal_range( client->GetIP() );

			IDMap::iterator it = range.first;
			for ( ; it != range.second; it++ ) {
				// Check if the port ( and server for lowids ) matches
				if ( it->second->GetUserPort() == client->GetUserPort() ) {
					return it->second;
				}
			}
		}
	}
		
		
	// If anything else fails, then we look at hashes
	if ( client->HasValidHash() ) {
		// Find all items with the specified hash
		std::pair<HashMap::iterator, HashMap::iterator> range = m_hashList.equal_range( client->GetUserHash() );

		// Just return the first item if any
		if ( range.first != range.second ) 
			return range.first->second;
	}

	// Nothing found, must be a new client
	return NULL;
}


uint16 CClientList::GetBannedCount() const
{
	return m_bannedList.size();
}


uint32 CClientList::GetClientCount() const
{
	return m_clientList.size(); 
}


void CClientList::DeleteAll()
{
	theApp.uploadqueue->DeleteAll();
	theApp.downloadqueue->ClearAllSources();

	m_ipList.clear();
	m_hashList.clear();
	
	while ( !m_clientList.empty() ) {
		IDMap::iterator it = m_clientList.begin();
	
		delete it->second;
			
		m_clientList.erase( it );
	}
	
	while ( !m_delete_queue.empty() ) {
		delete m_delete_queue.front();
		m_delete_queue.pop_front();
	}
}


void CClientList::GetStatistics(uint32 &totalclient, uint32 stats[], ClientMap *clientVersionEDonkey, ClientMap *clientVersionEDonkeyHybrid, ClientMap *clientVersionEMule, ClientMap *clientVersionAMule, aMuleOSInfoMap* OSMap)
{
	totalclient = m_clientList.size();
	
	if (clientVersionEDonkey) {
		clientVersionEDonkey->clear();
	}
		
	if (clientVersionEMule) {
		clientVersionEMule->clear();
	}
		
	if (clientVersionEDonkeyHybrid) {
		clientVersionEDonkeyHybrid->clear();
	}
		
	if (clientVersionAMule) {
		clientVersionAMule->clear();
	}
	
	if (OSMap) {
		OSMap->clear();
	}


	for ( int i = 0; i < 19; i++ ) {
		stats[i] = 0;
	}

	IDMap::iterator it = m_clientList.begin();
	for ( IDMap::iterator it = m_clientList.begin(); it != m_clientList.end(); ++it ) {
		CUpDownClient* cur_client =	it->second;
		
		if (cur_client->HasLowID()) {
			stats[11]++;
			if (cur_client->GetClientSoft()!=SO_UNKNOWN) {
				stats[18]++;
			}
		}
		
		switch (cur_client->GetClientSoft()) {
			case SO_UNKNOWN : 
				stats[0]++;
				break;
			case SO_EDONKEY : 
				stats[1]++;
				if(clientVersionEDonkey) {
					(*clientVersionEDonkey)[cur_client->GetVersion()]++;
				}
				break;
			case SO_EDONKEYHYBRID : 
				stats[4]++;
				if(clientVersionEDonkeyHybrid) {
					(*clientVersionEDonkeyHybrid)[cur_client->GetVersion()]++;
				}
				break;
				
			case SO_EMULE   :
			case SO_OLDEMULE:
				if(clientVersionEMule) {
					uint8 version = cur_client->GetMuleVersion();
					if (version == 0xFF || version == 0x66 || version==0x69 || version==0x90 || version==0x33 || version==0x60) {
						continue;					
					}
					(*clientVersionEMule)[cur_client->GetVersion()]++;
				}
			case SO_EMULEPLUS: // And SO_EMULE and SO_OLDEMULE (no break before this)
				stats[2]++;
				break;
			
			case SO_CDONKEY : 
				stats[5]++;
				break;
			case SO_LXMULE:
				stats[6]++;
				break;
			case SO_AMULE:
				stats[8]++;
				if(clientVersionAMule) {
					uint8 version = cur_client->GetMuleVersion();
					if (version == 0xFF || version == 0x66 || version==0x69 || version==0x90 || version==0x33 || version==0x60) {
						continue;					
					}
					(*clientVersionAMule)[cur_client->GetVersion()]++;
				}
				if (OSMap) {
					wxString OS = cur_client->GetClientOSInfo();
					if (!OS.IsEmpty()) {
						(*OSMap)[OS]++;	
					}
				}
				break;
			case SO_MLDONKEY:
				stats[3]++;
				break;
			case SO_NEW_MLDONKEY:
			case SO_NEW2_MLDONKEY:
				stats[7]++;
				break;
			case SO_COMPAT_UNK:
				stats[9]++;
				break;
			case SO_LPHANT:
				stats[10]++;
				break;
			case SO_SHAREAZA:
				stats[16]++;
				break;
		}
		
		if (cur_client->Credits() != NULL){
			switch(cur_client->Credits()->GetCurrentIdentState(cur_client->GetIP())){
				case IS_IDENTIFIED:
					stats[12]++;
					break;
				case IS_IDFAILED:
				case IS_IDNEEDED:
				case IS_IDBADGUY:
					stats[13]++;
				default:
					break;
			}
		}
		
		if (cur_client->GetSocket()) {
			stats[17]++;
		}
	}
}


bool CClientList::AttachToAlreadyKnown(CUpDownClient** client, CClientReqSocket* sender)
{
	CUpDownClient* tocheck = (*client);
	
	CUpDownClient* found_client = FindMatchingClient( tocheck );

	if ( tocheck == found_client ) {
		// We found the same client instance (client may have sent more than one OP_HELLO). do not delete that client!
		return true;
	}
		
	if (found_client != NULL){
		if (sender) {
			if (found_client->GetSocket()) {
				if (found_client->IsConnected() 
					&& (found_client->GetIP() != tocheck->GetIP() || found_client->GetUserPort() != tocheck->GetUserPort() ) )
				{
					// if found_client is connected and has the IS_IDENTIFIED, it's safe to say that the other one is a bad guy
					if (found_client->Credits() && found_client->Credits()->GetCurrentIdentState(found_client->GetIP()) == IS_IDENTIFIED){
						AddDebugLogLineM( false, logClient, wxT("Client: ") + tocheck->GetUserName() + wxT("(") + tocheck->GetFullIP() +  wxT("), Banreason: Userhash invalid")); 
						tocheck->Ban();
						return false;
					}
	
					AddDebugLogLineM( false, logClient, wxT("WARNING! Found matching client, to a currently connected client: ") 
															+ tocheck->GetUserName() + wxT("(") +  tocheck->GetFullIP() 
															+ wxT(") and ") + found_client->GetUserName() + wxT("(") +  found_client->GetFullIP() + wxT(")"));
					return false;
				}
				found_client->GetSocket()->SetClient( NULL );
				found_client->GetSocket()->Safe_Delete();
			}
			found_client->SetSocket( sender );
			tocheck->SetSocket( NULL );
		}
		*client = 0;
		tocheck->Safe_Delete();
		*client = found_client;
		return true;
	}
	
	return false;
}


CUpDownClient* CClientList::FindClientByIP( uint32 clientip, uint16 port )
{
	// Find all items with the specified ip
	std::pair<IDMap::iterator, IDMap::iterator> range = m_ipList.equal_range( clientip );

	for ( ; range.first != range.second; range.first++ ) {
		CUpDownClient* cur_client =	range.first->second;
		// Check if it's actually the client we want
		if ( cur_client->GetUserPort() == port )
			return cur_client;
	}

	return NULL;
}


bool CClientList::ComparePriorUserhash(uint32 dwIP, uint16 nPort, void* pNewHash)
{
	std::map<uint32, CDeletedClient*>::iterator it = m_trackedClientsList.find( dwIP );
	
	if ( it != m_trackedClientsList.end() ) {
		CDeletedClient* pResult = it->second;
	
		CDeletedClient::PaHList::iterator it = pResult->m_ItemsList.begin();
		for ( ; it != pResult->m_ItemsList.end(); it++ ) {
			if ( it->nPort == nPort ) {
				if ( it->pHash != pNewHash) {
					return false;
				} else {
					break;
				}
			}
		}
	}
	return true;
}


void CClientList::AddTrackClient(CUpDownClient* toadd)
{
	std::map<uint32, CDeletedClient*>::iterator it = m_trackedClientsList.find( toadd->GetIP() );
	
	if ( it != m_trackedClientsList.end() ) {
		CDeletedClient* pResult = it->second;
	
		pResult->m_dwInserted = ::GetTickCount();

		CDeletedClient::PaHList::iterator it = pResult->m_ItemsList.begin();
		for ( ; it != pResult->m_ItemsList.end(); it++ ) {
			if ( it->nPort == toadd->GetUserPort() ) {
				// already tracked, update
				it->pHash = toadd->Credits();
				return;
			}
		}
	
		// New client for that IP, add an entry
		CDeletedClient::PortAndHash porthash = { toadd->GetUserPort(), toadd->Credits()};
		pResult->m_ItemsList.push_back(porthash);
	} else {
		m_trackedClientsList[ toadd->GetIP() ] = new CDeletedClient(toadd);
	}
}


uint16 CClientList::GetClientsFromIP(uint32 dwIP)
{
	std::map<uint32, CDeletedClient*>::iterator it = m_trackedClientsList.find( dwIP );
	
	if ( it != m_trackedClientsList.end() ) {
		return it->second->m_ItemsList.size();
	} else {
		return 0;
	}
}


void CClientList::Process()
{
	const uint32 cur_tick = ::GetTickCount();

	// Delete pending clients
	while ( !m_delete_queue.empty() ) {
		CUpDownClient* toremove = m_delete_queue.front();
		m_delete_queue.pop_front();
		
		// Doing what RemoveClient used to do. Just to be sure...
		theApp.uploadqueue->RemoveFromUploadQueue( toremove );
		theApp.uploadqueue->RemoveFromWaitingQueue( toremove );
		theApp.downloadqueue->RemoveSource( toremove );
	
		Notify_ClientCtrlRemoveClient( toremove );
				
		delete toremove;
	}
	
	if (m_dwLastBannCleanUp + BAN_CLEANUP_TIME < cur_tick) {
		m_dwLastBannCleanUp = cur_tick;
		
		ClientMap::iterator it = m_bannedList.begin();
		while ( it != m_bannedList.end() ) {
			if ( it->second + CLIENTBANTIME < cur_tick ) {
				ClientMap::iterator tmp = it++;		
				
				m_bannedList.erase( tmp );
			} else {
				it++;
			}
		}
	}

	
	if ( m_dwLastTrackedCleanUp + TRACKED_CLEANUP_TIME < cur_tick ) {
		m_dwLastTrackedCleanUp = cur_tick;
		
		std::map<uint32, CDeletedClient*>::iterator it = m_trackedClientsList.begin();
		while ( it != m_trackedClientsList.end() ) {
			std::map<uint32, CDeletedClient*>::iterator cur_src = it++;
			
			if ( cur_src->second->m_dwInserted + KEEPTRACK_TIME < cur_tick ) {
				delete cur_src->second;
				m_trackedClientsList.erase( cur_src );
			}
		}
	}
	
	#ifdef __COMPILE_KAD__
	//We need to try to connect to the clients in m_KadList
	//If connected, remove them from the list and send a message back to Kad so we can send a ACK.
	//If we don't connect, we need to remove the client..
	//The sockets timeout should delete this object.

	// buddy is just a flag that is used to make sure we are still connected or connecting to a buddy.
	buddyState buddy = Disconnected;

	for (std::set<CUpDownClient*>::iterator it = m_KadSources.begin(); it != m_KadSources.end(); ++it) {
		CUpDownClient* cur_client = *it;
		if( !Kademlia::CKademlia::isRunning() ) {
			//Clear out this list if we stop running Kad.
			//Setting the Kad state to KS_NONE causes it to be removed in the switch below.
			cur_client->SetKadState(KS_NONE);
		}
		switch (cur_client->GetKadState()) {
			case KS_QUEUED_FWCHECK:
				//Another client asked us to try to connect to them to check their firewalled status.
				cur_client->TryToConnect(true);
				break;

			case KS_CONNECTING_FWCHECK:
				//Ignore this state as we are just waiting for results.
				break;

			case KS_CONNECTED_FWCHECK:
				//We successfully connected to the client.
				//We now send a ack to let them know.
				Kademlia::CKademlia::getUDPListener()->sendNullPacket(KADEMLIA_FIREWALLED_ACK, ENDIAN_NTOHL(cur_client->GetIP()), cur_client->GetKadPort());
				//We are done with this client. Set Kad status to KS_NONE and it will be removed in the next cycle.
				cur_client->SetKadState(KS_NONE);
				break;

			case KS_INCOMING_BUDDY:
				//A firewalled client wants us to be his buddy.
				//If we already have a buddy, we set Kad state to KS_NONE and it's removed in the next cycle.
				//If not, this client will change to KS_CONNECTED_BUDDY when it connects.
				if( m_nBuddyStatus == Connected ) {
					cur_client->SetKadState(KS_NONE);
				}
				break;

			case KS_QUEUED_BUDDY:
				//We are firewalled and want to request this client to be a buddy.
				//But first we check to make sure we are not already trying another client.
				//If we are not already trying. We try to connect to this client.
				//If we are already connected to a buddy, we set this client to KS_NONE and it's removed next cycle.
				//If we are trying to connect to a buddy, we just ignore as the one we are trying may fail and we can then try this one.
				if( m_nBuddyStatus == Disconnected ) {
					buddy = Connecting;
					m_nBuddyStatus = Connecting;
					cur_client->SetKadState(KS_CONNECTING_BUDDY);
					cur_client->TryToConnect(true);
					Notify_ServerUpdateMyInfo();
				} else {
					if( m_nBuddyStatus == Connected ) {
						cur_client->SetKadState(KS_NONE);
					}
				}
				break;

			case KS_CONNECTING_BUDDY:
				//We are trying to connect to this client.
				//Although it should NOT happen, we make sure we are not already connected to a buddy.
				//If we are we set to KS_NONE and it's removed next cycle.
				//But if we are not already connected, make sure we set the flag to connecting so we know 
				//things are working correctly.
				if( m_nBuddyStatus == Connected ) {
					cur_client->SetKadState(KS_NONE);
				} else {
					wxASSERT( m_nBuddyStatus == Connecting );
					buddy = Connecting;
				}
				break;

			case KS_CONNECTED_BUDDY:
				//A potential connected buddy client wanting to me in the Kad network
				//We set our flag to connected to make sure things are still working correctly.
				buddy = Connected;
				
				//If m_nBuddyStatus is not connected already, we set this client as our buddy!
				if( m_nBuddyStatus != Connected ) {
					m_pBuddy = cur_client;
					m_nBuddyStatus = Connected;
					Notify_ServerUpdateMyInfo();
				}
				if( m_pBuddy == cur_client && theApp.IsFirewalled() && cur_client->SendBuddyPingPong() ) {
					cur_client->SendBuddyPing();
				}
				break;

			default:
				RemoveFromKadList(cur_client);
		}
	}
	
	//We either never had a buddy, or lost our buddy..
	if( buddy == Disconnected ) {
		if( m_nBuddyStatus != Disconnected || m_pBuddy ) {
			if( Kademlia::CKademlia::isRunning() && theApp.IsFirewalled() ) {
				//We are a lowID client and we just lost our buddy.
				//Go ahead and instantly try to find a new buddy.
				Kademlia::CKademlia::getPrefs()->setFindBuddy();
			}
			m_pBuddy = NULL;
			m_nBuddyStatus = Disconnected;
			Notify_ServerUpdateMyInfo();
		}
	}

	if ( Kademlia::CKademlia::isConnected() ) {
		if( Kademlia::CKademlia::isFirewalled() ) {
			if( m_nBuddyStatus == Disconnected && Kademlia::CKademlia::getPrefs()->getFindBuddy() ) {
				//We are a firewalled client with no buddy. We have also waited a set time 
				//to try to avoid a false firewalled status.. So lets look for a buddy..
				Kademlia::CSearch *findBuddy = new Kademlia::CSearch;
				findBuddy->setSearchTypes(Kademlia::CSearch::FINDBUDDY);
				Kademlia::CUInt128 ID(true);
				ID.XOR(Kademlia::CKademlia::getPrefs()->getKadID());
				findBuddy->setTargetID(ID);
				if( !Kademlia::CSearchManager::startSearch(findBuddy) ) {
					//This search ID was already going. Most likely reason is that
					//we found and lost our buddy very quickly and the last search hadn't
					//had time to be removed yet. Go ahead and set this to happen again
					//next time around.
					Kademlia::CKademlia::getPrefs()->setFindBuddy();
				}
			}
		} else {
			if( m_pBuddy ) {
				//Lets make sure that if we have a buddy, they are firewalled!
				//If they are also not firewalled, then someone must have fixed their firewall or stopped saturating their line.. 
				//We just set the state of this buddy to KS_NONE and things will be cleared up with the next cycle.
				if( !m_pBuddy->HasLowID() ) {
					m_pBuddy->SetKadState(KS_NONE);
				}
			}
		}
	} else {
		if( m_pBuddy ) {
			//We are not connected anymore. Just set this buddy to KS_NONE and things will be cleared out on next cycle.
			m_pBuddy->SetKadState(KS_NONE);
		}
	}
	#endif
	
	CleanUpClientList();
}


void CClientList::AddBannedClient(uint32 dwIP)
{
	m_bannedList[dwIP] = ::GetTickCount();
}


bool CClientList::IsBannedClient(uint32 dwIP)
{
	ClientMap::iterator it = m_bannedList.find( dwIP );
		
	if ( it != m_bannedList.end() ) {
		if ( it->second + CLIENTBANTIME > ::GetTickCount() ) {
			return true;
		} else {
			RemoveBannedClient(dwIP);
		}
	}
	return false; 
}


void CClientList::RemoveBannedClient(uint32 dwIP)
{
	m_bannedList.erase(dwIP);
}


void CClientList::FilterQueues()
{
	// Filter client list
	IDMap::iterator it = m_ipList.begin();
	for ( IDMap::iterator it = m_ipList.begin(); it != m_ipList.end(); ) {
		IDMap::iterator tmp = it++;
		
		if ( theApp.ipfilter->IsFiltered(tmp->second->GetConnectIP())) {
			tmp->second->Disconnected(wxT("Filtered by IPFilter"));
			tmp->second->Safe_Delete();
		}
	}
}


CClientList::SourceList	CClientList::GetClientsByHash( const CMD4Hash& hash )
{
	SourceList results;

	// Find all items with the specified hash
	std::pair<HashMap::iterator, HashMap::iterator> range = m_hashList.equal_range( hash );

	for ( ; range.first != range.second; range.first++ )  {
		results.push_back( range.first->second );
	}
	
	return results;
}


CClientList::SourceList	CClientList::GetClientsByIP( unsigned long ip )
{
	SourceList results;

	// Find all items with the specified hash
	std::pair<IDMap::iterator, IDMap::iterator> range = m_ipList.equal_range( ip );

	for ( ; range.first != range.second; range.first++ )  {
		results.push_back( range.first->second );
	}
	
	return results;
}


const CClientList::IDMap& CClientList::GetClientList()
{
	return m_clientList;
}


void CClientList::AddDeadSource(const CUpDownClient* client)
{
	m_deadSources.AddDeadSource( client );
}


bool CClientList::IsDeadSource(const CUpDownClient* client)
{
	return m_deadSources.IsDeadSource( client );
}

bool CClientList::SendMessage(uint64 client_id, const wxString& message)
{
	CUpDownClient* client = FindClientByIP(IP_FROM_GUI_ID(client_id), PORT_FROM_GUI_ID(client_id));
	AddDebugLogLineM( false, logClient, wxT("Trying to Send Message.") );
	if (client) {
		AddDebugLogLineM( false, logClient, wxT("Sending.") );
	} else {
		AddDebugLogLineM( true, logClient, 
			CFormat( wxT("No client (GUI_ID %lli [%s:%llu]) found in CClientList::SendMessage(). Creating") ) 
				% client_id 
				% Uint32toStringIP(IP_FROM_GUI_ID(client_id))
				% PORT_FROM_GUI_ID(client_id) );
		client = new CUpDownClient(PORT_FROM_GUI_ID(client_id),IP_FROM_GUI_ID(client_id),0,0,NULL, true, true);
		AddClient(client);
	}
	return client->SendMessage(message);
}

void CClientList::SetChatState(uint64 client_id, uint8 state) {
	CUpDownClient* client = FindClientByIP(IP_FROM_GUI_ID(client_id), PORT_FROM_GUI_ID(client_id));
	if (client) {
		client->SetChatState(state);
	}
}

/* Kad stuff */
#warning KAD TODO: client list handling needs a big import.

void CClientList::RequestTCP(Kademlia::CContact* contact)
{
	#ifdef __COMPILE_KAD__
	uint32 nContactIP = ENDIAN_NTOHL(contact->getIPAddress());
	// don't connect ourself
	if (theApp.serverconnect->GetLocalIP() == nContactIP && thePrefs::GetPort() == contact->getTCPPort()) {
		return;
	}

	CUpDownClient* pNewClient = FindClientByIP(nContactIP, contact->getTCPPort());

	if (!pNewClient) {
		#warning Do we actually have to check friendstate here?
		pNewClient = new CUpDownClient(contact->getTCPPort(), contact->getIPAddress(), 0, 0, NULL, false, true);
	}

	//Add client to the lists to be processed.
	pNewClient->SetKadPort(contact->getUDPPort());
	pNewClient->SetKadState(KS_QUEUED_FWCHECK);
	AddToKadList(pNewClient); // This was a direct adding, but I like to check duplicates
	//This method checks if this is a dup already.
	AddClient(pNewClient);
	#endif
}

void CClientList::RequestBuddy(Kademlia::CContact* contact)
{
	#ifdef __COMPILE_KAD__
	
	uint32 nContactIP = ENDIAN_NTOHL(contact->getIPAddress());
	// Don't connect to ourself
	if (theApp.serverconnect->GetLocalIP() == nContactIP && thePrefs::GetPort() == contact->getTCPPort()) {
		return;
	}
	
	CUpDownClient* pNewClient = FindClientByIP(nContactIP, contact->getTCPPort());
	if (!pNewClient) {
		pNewClient = new CUpDownClient(contact->getTCPPort(), contact->getIPAddress(), 0, 0, NULL, false, true );
	}

	//Add client to the lists to be processed.
	pNewClient->SetKadPort(contact->getUDPPort());
	pNewClient->SetKadState(KS_QUEUED_BUDDY);
	byte ID[16];
	contact->getClientID().toByteArray(ID);
	pNewClient->SetUserHash(ID);
	AddToKadList(pNewClient);
	//This method checks if this is a dup already.
	AddClient(pNewClient);
	
	#endif
}

void CClientList::IncomingBuddy(Kademlia::CContact* contact, Kademlia::CUInt128* buddyID )
{
	#ifdef __COMPILE_KAD__
	
	uint32 nContactIP = ENDIAN_NTOHL(contact->getIPAddress());
	//If eMule already knows this client, abort this.. It could cause conflicts.
	//Although the odds of this happening is very small, it could still happen.
	if (FindClientByIP(nContactIP, contact->getTCPPort())) {
		return;
	}

	// don't connect ourself
	if (theApp.serverconnect->GetLocalIP() == nContactIP && thePrefs::GetPort() == contact->getTCPPort()) {
		return;
	}

	//Add client to the lists to be processed.
	CUpDownClient* pNewClient = new CUpDownClient(contact->getTCPPort(), contact->getIPAddress(), 0, 0, NULL, false, true );
	pNewClient->SetKadPort(contact->getUDPPort());
	pNewClient->SetKadState(KS_INCOMING_BUDDY);
	byte ID[16];
	contact->getClientID().toByteArray(ID);
	pNewClient->SetUserHash(ID);
	buddyID->toByteArray(ID);
	pNewClient->SetBuddyID(ID);
	AddToKadList(pNewClient);
	AddClient(pNewClient);
	#endif
}

void CClientList::RemoveFromKadList(CUpDownClient* torem) {
	#ifdef __COMPILE_KAD__
	
	wxASSERT(torem);
	
	if (m_KadSources.erase(torem)) {
		if(torem == m_pBuddy) {
			m_pBuddy = NULL;
			Notify_ServerUpdateMyInfo();
		}
	}
		
	#endif
}

void CClientList::AddToKadList(CUpDownClient* toadd) {
	#ifdef __COMPILE_KAD__
	
	if(!toadd) {
		return;
	}
	
	m_KadSources.insert(toadd); // This will take care of duplicates.
	
	#endif
}

void CClientList::CleanUpClientList(){
	// We remove clients which are not needed any more by time
	// this check is also done on CUpDownClient::Disconnected, however it will not catch all
	// cases (if a client changes the state without beeing connected
	//
	// Adding this check directly to every point where any state changes would be more effective,
	// is however not compatible with the current code, because there are points where a client has
	// no state for some code lines and the code is also not prepared that a client object gets
	// invalid while working with it (aka setting a new state)
	// so this way is just the easy and safe one to go (as long as emule is basically single threaded)
	const uint32 cur_tick = ::GetTickCount();
	if (m_dwLastClientCleanUp + CLIENTLIST_CLEANUP_TIME < cur_tick ){
		m_dwLastClientCleanUp = cur_tick;
		uint32 cDeleted = 0;
		for (IDMap::iterator it = m_clientList.begin(); it != m_clientList.end();/*nothing*/) {
			IDMap::iterator it2 = it++; // Don't change this to a ++it!!!!
			CUpDownClient* pCurClient = it2->second;
			if ((pCurClient->GetUploadState() == US_NONE || pCurClient->GetUploadState() == US_BANNED && !pCurClient->IsBanned())
				&& pCurClient->GetDownloadState() == DS_NONE
				&& pCurClient->GetChatState() == MS_NONE
				&& pCurClient->GetKadState() == KS_NONE
				&& pCurClient->GetSocket() == NULL)
			{
				cDeleted++;
				delete pCurClient; 
				m_clientList.erase(it2);
			}
		}
		AddDebugLogLineM(false, logClient, wxString::Format(wxT("Cleaned ClientList, removed %i not used known clients"), cDeleted));
	}
}
