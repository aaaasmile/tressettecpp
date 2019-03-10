//cInvidoCoreEngine.cpp
#include "StdAfx.h"
#include "cInvidoCore.h"
#include "cMazzo.h"
#include "TraceService.h"

////////////////////////////////////////////////////////////////
// **********************   CINVIDOCORE CLASS *****************
////////////////////////////////////////////////////////////////


// Constructor
cInvidoCore::cInvidoCore()
{
	m_lNumPlayers = 0;
	m_pPlHaveToPlay = 0;
	m_pStartPlayer = 0;
	m_pMyMazzo = 0;
	resetCardInfoPlayers();
}



////////////////////////////////////////
//       ~cInvidoCore
/*! Destructor
*/
cInvidoCore::~cInvidoCore()
{
	delete m_pMyMazzo;
}


////////////////////////////////////////
//       Create
/*! Create the core game
// \param cPlayer* pHmiPlayer : player instanciated in hmi
// \param int iNumPlayers : number of players
*/
void cInvidoCore::Create(cPlayer* pHmiPlayer, int iNumPlayers)
{
	m_pTracer = TraceService::Instance();
	//TRACE("cInvidoCore is created\n");
	m_pTracer->AddSimpleTrace(2, "cInvidoCore is created");

	//deck
	m_pMyMazzo = new cMazzo();
	m_pMyMazzo->SetCoreEngine(this);
	m_pMyMazzo->Create();

	m_PlayersOnTable.Create(pHmiPlayer, iNumPlayers);

	m_eGameType = LOCAL_TYPE;

	// init state
	m_Partita.SetCore(this);
	m_Partita.SetGiocata(&m_Giocata);

	m_Giocata.SetCore(this);
	m_Giocata.SetPartita(&m_Partita);
	m_Giocata.SetMano(&m_Mano);

	m_Mano.SetCore(this);
	m_Mano.SetGiocata(&m_Giocata);
	m_Mano.SetScore(&m_MatchPoints);

	m_lNumPlayers = iNumPlayers;

	for (int i = 0; i < MAX_NUM_PLAYER; i++)
	{
		m_vctAlgPlayer[i] = 0;
	}

	m_MatchPoints.SetManoObj(&m_Mano);

}


////////////////////////////////////////
//       WhoWonsTheGame
/*! Provides the player index who wons the game. If the game is drawn pbIsDrawn is set to TRUE.
// \param long* plPlayerIx : return winner index
// \param BOOL* pbIsDrawn : return TRUE if the game has no winner, otherwise FALSE
*/
BOOL  cInvidoCore::WhoWonsTheGame(cPlayer** ppPlayer)
{
	ASSERT(ppPlayer);
	ASSERT(0);

	return TRUE;
}

int  cInvidoCore::getNewMatchFirstPlayer()
{
    return CASO(m_lNumPlayers);
}

////////////////////////////////////////
//       NewMatch
/*! Start an Invido new match
*/
void  cInvidoCore::NewMatch()
{
	NotifyScript(SCR_NFY_NEWMATCH);

	// extract the first player
	int iFirstPlayer = getNewMatchFirstPlayer();

	// save players alg in a table
	// don't change level during a match
	for (int i = 0; i < m_lNumPlayers; i++)
	{
		cPlayer* pPlayer = m_PlayersOnTable.GetPlayerIndex(i);
		m_vctAlgPlayer[i] = pPlayer->GetAlg();
		if (m_vctAlgPlayer[i])
		{
			// information before match begin
			m_vctAlgPlayer[i]->ALG_SetPlayerIndex(pPlayer->GetIndex());
			m_vctAlgPlayer[i]->ALG_SetCoreInterface(this);
			m_vctAlgPlayer[i]->ALG_NewMatch(m_lNumPlayers);
			if (i == 0)
			{
				if (m_lNumPlayers == 2)
				{
					// invido 2 player
					m_vctAlgPlayer[i]->ALG_SetOpponentIndex(1, 0);
				}
				else if (m_lNumPlayers == 4)
				{
					// invido 4 players
					m_vctAlgPlayer[i]->ALG_SetOpponentIndex(1, 0);
					m_vctAlgPlayer[i]->ALG_SetOpponentIndex(3, 1);
				}
				else
				{
					ASSERT(0);
				}
			}
			else if (i == 1)
			{
				if (m_lNumPlayers == 2)
				{
					// invido 2 player
					m_vctAlgPlayer[i]->ALG_SetOpponentIndex(0, 0);
				}
				else
				{
					// invido 4 players
					m_vctAlgPlayer[i]->ALG_SetOpponentIndex(0, 0);
					m_vctAlgPlayer[i]->ALG_SetOpponentIndex(2, 1);
				}
			}
			else if (i == 2)
			{
				m_vctAlgPlayer[i]->ALG_SetOpponentIndex(1, 0);
				m_vctAlgPlayer[i]->ALG_SetOpponentIndex(3, 1);
			}
			else if (i == 3)
			{
				m_vctAlgPlayer[i]->ALG_SetOpponentIndex(0, 0);
				m_vctAlgPlayer[i]->ALG_SetOpponentIndex(2, 1);
			}
			else
			{
				ASSERT(0);
			}
		}
	}

	m_Mano.MatchStart();
	m_PlayersOnTable.SetFirstOnMatch(iFirstPlayer);
	m_pStartPlayer = m_PlayersOnTable.GetPlayerIndex(iFirstPlayer);
	m_Partita.NewPartita(iFirstPlayer);
	m_MatchPoints.MatchStart(m_lNumPlayers);
}




////////////////////////////////////////
//       GetPlayerInPlaying
/*! Return the index of the player that must play
// \param long * plPlayerIx :
*/
BOOL  cInvidoCore::GetPlayerInPlaying(cPlayer** ppPlayer)
{
	ASSERT(ppPlayer);

	*ppPlayer = m_pPlHaveToPlay;

	return TRUE;
}

////////////////////////////////////////
//       NextAction
/*! Trigger the next state
*/
void  cInvidoCore::NextAction()
{
	m_Mano.NextAction();
	m_Giocata.NextAction();
	m_Partita.NextAction();
}



////////////////////////////////////////
//       isCardInPlayerHand
/*! return true if the card is on player hand, false otherwise
*/
CardSpec* cInvidoCore::isCardInPlayerHand(int iPlayerIx, const CARDINFO* pCardInfo)
{
	CardSpec* pCardSpecRes = NULL;
	ASSERT(pCardInfo);
	ASSERT(iPlayerIx >= 0 && iPlayerIx < MAX_NUM_PLAYER);

	CardSpec  myCard;
	myCard.SetCardInfo(*pCardInfo);

	for (int i = 0; i < NUM_CARDS_HAND; i++)
	{
		int iPlayerPosIx = iPlayerIx * NUM_CARDS_HAND + i;
		if (m_aCardInfo[iPlayerPosIx] == myCard)
		{
			pCardSpecRes = &m_aCardInfo[iPlayerPosIx];
			break;
		}
	}

	return pCardSpecRes;
}


////////////////////////////////////////
//       resetCardInfoPlayers
/*! Reset information on card about all players.
*/
void cInvidoCore::resetCardInfoPlayers()
{
	int iSize = NUM_CARDS_HAND * MAX_NUM_PLAYER;
	for (int i = 0; i < iSize; i++)
	{
		m_aCardInfo[i].Reset();
	}
}


////////////////////////////////////////
//       resetCard
/*! reset informatio about a card on player hand. This is called after that a player has played a card.
*/
BOOL  cInvidoCore::resetCard(int iPlayerIx, CARDINFO* pCardInfo)
{
	BOOL bRet = FALSE;
	ASSERT(pCardInfo);
	ASSERT(iPlayerIx >= 0 && iPlayerIx < MAX_NUM_PLAYER);

	CardSpec  myCard;
	myCard.SetCardInfo(*pCardInfo);

	for (int i = 0; i < NUM_CARDS_HAND; i++)
	{
		int iPlayerPosIx = iPlayerIx * NUM_CARDS_HAND + i;
		if (m_aCardInfo[iPlayerPosIx] == myCard)
		{
			bRet = TRUE;
			m_aCardInfo[iPlayerPosIx].Reset();
			break;
		}
	}

	return bRet;
}

////////////////////////////////////////
//       Giocata_Start
/*! Shuffle the cards and distribuite the cards
// \param long lPlayerIx : player index that must play
*/
void cInvidoCore::Giocata_Start(long lPlayerIx)
{
	TRACE("Nuova giocata\n");

	// reset card info of all players
	resetCardInfoPlayers();
	// shuffle cards
	m_pMyMazzo->Shuffle();
	// distribuite the cards
	CardSpec tmpCard;
	m_PlayersOnTable.SetFirstOnGiocata(lPlayerIx);

	// 1) first - calculate the table (there is no switch)
	// player that have to play first, is the first that get the cards after shuffle
	int aPlayerDeck[MAX_NUM_PLAYER];
	m_PlayersOnTable.CalcCircleIndex(aPlayerDeck);

	// 2) second - retreive the player that have to play and switch the table
	m_pPlHaveToPlay = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::SWITCH_TO_NEXT);

	// 3) distribuite cards
	for (int i = 0; i < m_lNumPlayers; i++)
	{
		int iIxCurrPLayer = aPlayerDeck[i];
		ASSERT(iIxCurrPLayer >= 0 && iIxCurrPLayer < m_lNumPlayers);

		cPlayer* pCurrPlayer = m_PlayersOnTable.GetPlayerIndex(iIxCurrPLayer);
		CARDINFO CardArray[NUM_CARDS_HAND];

		TRACE("%s => ", pCurrPlayer->GetName());

		for (int j = 0; j < NUM_CARDS_HAND; j++)
		{
			// distribuite all cards on player
			m_pMyMazzo->PickNextCard(&tmpCard);

			tmpCard.FillInfo(&CardArray[j]);
			TRACE("[%s] , ix: %d, pt: %d", tmpCard.GetName(), tmpCard.GetCardIndex(), tmpCard.GetPoints());

			// store card information for controlling
			int iTmpCdIndex = iIxCurrPLayer * NUM_CARDS_HAND + j;
			m_aCardInfo[iTmpCdIndex] = tmpCard;
		}
		TRACE("\n");
		if (m_vctAlgPlayer[iIxCurrPLayer])
		{
			m_vctAlgPlayer[iIxCurrPLayer]->ALG_NewGiocata(CardArray, NUM_CARDS_HAND, lPlayerIx);
		}
	}
	m_MatchPoints.GiocataStart();
	// notify script 
	NotifyScript(SCR_NFY_NEWGIOCATA);
	// notify mano
	m_Mano.GiocataStart();

}



////////////////////////////////////////
//       Mano_End
/*! A mano is terminated.
*/
void cInvidoCore::Mano_End()
{
	m_MatchPoints.ManoEnd();
	int iPlayer = m_MatchPoints.GetManoWinner();


	if (m_MatchPoints.IsManoPatada())
	{
		// trick patada
		// set the same player that have start
		long lPlayer = m_PlayersOnTable.GetFirstOnTrick();
		m_PlayersOnTable.SetFirstOnTrick(lPlayer);

	}
	else
	{
		// update the table, the trick winner have to play first
		m_PlayersOnTable.SetFirstOnTrick(iPlayer);
	}
	m_pPlHaveToPlay = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::SWITCH_TO_NEXT);
	m_Giocata.Update_Giocata(m_pPlHaveToPlay->GetIndex(), &m_MatchPoints);


	for (int i = 0; i < m_lNumPlayers; i++)
	{
		if (m_vctAlgPlayer[i])
		{
			m_vctAlgPlayer[i]->ALG_ManoEnd(&m_MatchPoints);
		}
	}
	// notify script 
	NotifyScript(SCR_NFY_ALGMANOEND);
}


////////////////////////////////////////
//       Giocata_AMonte
/*! A giocata is going to "A monte"
*/
void cInvidoCore::Giocata_AMonte()
{
	m_MatchPoints.AMonte();
	m_Giocata.Update_Giocata(NOT_VALID_INDEX, &m_MatchPoints);
}

////////////////////////////////////////
//       Player_VaVia
/*! The player abandon the giocata
// \param int iPlayerIx : Player index that abandon the giocata
*/
void cInvidoCore::Player_VaVia(int iPlayerIx)
{
	//ASSERT(0); 
	m_MatchPoints.PlayerVaVia(iPlayerIx);

	m_Giocata.Update_Giocata(iPlayerIx, &m_MatchPoints);
}


////////////////////////////////////////
//       ChangeGiocataScore
/*! Giocata score is changed
// \param eGiocataScoreState eNewScore :
*/
void cInvidoCore::ChangeGiocataScore(eGiocataScoreState eNewScore)
{
	for (int i = 0; i < m_lNumPlayers; i++)
	{
		if (m_vctAlgPlayer[i])
		{
			m_vctAlgPlayer[i]->ALG_GicataScoreChange(eNewScore);
		}
	}
}

////////////////////////////////////////
//       Giocata_End
/*! Giocata is ended
*/
void   cInvidoCore::Giocata_End()
{
	// calculate points
	m_MatchPoints.GiocataEnd();
	// update match state machine
	m_Partita.Update_Partita(&m_MatchPoints);

	for (int i = 0; i < m_lNumPlayers; i++)
	{
		if (m_vctAlgPlayer[i])
		{
			m_vctAlgPlayer[i]->ALG_GiocataEnd(&m_MatchPoints);
		}
	}

	NotifyScript(SCR_NFY_ALGGIOCATAEND);
}


////////////////////////////////////////
//       Partita_End
/*! Match is terminated. Iform all algorithms
*/
void  cInvidoCore::Partita_End()
{
	for (int i = 0; i < m_lNumPlayers; i++)
	{
		if (m_vctAlgPlayer[i])
		{
			m_vctAlgPlayer[i]->ALG_MatchEnd(&m_MatchPoints);
		}
	}
	NotifyScript(SCR_NFY_ALGMATCHEND);
}


////////////////////////////////////////
//       AbandonGame
/*! The player abandon the game, the game is teminated
// \param int iPlayerIx : player index that abandon the game
*/
void cInvidoCore::AbandonGame(int iPlayerIx)
{
	int iNextPlayer;
	int aPlayerDeck[MAX_NUM_PLAYER];
	m_PlayersOnTable.CalcCircleIndex_Cust(aPlayerDeck, iPlayerIx);
	// give the victory to the next player
	iNextPlayer = aPlayerDeck[1];

	m_MatchPoints.SetTheWinner(iNextPlayer);

	for (int i = 0; i < m_lNumPlayers; i++)
	{
		if (m_vctAlgPlayer[i])
		{
			m_vctAlgPlayer[i]->ALG_MatchEnd(&m_MatchPoints);
		}
	}
}

////////////////////////////////////////
//       NtyWaitingPlayer_Toplay
/*! Inform algorithm  that player  have to play
*/
void   cInvidoCore::NtyWaitingPlayer_Toplay(int iPlayerIx)
{
	ASSERT(m_pPlHaveToPlay);
	ASSERT(iPlayerIx == m_pPlHaveToPlay->GetIndex());

	I_ALG_Player* pAlg = m_vctAlgPlayer[iPlayerIx];
	ASSERT(pAlg);

	// algorithm have to play
	pAlg->ALG_Play();

}

////////////////////////////////////////
//       NtyWaitingPlayer_ToResp
/*! Inform algorithm that player  have to responce
// \param int iPlayerIx : player index
*/
void   cInvidoCore::NtyWaitingPlayer_ToResp(int iPlayerIx)
{
	I_ALG_Player* pAlg = m_vctAlgPlayer[iPlayerIx];
	ASSERT(pAlg);

	pAlg->ALG_HaveToRespond();
}

////////////////////////////////////////
//       NtyPlayerSayBuiada
/*! The player say something not corerct
// \param int iPlayerIx : player index
*/
void  cInvidoCore::NtyPlayerSayBuiada(int iPlayerIx)
{
	for (int i = 0; i < m_lNumPlayers; i++)
	{
		// notify all players that a player says something not correct
		if (m_vctAlgPlayer[i])
		{
			m_vctAlgPlayer[i]->ALG_PlayerSaidWrong(iPlayerIx);
		}

	}
}


////////////////////////////////////////
//       RaiseError
/*! To make error handling message system gui indipendent.
// \param const std::string &errorMsg :
*/
void cInvidoCore::RaiseError(const std::string &errorMsg)
{
	ASSERT(0);
	TRACE(const_cast<char *>(errorMsg.c_str()));
    TRACE("\n");
}


CardSpec* cInvidoCore::checkValidCardPlayed(int iPlayerIx, const CARDINFO* pCardInfo)
{
    CardSpec cardUndef;
    if (cardUndef.GetCardIndex() == pCardInfo->byIndex)
    {
        ASSERT(0);
    }

    CardSpec* pCardplayed = isCardInPlayerHand(iPlayerIx, pCardInfo);
    
    return pCardplayed;
}

BOOL cInvidoCore::Player_vaDentro(int iPlayerIx, const CARDINFO* pCardInfo)
{
    CardSpec* pCardplayed = checkValidCardPlayed(iPlayerIx, pCardInfo);
    if (pCardplayed == NULL)
    {
        return FALSE;
    }
    
    BOOL bRes = FALSE;
    // change mano state
    if (m_Mano.Player_Play(iPlayerIx, TRUE))
    {
        // next player is on game
        m_pPlHaveToPlay = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::SWITCH_TO_NEXT);

        // update match points
        int ixCardVaDentro = 3;
        CARDINFO cardVadodentro; // quattro di bastoni, carta sempre perdente
        cardVadodentro.byIndex = ixCardVaDentro; 
        strncpy(cardVadodentro.CardName, g_CardsNameX[ixCardVaDentro].c_str(), NUM_BYTE_NAME);
        cardVadodentro.eSuit = BASTONI;

        m_MatchPoints.PlayerPlay(iPlayerIx, &cardVadodentro);

        for (int i = 0; i < m_lNumPlayers; i++)
        {
            // notify all players that a card was played
            if (m_vctAlgPlayer[i])
            {
                m_vctAlgPlayer[i]->ALG_PlayerHasVadoDentro(iPlayerIx);
            }
        }

        // reset info about played card
        resetCard(iPlayerIx, pCardplayed->GetCardInfo());
        bRes = TRUE;
    }
    return bRes;
}

////////////////////////////////////////
//       Player_playCard
/*! A player have played a card, terminate a hand or the game or simply wait for the next action in the hand.
// Check also if the card played is on player hand.
// \param int iPlayerIx : player index
// \param CARDINFO* pCardInfo : card information pointer
*/
BOOL  cInvidoCore::Player_playCard(int iPlayerIx, const CARDINFO* pCardInfo)
{
    CardSpec* pCardplayed = checkValidCardPlayed(iPlayerIx, pCardInfo);
    if (pCardplayed == NULL)
    {
        return FALSE;
    }

    BOOL bRes = FALSE;
	// change mano state
	if (m_Mano.Player_Play(iPlayerIx, FALSE))
	{
		// next player is on game
		m_pPlHaveToPlay = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::SWITCH_TO_NEXT);

		// update match points
		m_MatchPoints.PlayerPlay(iPlayerIx, pCardplayed->GetCardInfo());

		for (int i = 0; i < m_lNumPlayers; i++)
		{
			// notify all players that a card was played
			if (m_vctAlgPlayer[i])
			{
				m_vctAlgPlayer[i]->ALG_PlayerHasPlayed(iPlayerIx, pCardplayed->GetCardInfo());
			}
		}

		// reset info about played card
		resetCard(iPlayerIx, pCardplayed->GetCardInfo());

		bRes = TRUE;
	}
	return bRes;
}


////////////////////////////////////////
//       Player_saySomething
/*! A  player has said something
// \param int iPlayerIx : player index
*/
BOOL  cInvidoCore::Player_saySomething(int iPlayerIx, eSayPlayer eSay)
{
	BOOL bRes = FALSE;
	if (m_Mano.Player_Say(iPlayerIx, eSay))
	{
		//  what he said is acceptable on the game
		for (int i = 0; i < m_lNumPlayers; i++)
		{
			// notify all players that a card was played
			if (m_vctAlgPlayer[i])
			{
				m_vctAlgPlayer[i]->ALG_PlayerHasSaid(iPlayerIx, eSay);
			}

		}
		bRes = TRUE;
	}

	return bRes;
}

////////////////////////////////////////
//       GetAdmittedCommands
/*! Provides a list of admitted commands
// \param VCT_COMMANDS& vct_Commands : result list
// \param int iPlayerIndex : player index
*/
void  cInvidoCore::GetAdmittedCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex)
{
	m_Mano.GetAdmittedCommands(vct_Commands, iPlayerIndex);
}

// GetMoreCommands
void   cInvidoCore::GetMoreCommands(VCT_COMMANDS& vct_Commands, int iPlayerIndex)
{
    m_Mano.GetMoreCommands(vct_Commands, iPlayerIndex);
}

////////////////////////////////////////
//       NotifyScript
/*Notify event to the script engine
// \param eScriptNotification eVal :
*/
void  cInvidoCore::NotifyScript(eScriptNotification eVal)
{
	TRACE("Event %d\n", eVal);
}


////////////////////////////////////////
//       NotifyScriptAlgorithm
/*! Notify the algorithm
// \param int iPlayerIx : player index that make  the notification
// \param eScriptNotification eVal :
*/
void  cInvidoCore::NotifyScriptAlgorithm(int iPlayerIx, eScriptNotification eVal)
{
	TRACE("Algorithm %d, %d\n", iPlayerIx, eVal);
}

////////////////////////////////////////// functions called by Script

////////////////////////////////////////
//       Script_OverrideDeck
/*! Script override the current deck
// \param int iPlayer : player index
// \param int iC1 : card 1
// \param int iC2 : card 2
// \param int iC3 : card 3
*/
void  cInvidoCore::Script_OverrideDeck(int iPlayer, int iC1, int iC2, int iC3)
{
	cPlayer* pCurrPlayer = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::NO_SWITCH);
	// the player that have to play is the player that becomes the first 3 card
	int iRefPlayerIndex = pCurrPlayer->GetIndex();
	int iBegPos = 0;
	if (iRefPlayerIndex != iPlayer)
	{
		int iDist = m_PlayersOnTable.CalcDistance(iRefPlayerIndex, iPlayer);
		iBegPos = NUM_CARDS_HAND * iDist;
	}

	m_pMyMazzo->SetIndexRaw(iBegPos, iC1);
	m_pMyMazzo->SetIndexRaw(iBegPos + 1, iC2);
	m_pMyMazzo->SetIndexRaw(iBegPos + 2, iC3);

}

////////////////////////////////////////
//       Script_SetStartPlayer
/*!
// \param int iPlayer :
*/
void cInvidoCore::Script_SetStartPlayer(int iPlayer)
{

}

////////////////////////////////////////
//       Script_Say
/*! Script say
// \param int iPlayer : player say
// \param eSayPlayer eSay : say detail
*/
void  cInvidoCore::Script_Say(int iPlayer, eSayPlayer eSay)
{
	Player_saySomething(iPlayer, eSay);
}


////////////////////////////////////////
//       Script_Play
/*! Script engine has played a card
// \param int iPlayer :
// \param CardSpec& CardPlayed :
*/
void  cInvidoCore::Script_Play(int iPlayer, CardSpec& CardPlayed)
{
	Player_playCard(iPlayer, CardPlayed.GetCardInfo());
}


////////////////////////////////////////
//       Script_MatchEnd
/*! Terminate the match
*/
void  cInvidoCore::Script_MatchEnd()
{
	// reset state machines
	m_Partita.Reset();
	m_Giocata.Reset();
	m_Mano.Reset();
}


////////////////////////////////////////
//       Script_CheckResult
/*!
// \param int iTypeOfItem :
// \param int iParam1 :
// \param int iExpectedVal :
*/
int cInvidoCore::Script_CheckResult(int iTypeOfItem, int iParam1, int iExpectedVal)
{
	int iRes = 0;

	return iRes;
}


