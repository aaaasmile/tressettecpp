
//cCoreEngine.cpp
#include "StdAfx.h"
#include "cCoreEngine.h"
#include "cMazzo.h"
#include "lang_gen.h"
#include "AlgSupport.h"
#include "TraceService.h"


////////////////////////////////////////////////////////////////
// **********************   cCore CLASS *****************
////////////////////////////////////////////////////////////////


// Constructor
cCore::cCore()
{
    m_lNumPlayers = 0;
    m_pPlHaveToPlay = 0;
    m_pStartPlayer = 0;
    m_pMyMazzo = 0;
    resetCardInfoPlayers();
    m_eLocalType = LT_NEUTRO;
    m_bSuspendShuffle = FALSE;
    m_bGooGameAreEnabled = TRUE;
    m_iFirstPlayerPython = NOT_VALID_INDEX;
    m_pTracer = 0;
}



////////////////////////////////////////
//       ~cCore
/*! Destructor
*/
cCore::~cCore()
{
    delete m_pMyMazzo;
}


////////////////////////////////////////
//       Create
/*! Create the core game. Function called before the  match begin.
// \param cPlayer* pHmiPlayer : player created in hmi
// \param int iNumPlayers : number of players
*/
void cCore::Create( int iNumPlayers)
{
    m_pTracer = TraceService::Instance();

    //TRACE("cCore is created\n");
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 1, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry("cCore is created"); 

                            //deck
    m_pMyMazzo = new cMazzo();
    m_pMyMazzo->SetCoreEngine(this); 
    m_pMyMazzo->Create(); 

    m_PlayersOnTable.Create(iNumPlayers);

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

    

    // say strings
    m_Map_fb_Say[NOTHING]                        = "NOTHING";
    m_Map_fb_Say[VOLO]                           = "VOLO";
    m_Map_fb_Say[BUSSO_LAMIGLIORE]               = "BUSSO_LAMIGLIORE";
    m_Map_fb_Say[STRISCIO_NEHOTANTE]             = "STRISCIO_NEHOTANTE";
    m_Map_fb_Say[PUNTO_ANCORAUNA]                = "PUNTO_ANCORAUNA";
    m_Map_fb_Say[VIA_DAQUESTOGIOCO]              = "VIA_DAQUESTOGIOCO";
    m_Map_fb_Say[HO_ILTRE]                       = "HO_ILTRE";
    m_Map_fb_Say[HO_ILDUE]                       = "HO_ILDUE";
    m_Map_fb_Say[HO_ASSO]                        = "HO_ASSO";
    m_Map_fb_Say[LISCIO_NEHOANCORAPIUBASSE]      = "LISCIO_NEHOANCORAPIUBASSE";
    
}


////////////////////////////////////////
//       WhoWonsTheGame
/*! Provides the player index who wons the game. If the game is drawn pbIsDrawn is set to TRUE.
// \param long* plPlayerIx : return winner index
// \param BOOL* pbIsDrawn : return TRUE if the game has no winner, otherwise FALSE
*/
BOOL  cCore::WhoWonsTheGame(cPlayer** ppPlayer)
{
    ASSERT(ppPlayer);
    ASSERT(0);

    return TRUE;
}


////////////////////////////////////////
//       NewMatch
/*! Start a new match 
*/
void  cCore::NewMatch()
{
    // extract the first player
    int iFirstPlayer = 0;
    
    if (m_iFirstPlayerPython != NOT_VALID_INDEX)
    {
        // python is ongoing
        iFirstPlayer = m_iFirstPlayerPython;
    }
    else
    {
        iFirstPlayer = CASO(m_lNumPlayers);
    }
    
    if (m_eGameType == NET_CLIENT_TYPE)
    {
        // TO DO:
        // make sure that we are connected and the opponent has started the game
        BOOL bCanStartNetGame = FALSE;
        if (! bCanStartNetGame )
        {
            // could'n start the match
            return;
        }
        else
        {
            // ok we can start a new match
            // TO DO:
            // retrives the first player 
        }
    }

    // save players alg in a table
    // don't change level during a match
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        cPlayer* pPlayer = m_PlayersOnTable.GetPlayerIndex(i); 
        m_vctAlgPlayer[i] = pPlayer->GetAlg();
        if (m_vctAlgPlayer[i])
        {
            // information before match begin
            m_vctAlgPlayer[i]->ALG_SetPlayerIndex(pPlayer->GetIndex() );
            m_vctAlgPlayer[i]->ALG_SetCoreInterface(this);
            m_vctAlgPlayer[i]->ALG_NewMatch(m_lNumPlayers);
            if (i == 0)
            {
                // player index 0
                if (m_lNumPlayers == 2)
                {
                    //  2 player
                    m_vctAlgPlayer[i]->ALG_SetOpponentIndex(1, 0); 
                }
                else if (m_lNumPlayers == 4)
                {
                    //  4 players
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
                // player index 1
                if (m_lNumPlayers == 2)
                {
                    //  2 player
                    m_vctAlgPlayer[i]->ALG_SetOpponentIndex(0, 0); 
                }
                else
                {
                    //  4 players
                    m_vctAlgPlayer[i]->ALG_SetOpponentIndex(0, 0);
                    m_vctAlgPlayer[i]->ALG_SetOpponentIndex(2, 1); 
                }
            }
            else if (i == 2)
            {
                // player index 2
                m_vctAlgPlayer[i]->ALG_SetOpponentIndex(1, 0);
                m_vctAlgPlayer[i]->ALG_SetOpponentIndex(3, 1); 
            }
            else if (i == 3)
            {
                // player index 3
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
    m_PlayersOnTable.SetFirst(iFirstPlayer);
    m_pStartPlayer = m_PlayersOnTable.GetPlayerIndex(iFirstPlayer) ;
    m_Partita.NewPartita(iFirstPlayer);
    m_MatchPoints.MatchStart(m_lNumPlayers);
}




////////////////////////////////////////
//       GetPlayerInPlaying
/*! Return the index of the player that must play
// \param long * plPlayerIx : 
*/
BOOL  cCore::GetPlayerInPlaying(cPlayer** ppPlayer)
{
    ASSERT(ppPlayer);
 
    *ppPlayer = m_pPlHaveToPlay;
    
    return TRUE;
}

////////////////////////////////////////
//       NextAction
/*! Trigger the next state
*/
void  cCore::NextAction()
{
    m_Mano.NextAction();
    m_Giocata.NextAction();
    m_Partita.NextAction(); 
}



////////////////////////////////////////
//       isCardInPlayerHand
/*! return true if the card is on player hand, false otherwise
*/
BOOL cCore::isCardInPlayerHand(int iPlayerIx, CARDINFO* pCardInfo)
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
            break;
        }
    }

    return bRet;
}


////////////////////////////////////////
//       isDeclarationInPlayerHand
/*! return true if the declaration is compatible with the player hand
// \param int iPlayerIx : 
// \param eDeclGoodGame eValgg : 
// \param eSUIT eValsuit : 
*/
BOOL cCore::isDeclarationInPlayerHand(int iPlayerIx, eDeclGoodGame eValgg,  eSEED eValsuit)
{
    VCT_GOODGAMEDETAIL vct_GGRec;
    VCT_CARDINFO vctMyCards;
    for (int j = 0; j < NUM_CARDS_HAND; j++)
    {
        int iPlayerPosIx = iPlayerIx * NUM_CARDS_HAND + j;
        vctMyCards.push_back( *(m_aCardInfo[iPlayerPosIx].GetCardInfo()) );
    }

    // retrives all available good games
    AlgSupport::GetAvailbDeclGoodGames(vctMyCards, vct_GGRec);

    return TRUE;
}


////////////////////////////////////////
//       resetCardInfoPlayers
/*! Reset information on card about all players. 
*/
void cCore::resetCardInfoPlayers()
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
BOOL  cCore::resetCard(int iPlayerIx, CARDINFO* pCardInfo)
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
    ASSERT(bRet);

    return bRet;
}

////////////////////////////////////////
//       Giocata_Start
/*! Shuffle the cards and distribuite the cards
// \param long lPlayerIx : player index that must play
*/
void cCore::Giocata_Start(long lPlayerIx)
{
    //TRACE("Nuova giocata\n");
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 2, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry("Nuova giocata"); 

                            // reset card info of all players
    resetCardInfoPlayers();

    if (!m_bSuspendShuffle)
    {
                            // shuffle cards
        m_pMyMazzo->Shuffle();
    }
    m_pMyMazzo->DeckRewind();
    
                            // distribuite the cards
    CardSpec tmpCard; 
    m_PlayersOnTable.SetFirst(lPlayerIx);

    // 1) first - calculate the table (there is no switch)
    // player that have to play first, is the first that get the cards after shuffle
    int aPlayerDeck[MAX_NUM_PLAYER];
    m_PlayersOnTable.CalcCircleIndex(aPlayerDeck);

    // 2) second - retreive the player that have to play and switch the table
    m_pPlHaveToPlay  = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::SWITCH_TO_NEXT);
   
    // 3) distribuite cards
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        int iIxCurrPLayer = aPlayerDeck[i];
        ASSERT(iIxCurrPLayer >= 0 && iIxCurrPLayer < m_lNumPlayers);
        
        cPlayer* pCurrPlayer = m_PlayersOnTable.GetPlayerIndex(iIxCurrPLayer);
        CARDINFO CardArray[NUM_CARDS_HAND];
        
        //TRACE( "%s => ", pCurrPlayer->GetName() );
        if ( m_pTracer->AddNewEntry(TR_CORE_CH, 3, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
            m_pTracer->AddCommentToLastEntry("%s => Index %d ", pCurrPlayer->GetName(), iIxCurrPLayer ); 

        for (int j = 0; j < NUM_CARDS_HAND; j++)
        {
                            // distribuite all cards on player
            m_pMyMazzo->PickNextCard(&tmpCard);
            
            tmpCard.FillInfo(&CardArray[j]);
            //TRACE("[%s] ", tmpCard.GetName()   );
            if ( m_pTracer->AddNewEntry(TR_CORE_CH, 4, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
                m_pTracer->AddCommentToLastEntry("[%s] ", tmpCard.GetName()); 
            
            // store card information for controlling
            int iTmpCdIndex = iIxCurrPLayer * NUM_CARDS_HAND + j;
            m_aCardInfo[iTmpCdIndex] = tmpCard; 
        }
        //TRACE("\n");
        if (m_vctAlgPlayer[iIxCurrPLayer])
        {
            m_vctAlgPlayer[iIxCurrPLayer]->ALG_NewGiocata(CardArray, NUM_CARDS_HAND,lPlayerIx);
        }
    }
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 14, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry("Player start: %d", lPlayerIx);

    m_MatchPoints.GiocataStart();
    // notify mano
    m_Mano.GiocataStart();  
    
}



////////////////////////////////////////
//       Mano_End
/*! A mano is terminated.
*/
void cCore::Mano_End()
{
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 5, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry("Mano_End"); 

    m_MatchPoints.ManoEnd();
    int iPlayer =  m_MatchPoints.GetManoWinner();
    m_Giocata.Update_Giocata(iPlayer, &m_MatchPoints); 

    // update the table
    m_PlayersOnTable.SetFirst(iPlayer);
    m_pPlHaveToPlay  = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::SWITCH_TO_NEXT);

    for (int i = 0; i < m_lNumPlayers; i++)
    {
        if (m_vctAlgPlayer[i])
        {
            m_vctAlgPlayer[i]->ALG_ManoEnd(&m_MatchPoints); 
        }
    }
}


////////////////////////////////////////
//       Giocata_AMonte
/*! A giocata is going to "A monte"
*/
void cCore::Giocata_AMonte()
{
    m_MatchPoints.AMonte();
    m_Giocata.Update_Giocata(NOT_VALID_INDEX, &m_MatchPoints);    
}

////////////////////////////////////////
//       Player_VaVia
/*! The player abandon the giocata
// \param int iPlayerIx : Player index that abandon the giocata
*/
void cCore::Player_VaVia(int iPlayerIx)
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
void cCore::ChangeGiocataScore(eGiocataScoreState eNewScore)
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
void   cCore::Giocata_End()
{
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 6, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry("Giocata_End"); 

    // calculate points
    m_MatchPoints.GiocataEnd(); 
    // update match state machine, here is calculate the first player tha have to play.
    m_Partita.Update_Partita(&m_MatchPoints); 

    for (int i = 0; i < m_lNumPlayers; i++)
    {
        if (m_vctAlgPlayer[i])
        {
            m_vctAlgPlayer[i]->ALG_GiocataEnd(&m_MatchPoints); 
        }
    }
}


////////////////////////////////////////
//       Partita_End
/*! Match is terminated. Iform all algorithms
*/
void  cCore::Partita_End()
{
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 8, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry("Partita_End"); 

    for (int i = 0; i < m_lNumPlayers; i++)
    {
        if (m_vctAlgPlayer[i])
        {
            m_vctAlgPlayer[i]->ALG_MatchEnd(&m_MatchPoints); 
        }
    }
}


////////////////////////////////////////
//       AbandonGame
/*! The player abandon the game, the game is teminated
// \param int iPlayerIx : player index that abandon the game
*/
void cCore::AbandonGame(int iPlayerIx)
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
void   cCore::NtyWaitingPlayer_Toplay(int iPlayerIx)
{
    ASSERT(m_pPlHaveToPlay);
    ASSERT(iPlayerIx == m_pPlHaveToPlay->GetIndex() );
    
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
void   cCore::NtyWaitingPlayer_ToResp(int iPlayerIx)
{
    I_ALG_Player* pAlg = m_vctAlgPlayer[iPlayerIx]; 
    ASSERT(pAlg);

    // algorithm have to play
    pAlg->ALG_Say(); 
}

////////////////////////////////////////
//       NtyPlayerSayBuiada
/*! The player say something not corerct
// \param int iPlayerIx : player index
*/
void  cCore::NtyPlayerSayBuiada(int iPlayerIx)
{
    for (int i = 0; i < m_lNumPlayers; i++)
    {
        // notify all players that a player says something not correct
        if (m_vctAlgPlayer[i])
        {       
            m_vctAlgPlayer[i]->ALG_PLayerSaidFalse(iPlayerIx); 
        }       
    
    }
}


////////////////////////////////////////
//       RaiseError
/*! To make error handling message system gui indipendent.
// \param const std::string &errorMsg : 
*/
void cCore::RaiseError( const std::string &errorMsg)
{
    ASSERT(0);
    //TRACE(const_cast<char *>( errorMsg.c_str() ));
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 9, EntryTraceDetail::TR_ERR, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry(const_cast<char *>( errorMsg.c_str() )); 
}


////////////////////////////////////////
//       Player_playCard
/*! A player has played a card, terminate the trick or the game or simply wait for the next action in the trick.
// Check also if the card played is on player hand.
// \param int iPlayerIx : player index
// \param CARDINFO* pCardPl : card information pointer
*/
BOOL  cCore::Player_playCard(int iPlayerIx, CARDINFO* pCardPl)
{
    BOOL bRes = FALSE;
    ASSERT(pCardPl->eSeed != UNDEF );

    CARDINFO cardPlayed = *pCardPl;

    if ( !isCardInPlayerHand(iPlayerIx, &cardPlayed) )
    {
        // this is a programming error. Don't admit hmi to play cards that not are in hand
        if ( m_pTracer->AddNewEntry(TR_CORE_CH, 10, EntryTraceDetail::TR_ERR, __FILE__, __LINE__) )
            m_pTracer->AddCommentToLastEntry("this is a programming error. Don't admit hmi to play cards that not are in hand"); 
        ASSERT(0);
        return FALSE;
    }

    // check if the card reject the first suit played
    BOOL bIsSuitCompatible = m_MatchPoints.CheckRejecting(iPlayerIx,&cardPlayed);
    if (!bIsSuitCompatible)
    {
        // not the same suit of the first played card in the current trick
        // check if the player have really no other cards of the initial suit
        CardSpec cardTmp;
        m_MatchPoints.GetCardPlayedOnTrick(0, &cardTmp);
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            int iPlayerPosIx = iPlayerIx * NUM_CARDS_HAND + i;
            if (m_aCardInfo[iPlayerPosIx].GetSeed() == cardTmp.GetSeed() )
            {
                // uppss the player can't reject the suit, he has an admitted card.
                // play not admitted
                return FALSE;
            }
        }
        bIsSuitCompatible = TRUE;
    }

    // change mano state
    if ( bIsSuitCompatible && m_Mano.Player_Play(iPlayerIx) )
    {
        // ok card is played
        if ( m_pTracer->AddNewEntry(TR_CORE_CH, 11, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
            m_pTracer->AddCommentToLastEntry("Player %d, card played [%s]",iPlayerIx, cardPlayed.CardName ); 
        
        // next player is on game
        m_pPlHaveToPlay = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::SWITCH_TO_NEXT);  

        // update match points
        m_MatchPoints.PlayerPlay(iPlayerIx,&cardPlayed); 

        for (int i = 0; i < m_lNumPlayers; i++)
        {
            // notify all players that a card was played
            if (m_vctAlgPlayer[i])
            {       
                m_vctAlgPlayer[i]->ALG_PlayerHasPlayed(iPlayerIx, &cardPlayed); 
            }       
        
        }

        // reset info about played card
        resetCard(iPlayerIx, &cardPlayed);

        bRes = TRUE;
    }
    return bRes;
}


////////////////////////////////////////
//       Player_saySomething
/*! A  player has said something
// \param int iPlayerIx : player index
*/
BOOL  cCore::Player_saySomething(int iPlayerIx, eSayPlayer eSay )
{
    BOOL bRes = FALSE;
    int iManoNum = m_MatchPoints.GetManoNum();
    if (iManoNum >= NUM_CARDS_HAND - 1)
    {
        // don't need signal at the end
        return bRes;
    }
    if (m_Mano.Player_Say(iPlayerIx, eSay))
    {
        //  what he said is acceptable on the game
        if ( m_pTracer->AddNewEntry(TR_CORE_CH, 12, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        {
            STRING lpsNameSay = m_Map_fb_Say[eSay];
            m_pTracer->AddCommentToLastEntry("Player %d, has said %s", iPlayerIx, lpsNameSay.c_str() ); 
        }

        for (int i = 0; i < m_lNumPlayers; i++)
        {
            // notify all players that a card was played
            if (m_vctAlgPlayer[i])
            {       
                m_vctAlgPlayer[i]->ALG_PlayerHasSaid(iPlayerIx, eSay) ; 
            }       
    
        }
        bRes = TRUE;
    }

    return bRes;
}


////////////////////////////////////////
//       NoInitScript
/*! Start a match without a script 
*/
void  cCore::NoInitScript()
{
    m_iFirstPlayerPython = NOT_VALID_INDEX;
    m_bSuspendShuffle = FALSE;
}

////////////////////////////////////////// functions called by Script


////////////////////////////////////////
//       Script_CheckDeck
/*! Script check deck consistency 
*/
void cCore::Script_CheckDeck()
{
    m_pMyMazzo->CheckDeck();
}


////////////////////////////////////////
//       Script_SetStartPlayer
/*! 
// \param int iPlayer : 
*/
void cCore::Script_SetStartPlayer(int iPlayer)
{
    m_iFirstPlayerPython = iPlayer;
    
}

////////////////////////////////////////
//       Script_OverrideDeck
/*! Script override the current deck
// \param int iPlayer : player index
// \param int vctCardPlayer : vector of card index
*/
void  cCore::Script_OverrideDeck(int iPlayer, int vctCardPlayer[])
{
    cPlayer* pCurrPlayer = m_PlayersOnTable.GetPlayerToPlay(cPlayersOnTable::NO_SWITCH);
    // the player that have to play is the player that becomes the first 10 card
    int iRefPlayerIndex = pCurrPlayer->GetIndex();
    int iBegPos = 0;
    if (iRefPlayerIndex != iPlayer)
    {
        int iDist = m_PlayersOnTable.CalcDistance(iRefPlayerIndex, iPlayer);
        iBegPos = NUM_CARDS_HAND * iDist;
    }

    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_pMyMazzo->SetIndexRaw(iBegPos+i, vctCardPlayer[i]);
    }
    m_bSuspendShuffle = TRUE;
}

////////////////////////////////////////
//       Script_Say
/*! Script say
// \param int iPlayer : player say
// \param eSayPlayer eSay : say detail
*/
void  cCore::Script_Say(int iPlayer, eSayPlayer eSay)
{
    Player_saySomething(iPlayer,  eSay );
}


////////////////////////////////////////
//       Script_Play
/*! Script engine has played a card
// \param int iPlayer : 
// \param CardSpec& CardPlayed : 
*/
void  cCore::Script_Play(int iPlayer, CardSpec& CardPlayed)
{
    Player_playCard(iPlayer,  CardPlayed.GetCardInfo()  );
}

////////////////////////////////////////// END functions called by Script

////////////////////////////////////////
//       DeclareGoodGame
/*! A player declare good game
// \param eDeclGoodGame eValgg : 
// \param eSUIT eValsuit : 
*/
BOOL cCore::DeclareGoodGame(int iPlayerIx, eDeclGoodGame eValgg,  eSEED eValsuit)
{
    if (!m_bGooGameAreEnabled)
    {
        return FALSE;
    }
    int iCurrTrick = m_MatchPoints.GetManoNum(); 
    if (iCurrTrick == 0)
    {
        if ( !isDeclarationInPlayerHand(iPlayerIx, eValgg, eValsuit) )
        {
            // this is a programming error. Don't admit erroneus declarations.
            ASSERT(0);
            return FALSE;
        }

        // update match points
        m_MatchPoints.DeclareGoodGame(iPlayerIx, eValgg, eValsuit); 
        if ( m_pTracer->AddNewEntry(TR_CORE_CH, 14, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        {
            m_pTracer->AddCommentToLastEntry("Player %d, good game %d, suite %d", iPlayerIx, eValgg, eValsuit ); 
        }

        for (int i = 0; i < m_lNumPlayers; i++)
        {
            // notify all players that a declaration was done
            if (m_vctAlgPlayer[i])
            {       
                m_vctAlgPlayer[i]->ALG_PLayerDeclareGoodGame(iPlayerIx, eValgg, eValsuit); 
            }       
    
        }
    }

    return TRUE;
}

////////////////////////////////////////
//       GetAdmittedSignals
/*! Provides a list of admitted commands
// \param VCT_SIGNALS& vct_Signals : result list
// \param int iPlayerIndex : player index
*/
void  cCore::GetAdmittedSignals(CardSpec&   cardClicked, VCT_SIGNALS& vct_Signals, int iPlayerIndex)
{
    SayDetail sdTmp;
    cLanguages* pLan = cLanguages::Instance();

    if (m_eLocalType == LT_BREDA)
    {
        // all defaults commands are always available
        vct_Signals = m_vctSignAvail;
    }
    else 
    {
        vct_Signals.clear();

        BOOL bBusso = FALSE;
        BOOL bVolo = FALSE;
        BOOL bLiscio = FALSE;

        // check if busso is available
        checkForBussoVoloLiscieBasse(bBusso, bVolo, bLiscio, iPlayerIndex, cardClicked);
        if (bVolo)
        {
            if (m_eLocalType == LT_CHITARELLA)
            {
                sdTmp.eSay = PIOMBO;
                strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_PIOMBO));
                vct_Signals.push_back(sdTmp);
            }
            else
            {
                sdTmp.eSay = VOLO;
                strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_VOLO));
                vct_Signals.push_back(sdTmp);
            }

        }
        
        if (bBusso)
        {
            if (m_eLocalType == LT_CHITARELLA && bVolo)
            {
                // we don't need volo and busso, volo is enought
            }
            else
            {
                sdTmp.eSay = BUSSO_LAMIGLIORE;
                strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_BUSSO_LAMIGLIORE));
                vct_Signals.push_back(sdTmp);
            }
        }
        
        if (bLiscio)
        {
            if (m_eLocalType == LT_CHITARELLA)
            {
                // uses striscio instead of liscio
                sdTmp.eSay = LISCIO_NEHOANCORAPIUBASSE;
                strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_STRISCIO_COMELISCIO));
                vct_Signals.push_back(sdTmp);
            }
            else
            {
                sdTmp.eSay = LISCIO_NEHOANCORAPIUBASSE;
                strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_LISCIO_NEHOANCORAPIUBASSE));
                vct_Signals.push_back(sdTmp);
            }
        }

        if (m_eLocalType == LT_CHITARELLA)
        {
            // check for some more signals
            if ( checkForStriscioNeHoTante(iPlayerIndex, cardClicked) )
            {
                sdTmp.eSay = STRISCIO_NEHOTANTE;
                strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_STRISCIO_NEHOTANTE));
                vct_Signals.push_back(sdTmp);
            }

        }

        if (vct_Signals.size() > 0)
        {
            sdTmp.eSay = NOTHING;
            strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_NOTHING));
            vct_Signals.push_back(sdTmp);
        }
    }
}



////////////////////////////////////////
//       checkForBussoVoloLiscieBasse
/*! Check if volo, busso and liscio are available
// \param BOOL& bVolo : result
// \param int iPlayerIndex : player index
// \param cardClicked : card to play
*/
void cCore::checkForBussoVoloLiscieBasse(BOOL& bBusso, BOOL& bVolo, BOOL& bLiscio, 
                                       int iPlayerIndex, CardSpec&   cardClicked)
{
    bVolo = FALSE;
    bLiscio = FALSE;
    int iNumCardPlayed = m_MatchPoints.GetCurrNumCardPlayed() ;
    if (iNumCardPlayed == 0)
    {
        // only the player has played, command available
        bBusso = TRUE;
        int iCardOnSuitCount = 0;
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            int iPlayerPosIx = iPlayerIndex * NUM_CARDS_HAND + i;
            if (m_aCardInfo[iPlayerPosIx].GetSeed() == cardClicked.GetSeed() )
            {
                iCardOnSuitCount ++;
                if (cardClicked > m_aCardInfo[iPlayerPosIx] && 
                    m_aCardInfo[iPlayerPosIx].IsLiscio() )
                {
                    // there is other liscie
                    bLiscio = TRUE;
                }
            }
        }
        if (iCardOnSuitCount == 1)
        {
            bVolo = TRUE;
        }
    }
    else if (iNumCardPlayed > 0)
    {
        CardSpec cardTmp;
        m_MatchPoints.GetCardPlayedOnTrick(0, &cardTmp);
        // check if the card is not a reject
        if (cardClicked.GetSeed() !=  cardTmp.GetSeed() )
        {
            // card is a reject,
            // signal not available
            return;
        }
        // not a reject

        // count suits
        int iCardOnSuitCount = 0;
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            int iPlayerPosIx = iPlayerIndex * NUM_CARDS_HAND + i;
            if (m_aCardInfo[iPlayerPosIx].GetSeed() == cardTmp.GetSeed() )
            {
                iCardOnSuitCount ++;
                if (cardClicked > m_aCardInfo[iPlayerPosIx] && 
                    m_aCardInfo[iPlayerPosIx].IsLiscio() )
                {
                    // there is other liscie
                    bLiscio = TRUE;
                }
            }
        }
        if (iCardOnSuitCount == 1)
        {
            // this is a volo
            bVolo = TRUE;
        }
        
    }
    
}


////////////////////////////////////////
//       checkForStriscioNeHoTante
/*! Check if the player can say striscio ne ho tante
// \param int iPlayerIndex : player that have to play
// \param CardSpec&   cardClicked : card clicked
*/
BOOL cCore::checkForStriscioNeHoTante(int iPlayerIndex, CardSpec&   cardClicked)
{
    BOOL bRet = FALSE;
    int iNumCardPlayed = m_MatchPoints.GetCurrNumCardPlayed() ;
    if (iNumCardPlayed == 0)
    {
        // this is possible only for the first player in the trick
        int iCardOnSuitCount = 0;
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            int iPlayerPosIx = iPlayerIndex * NUM_CARDS_HAND + i;
            if (m_aCardInfo[iPlayerPosIx].GetSeed() == cardClicked.GetSeed() )
            {
                iCardOnSuitCount ++;
            }
        }
        if (iCardOnSuitCount >= 3)
        {
            bRet = TRUE;
        }
    }

    return bRet;
}


////////////////////////////////////////
//       GetComandString
/*! Provides a text based on signal
// \param eSayPlayer eSay : signal
*/
STRING  cCore::GetComandString(eSayPlayer eSay)
{
    STRING strRet;
    for (UINT i = 0; i < m_vctSignAvail.size(); i++)
    {
        if (m_vctSignAvail[i].eSay == eSay)
        {
            strRet = m_vctSignAvail[i].lpcText;
            break;
        }
    }
    return strRet;
}

////////////////////////////////////////
//       SetLocalType
/*! Set the local game type. It is important to define all signals admitted for a local game
// also if they are not used at thesame time.
// \param eTypeLocal eLocal : local type
*/
void  cCore::SetLocalType(eTypeLocal eLocal)
{
    m_eLocalType = eLocal;
    m_vctSignAvail.clear();
    SayDetail sdTmp;
    cLanguages* pLan = cLanguages::Instance();

    if (eLocal == LT_BREDA)
    {
        // this local is the game played a Breda
        sdTmp.eSay = BUSSO_LAMIGLIORE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_BUSSO_LAMIGLIORE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = VOLO;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_VOLO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = STRISCIO_NEHOTANTE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_STRISCIO_NEHOTANTE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = PUNTO_ANCORAUNA;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_PUNTO_ANCORAUNA));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = VIA_DAQUESTOGIOCO;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_VIA_DAQUESTOGIOCO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = HO_ILTRE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_HO_ILTRE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = HO_ILDUE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_HO_ILDUE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = HO_ASSO;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_HO_ASSO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = NOTHING;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_NOTHING));
        m_vctSignAvail.push_back(sdTmp);
    }
    else if (eLocal == LT_NEUTRO)
    {
        // neutral local
        sdTmp.eSay = BUSSO_LAMIGLIORE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_BUSSO_LAMIGLIORE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = VOLO;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_VOLO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = LISCIO_NEHOANCORAPIUBASSE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_LISCIO_NEHOANCORAPIUBASSE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = NOTHING;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_NOTHING));
        m_vctSignAvail.push_back(sdTmp);
    }
    else if (eLocal == LT_CHITARELLA)
    {
        // chitarella local
        sdTmp.eSay = BUSSO_LAMIGLIORE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_BUSSO_LAMIGLIORE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = PIOMBO;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_PIOMBO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = LISCIO_NEHOANCORAPIUBASSE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_LISCIO_NEHOANCORAPIUBASSE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = STRISCIO_NEHOTANTE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_STRISCIO_NEHOTANTE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = NOTHING;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_NOTHING));
        m_vctSignAvail.push_back(sdTmp);

    }
    else if (eLocal == LT_ROMANA)
    {
        // romana local described by Domenico  Starna
        sdTmp.eSay = LAMIGLIORE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_LAMIGLIORE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = VOLO;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_VOLO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = BUSSO_ILTRE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_BUSSO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = RIBUSSO_ILDUE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_RIBUSSO));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = VOGLIO_ILVENTICINQUE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_VOGLIOIL25));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = HO_ILVENTICINQUE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_HOIL25));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = ALTRE_CARTE;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_ALTRECARTE));
        m_vctSignAvail.push_back(sdTmp);

        sdTmp.eSay = PIOMBO_A_UNPALO;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_PIOMBOAUNPALO));
        m_vctSignAvail.push_back(sdTmp);

       
        sdTmp.eSay = NOTHING;
        strcpy(sdTmp.lpcText, pLan->GetCStringId(cLanguages::ID_C_NOTHING));
        m_vctSignAvail.push_back(sdTmp);

    }
    else
    {
        ASSERT(0);
    }
}



////////////////////////////////////////
//       SetRandomSeed
/*! Initialize the random seed
// \param int iVal : 
*/
void  cCore::SetRandomSeed(int iVal)
{
    m_pMyMazzo->SetRandomSeed(iVal);
    if ( m_pTracer->AddNewEntry(TR_CORE_CH, 12, EntryTraceDetail::TR_INFO, __FILE__, __LINE__) )
        m_pTracer->AddCommentToLastEntry("Seed random %d",iVal ); 
}

