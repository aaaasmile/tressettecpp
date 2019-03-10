
#include "StdAfx.h"
#include "win_type_global.h"
#include <map>
#include "cAlgAdvancedPlayer.h"
#include "cProbality.h"
#include "TraceService.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//random value between [0,x)
#define CASO(x) (x * rand()) / RAND_MAX

typedef std::map<eSayPlayer, LPCSTR> _MAP_SAY;
static _MAP_SAY  g_MapSay;


cAlgAdvancedPlayer::cAlgAdvancedPlayer()
{
    m_ixCurrMano = 0;
    m_pCoreGame = 0;
    m_iOppIndex = NOT_VALID_INDEX;
    m_pTracer = TraceService::Instance();
    m_itrChan = 3;
    m_pTracer->SetOutputChannel(m_itrChan, TraceService::OT_MSVDEBUGGER, "");
    m_pTracer->EnableChannel(m_itrChan, TRUE);
    // say strings
    g_MapSay[AMONTE] = "A monte";
    g_MapSay[INVIDO] = "Invido";
    g_MapSay[TRASMAS] = "Tras mas";
    g_MapSay[TRASMASNOEF] = "Tras mas noef";
    g_MapSay[FUERAJEUQ] = "Feura jeuq";
    g_MapSay[PARTIDA] = "Partida";
    g_MapSay[VABENE] = "Va bene";
    g_MapSay[VADOVIA] = "Vado via";
    g_MapSay[CHIAMADIPIU] = "Chiama di più";
    g_MapSay[NO] = "No";
    g_MapSay[VADODENTRO] = "Vado dentro";
    g_MapSay[GIOCA] = "Gioca";

}

cAlgAdvancedPlayer::~cAlgAdvancedPlayer()
{

}


////////////////////////////////////////
//       ALG_SetCoreInterface
/*!
// \param I_CORE_Game* pCore :
*/
void cAlgAdvancedPlayer::ALG_SetCoreInterface(I_CORE_Game* pCore)
{
    m_pCoreGame = pCore;
}


////////////////////////////////////////
//       ALG_SetPlayerIndex
/*! set player index
// \param int iIndex :
*/
void cAlgAdvancedPlayer::ALG_SetPlayerIndex(int iIndex)
{
    m_iMyIndex = iIndex;
}


////////////////////////////////////////
//       ALG_SetOpponentIndex
/*! set opponent index
// \param int iIndex :
// \param int iOpponentNr :
*/
void cAlgAdvancedPlayer::ALG_SetOpponentIndex(int iIndex, int iOpponentNr)
{
    m_iOppIndex = iIndex;
}


//! set associate index
void cAlgAdvancedPlayer::ALG_SetAssociateIndex(int iIndex)
{

}


////////////////////////////////////////
//       ALG_NewMatch
/*! new match notification
// \param int iNumPlayer :
*/
void cAlgAdvancedPlayer::ALG_NewMatch(int iNumPlayer)
{
    VCT_MAZZO vctMyDeck;
    for (int i = 0; i < NUM_CARDS; i++)
    {
        vctMyDeck.push_back(i);
    }
}


////////////////////////////////////////
//       ALG_NewGiocata
/*! new giocata notification
// \param CARDINFO* pCardArray :
// \param int iNumOfCards :
*/
void cAlgAdvancedPlayer::ALG_NewGiocata(const CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx)
{
    ASSERT(iNumOfCards == NUM_CARDS_HAND);
    CardSpec cardUndef;
    int i;
    m_iNumManiWon = 0;
    m_iNumChiamateMonte = 0;
    m_iNumChiamateInGiocata = 0;
    m_bIamCalledPoints = FALSE;
    m_opponetIsVadoDentro = FALSE;
    m_WonFirstHand = FALSE;
    m_ixCurrMano = 0;

    m_iPlayerOnTurn = iPlayerIx;

    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Giocata new:");
    for (i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_vct_Cards_CPU[i].SetCardInfo(pCardArray[i]);
        int points = g_PointsTable[m_vct_Cards_CPU[i].GetCardIndex()];
        m_arrIxPlayerWonHand[i] = -1;
        m_pTracer->AddSimpleTrace(m_itrChan, "%d , carta: %s ", i, pCardArray[i].CardName);
    }
    m_pTracer->AddSimpleTrace(m_itrChan, "\n");
    for (i = 0; i < NUM_HANDS; i++)
    {
        m_vct_Cards_played[i].clear();
    }

    m_MyLastSay = VABENE;
    m_sayMyRisp = VABENE;
    m_OpponentSay = VABENE;
    m_sayOppRisp = VABENE;
    m_bLastManoPatada = FALSE;

    if (m_pTracer)
    {
        CardSpec Card;
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Cards of player %d are: \n", m_iMyIndex);
        for (int i = 0; i < NUM_CARDS_HAND; i++)
        {
            Card.SetCardInfo(pCardArray[i]);
            m_pTracer->AddSimpleTrace(m_itrChan, "[%s] ", Card.GetName());
        }
        m_pTracer->AddSimpleTrace(m_itrChan, "\n");
    }
}

void cAlgAdvancedPlayer::ALG_PlayerHasVadoDentro(int iPlayerIx)
{
    TRACE("[TRALG]Player %1 va dentro\n", iPlayerIx);
    CardSpec cardDentro;
    if (iPlayerIx == m_iMyIndex)
    {
        // l'idea è quella di ritrovare la carta con la quale si è andati dentro e poi di chiamare ALG_PlayerHasPlayed
        ASSERT(m_iCPUCardDentroPos != NOT_VALID_INDEX);
        ASSERT(m_vct_Cards_CPU[m_iCPUCardDentroPos].GetCardIndex() != NOT_VALID_INDEX);
        cardDentro.SetCardIndex(m_vct_Cards_CPU[m_iCPUCardDentroPos].GetCardIndex());
        ALG_PlayerHasPlayed(iPlayerIx, cardDentro.GetCardInfo());
        m_iCPUCardDentroPos = NOT_VALID_INDEX;
    }
    else
    {
        m_opponetIsVadoDentro = TRUE;
        cardDentro.SetCardIndex(3);
        ALG_PlayerHasPlayed(iPlayerIx, cardDentro.GetCardInfo());
    }
}

void cAlgAdvancedPlayer::doVadoDentro(int cardPos)
{
    CardSpec cardUndef;
    m_iCPUCardDentroPos = cardPos;
    ASSERT(m_vct_Cards_CPU[cardPos] != cardUndef);
    m_pCoreGame->Player_vaDentro(m_iMyIndex, m_vct_Cards_CPU[cardPos].GetCardInfo());
}

////////////////////////////////////////
//       ALG_PlayerHasPlayed
/*! player has played a card
// \param int iPlayerIx :
// \param CARDINFO* pCard :
*/
void cAlgAdvancedPlayer::ALG_PlayerHasPlayed(int iPlayerIx, const CARDINFO* pCard)
{
    ASSERT(pCard);
    ASSERT(pCard->byIndex != NOT_VALID_INDEX);
    CardSpec cardUndef;
    int i;
    if (iPlayerIx == m_iMyIndex)
    {
        CardSpec Card;
        CardSpec CardUndef;
        Card.SetCardInfo(*pCard);
        BOOL bFound = FALSE;
        // card successfully played
        for (i = 0; !bFound && i < NUM_CARDS_HAND; i++)
        {
            if (Card == m_vct_Cards_CPU[i])
            {
                // card found
                m_vct_Cards_CPU[i] = CardUndef;
                bFound = TRUE;
            }
        }
        ASSERT(bFound);
    }
    else
    {
        // oponent play
        m_OpponentSay = VABENE;

    }
    ASSERT(pCard->byIndex != NOT_VALID_INDEX);
    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Player %d has played [%s]\n", iPlayerIx, pCard->CardName);

    CardSpec cardPlayed;
    cardPlayed.SetCardInfo(*pCard);
    m_vct_Cards_played[m_ixCurrMano].push_back(cardPlayed);

    m_iPlayerOnTurn = iPlayerIx == 0 ? 1 : 0;
    m_iNumChiamateMonte = 0;
    m_sayMyRisp = VABENE;

}

////////////////////////////////////////
//       ALG_PlayerHasSaid
/*! player has said something
// \param int iPlayerIx :
// \param eSayPlayer eSay :
*/
void cAlgAdvancedPlayer::ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay)
{
    LPCSTR lpsNameSay = g_MapSay[eSay];
    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Player %d has said %s\n", iPlayerIx, lpsNameSay);
    if (iPlayerIx == m_iOppIndex)
    {
        // Avversario ha parlato
        if (eSay > PARTIDA)
        {
            m_sayOppRisp = eSay; // Risposta alla chiamata
        }
        else
        {
            // avversario ha chiamato dei punti
            m_OpponentSay = eSay;
        }
    }
    else if (iPlayerIx == m_iMyIndex)
    {
        // Algoritmo ha parlato
        if (eSay > PARTIDA)
        {
            m_sayMyRisp = eSay; // Risposta alla chiamata
        }
        else
        {
            // chiamata a punti
            m_MyLastSay = eSay;
            m_bIamCalledPoints = TRUE;
        }

    }
}

BOOL cAlgAdvancedPlayer::Cagna(int  lastNumChiamate)
{
    VCT_COMMANDS vct_cmd;
    ASSERT(m_pCoreGame);
    BOOL res = FALSE;
    m_pCoreGame->GetAdmittedCommands(vct_cmd, m_iMyIndex);
    size_t iNumCmds = vct_cmd.size();
    if (iNumCmds > 0)
    {
        eSayPlayer eSay;

        int iTry = 0;
        do
        {
            size_t iRndIndex = CASO(iNumCmds);
            eSay = vct_cmd[iRndIndex];
            iTry++;
        } while (eSay == VADOVIA && iTry < 5);
        Chiama(eSay, lastNumChiamate);
        res = TRUE;
    }
    return res;
}

BOOL cAlgAdvancedPlayer::ChiamaAMonte(int lastNumChiamate)
{
    m_iNumChiamateMonte += 1;
    if (m_iNumChiamateMonte < 4)
    {
        Chiama(AMONTE, lastNumChiamate);
        return TRUE;
    }
    return FALSE;
}

void cAlgAdvancedPlayer::Chiama(eSayPlayer eSay, int lastChiamataNum)
{
    ASSERT(lastChiamataNum == m_iNumChiamateInGiocata);
    m_iNumChiamateInGiocata += 1;
    m_pCoreGame->Player_saySomething(m_iMyIndex, eSay);
}

BOOL cAlgAdvancedPlayer::ChiamaDiPiu(int  lastNumChiamate)
{
    VCT_COMMANDS vct_cmd;
    ASSERT(m_pCoreGame);

    m_pCoreGame->GetAdmittedCommands(vct_cmd, m_iMyIndex);
    for (UINT i = 0; i < vct_cmd.size(); i++)
    {
        eSayPlayer eSay = vct_cmd[i];
        if (eSay >= INVIDO && eSay <= PARTIDA)
        {
            Chiama(eSay, lastNumChiamate);
            return TRUE;
        }
    }
    return FALSE;
}

void cAlgAdvancedPlayer::PlayAsFirst()
{
    int lastNumChiamate = m_iNumChiamateInGiocata;
    CARDINFO* result = NULL;
    CardSpec cardUndef;
    int curr_mano = NumMano();
    if (CASO(40) >= 35 && !m_bIamCalledPoints)
    {
        if (Cagna(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R1cagna\n");
            return;
        }
    }

    int iLoops = 0, i, maxpoints = 0, max_pos = 0, sum_points = 0, min_pos = 0;
    int min_points = 20;
    int med_points = 0, med_pos = 0;
    int arrPoints[NUM_CARDS_HAND] = { 0,0,0 };
    for (i = 0; i < NUM_CARDS_HAND; i++)
    {
        if (m_vct_Cards_CPU[i] == cardUndef)
        {
            continue;
        }
        int points = m_vct_Cards_CPU[i].GetPoints();
        if (points > maxpoints)
        {
            med_points = maxpoints;
            med_pos = max_pos;
            maxpoints = points;
            max_pos = i;
        }
        else if (points >= med_points)
        {
            med_points = points;
            med_pos = i;
        }
        if (points < min_points)
        {
            min_pos = i;
            min_points = points;
        }
        arrPoints[i] = points;
        sum_points += points;
    }
    TRACE("[1ST]Take: min pos %d (pt %d), med pos %d (pt %d), max pos %d(pt %d) \n", min_pos,
        min_points, med_pos, med_points, max_pos, maxpoints);

    if (curr_mano == 2 && m_iNumManiWon == 1)
    {
        result = m_vct_Cards_CPU[min_pos].GetCardInfo();
        TRACE("Candidate from min position\n");
    }
    else
    {
        result = m_vct_Cards_CPU[max_pos].GetCardInfo();
    }
    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]candidate play PLF_pos: %s\n", result->CardName);

    if (curr_mano == 2 && m_iNumManiWon == 1)
    {
        int pointsCardMano1_pl1 = m_vct_Cards_played[0][0].GetPoints();
        int pointsCardMano1_pl2 = m_vct_Cards_played[0][1].GetPoints();
        int maxPointsMano1 = pointsCardMano1_pl1 > pointsCardMano1_pl2 ? pointsCardMano1_pl1 : pointsCardMano1_pl2;

        // seconda mano prima mano vinta
        TRACE("[TRALG]Vado dentro? maxpoints is %d\n", maxpoints);
        if (maxpoints == 13)
        {
            // tre in mano che vince sicuro
            if (CASO(10) != 9)
            {
                TRACE("[TRALG]Dentro per win\n");
                doVadoDentro(min_pos);
                return;
            }
        }
        else if (maxpoints > 10)
        {
            if (CASO(maxpoints) > 9)
            {
                TRACE("[TRALG]Dentro per win con rischio\n");
                doVadoDentro(min_pos);
                return;
            }
        }
        else if (result != NULL && min_points < maxPointsMano1)
        {
            TRACE("[TRALG]Dentro per bluf\n");
            doVadoDentro(min_pos);
            return;
        }
        else if (CASO(3) == 1 && m_eScoreCurrent <= SC_INVIDO)
        {
            if (result != NULL && ChiamaDiPiu(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R5_primavinta\n");
                result = NULL;
            }
        }
        if (result != NULL)
        {
            result = m_vct_Cards_CPU[min_pos].GetCardInfo();
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_cand_min_pos: %s\n", result->CardName);
        }
    }
    else if (m_iNumManiWon == 1 && maxpoints >= 12 && m_arrIxPlayerWonHand[0] == m_iMyIndex)
    {
        if (ChiamaDiPiu(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R1bisFortePrimamia\n");
            result = NULL;
        }
    }
    else if (curr_mano == 1 && maxpoints >= 12 && med_points < 10 && med_points > 0)
    {
        result = m_vct_Cards_CPU[med_pos].GetCardInfo();
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_cand_med_pos: %s\n", result->CardName);
    }
    else if (curr_mano == 1 && maxpoints >= 11 && med_points < 10)
    {
        if (CASO(10) > 5)
        {
            result = m_vct_Cards_CPU[med_pos].GetCardInfo();
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_cand_med_pos Brnd: %s\n", result->CardName);
        }
    }
    else if (m_iNumManiWon == 1 && maxpoints >= 12 && m_eScoreCurrent == SC_CANELA)
    {
        if (ChiamaDiPiu(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R1Bvintauna\n");
            result = NULL;
        }
    }
    else if (m_bLastManoPatada)
    {
        if (maxpoints == 13)
        {
            if (result != NULL && ChiamaDiPiu(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R2A_manopatada\n");
                result = NULL;
            }
        }
        else if (maxpoints <= 10)
        {
            if (result != NULL && ChiamaAMonte(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R2B_manopatada\n");
                result = NULL;
            }
        }
        else if ((maxpoints == 12 || maxpoints == 11) && m_eScoreCurrent <= SC_INVIDO)
        {

            if (CASO(30) < maxpoints && result != NULL && ChiamaDiPiu(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R2C_manopatada\n");
                result = NULL;
            }
        }
    }
    else if (maxpoints == 13 && sum_points > 21 && CASO(10) > 6 && m_eScoreCurrent <= SC_INVIDO)
    {
        if (result != NULL && ChiamaDiPiu(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R3_tre\n");
            result = NULL;
        }
    }
    else if (sum_points < 15 && curr_mano == 1 && CASO(2) == 1)
    {
        // mano scarsa
        if (result != NULL && ChiamaAMonte(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R4_poco\n");
            result = NULL;
        }
    }
    else if (curr_mano == 3 && m_arrIxPlayerWonHand[0] == m_iMyIndex)
    {
        // terza mano prima mia
        if (maxpoints == 13)
        {
            if (CASO(20) > 16)
            {
                // bluff
                if (result != NULL && ChiamaAMonte(lastNumChiamate))
                {
                    result = NULL;
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R7_bluff_coltre\n");
                }
            }
            else
            {
                if (result != NULL && ChiamaDiPiu(lastNumChiamate))
                {
                    result = NULL;
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R8_tre\n");
                }
            }
        }
        else if (maxpoints == 12)
        {
            if (CASO(20) > 14)
            {
                if (result != NULL && ChiamaAMonte(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R9_bluffcoldue\n");
                    result = NULL;
                }
            }
            else if (CASO(2) == 1 && m_eScoreCurrent <= SC_INVIDO)
            {
                if (result != NULL && ChiamaDiPiu(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R10_due\n");
                    result = NULL;
                }
            }
        }
        else if (maxpoints == 10 || maxpoints == 9)
        {
            if (CASO(20) > 11)
            {
                if (result != NULL && ChiamaAMonte(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R11_poco\n");
                    result = NULL;
                }
            }
            else if (CASO(20) > 15 && m_eScoreCurrent <= SC_INVIDO)
            {
                if (result != NULL && ChiamaDiPiu(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R12_bluffconpoco\n");
                    result = NULL;
                }
            }
        }
        else
        {
            if (CASO(20) > 7)
            {
                if (result != NULL && ChiamaAMonte(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R13_amonte\n");
                    result = NULL;
                }
            }
        }

    }
    else if (curr_mano == 3 && m_arrIxPlayerWonHand[0] == m_iOppIndex)
    {
        // terza mano, prima vinta dall'avversario
        if (maxpoints == 13)
        {
            if (CASO(20) > 15)
            {
                // bluff
                if (result != NULL && ChiamaAMonte(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R14_bluffcoltre\n");
                    result = NULL;
                }
            }
            else if (CASO(20) > 9 && m_eScoreCurrent <= SC_INVIDO)
            {
                if (result != NULL && ChiamaDiPiu(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R15_tre\n");
                    result = NULL;
                }
            }
        }
        else if (maxpoints == 12)
        {
            if (CASO(20) > 12)
            {
                if (result != NULL && ChiamaAMonte(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R16_montecoldue\n");
                    result = NULL;
                }
            }
            else if (CASO(3) == 1)
            {
                if (result != NULL && ChiamaDiPiu(lastNumChiamate) && m_eScoreCurrent <= SC_INVIDO)
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R17_rilanciodue\n");
                    result = NULL;
                }
            }
        }
        else if (maxpoints == 10 || maxpoints == 9)
        {
            if (CASO(20) > 9)
            {
                if (result != NULL &&  ChiamaAMonte(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R17_montecolre\n");
                    result = NULL;
                }
            }
            else if (CASO(20) > 17)
            {
                if (result != NULL && ChiamaDiPiu(lastNumChiamate) && m_eScoreCurrent <= SC_INVIDO)
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R18_rilanciocolre\n");
                    result = NULL;
                }
            }
        }
        else
        {
            if (CASO(20) > 5)
            {
                if (result != NULL && ChiamaAMonte(lastNumChiamate))
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R19_monte\n");
                    result = NULL;
                }
            }
        }

    }

    if (CASO(40) > 37)
    {
        // chiamata a monte rara
        if (result != NULL && ChiamaAMonte(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R20_monteraro\n");
            result = NULL;
        }
    }

    if (lastNumChiamate == m_iNumChiamateInGiocata && result == NULL)
    {
        ASSERT(0);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF_R21_giocaacaso\n");
        GiocaACaso();
    }

    if (result != NULL)
    {
        ASSERT(m_pCoreGame);
        m_pCoreGame->Player_playCard(m_iMyIndex, result);
    }
    else
    {
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PLF non gioca carta per chiamata\n");
    }
}

void cAlgAdvancedPlayer::GiocaACaso()
{
    CardSpec cardUndef;
    int iCartaPos = CASO(3);
    int iLoops = 0;
    while (m_vct_Cards_CPU[iCartaPos] == cardUndef && iLoops < NUM_CARDS_HAND)
    {
        iCartaPos++;
        if (iCartaPos >= NUM_CARDS_HAND)
        {
            iCartaPos = 0;
        }
        iLoops++;
    }
    ASSERT(m_pCoreGame);
    m_pCoreGame->Player_playCard(m_iMyIndex, m_vct_Cards_CPU[iCartaPos].GetCardInfo());
}

void cAlgAdvancedPlayer::PlayAsSecond()
{
    CARDINFO* result = NULL;
    CardSpec cardUndef;
    ASSERT(m_vct_Cards_played[m_ixCurrMano].size() == 1);
    CardSpec cardPlayed = m_vct_Cards_played[m_ixCurrMano].front();

    int pointsFirstCard = cardPlayed.GetPoints();
    int curr_mano = NumMano();
    int lastNumChiamate = m_iNumChiamateInGiocata;

    int iLoops = 0, i, maxpoints = 0, max_pos = 0, sum_points = 0, min_pos = 0;
    int min_points = 20, same_points_pos = -1, first_take_pos = -1, first_take_points = 20;
    int arrPoints[NUM_CARDS_HAND] = { 0,0,0 };
    for (i = 0; i < NUM_CARDS_HAND; i++)
    {
        if (m_vct_Cards_CPU[i] == cardUndef)
        {
            continue;
        }
        int points = m_vct_Cards_CPU[i].GetPoints();
        if (points > maxpoints)
        {
            maxpoints = points;
            max_pos = i;
        }
        if (points < min_points)
        {
            min_pos = i;
            min_points = points;
        }
        if (pointsFirstCard == points)
        {
            same_points_pos = i;
        }
        if (points > pointsFirstCard && points < first_take_points)
        {
            first_take_pos = i; // La carta più bassa che può prendere
            first_take_points = points;
        }
        arrPoints[i] = points;
        sum_points += points;
    }
    TRACE("[2ND]Points played card %d, Take: min pos %d (pt %d), first_take_pos %d (pt %d), max pos %d(pt %d) \n", pointsFirstCard, min_pos,
        min_points, first_take_pos, first_take_points, max_pos, maxpoints);
    if (m_opponetIsVadoDentro)
    {
        // Avversario è andato dentro, quindi si gioca la carta più bassa che si vince la mano
        result = m_vct_Cards_CPU[min_pos].GetCardInfo();
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_min_vadodentro: %s\n", result->CardName);
    }
    else if (first_take_pos != -1)
    {
        // si prende
        result = m_vct_Cards_CPU[first_take_pos].GetCardInfo();
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_cand_first_take_pos: %s\n", result->CardName);
    }
    else if (same_points_pos != -1)
    {
        //poi se patta
        result = m_vct_Cards_CPU[same_points_pos].GetCardInfo();
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_cand_same_pos: %s\n", result->CardName);
    }
    else
    {
        // perdo, quindi gioca la carta più bassa
        result = m_vct_Cards_CPU[min_pos].GetCardInfo();
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_cand_min_pos: %s\n", result->CardName);
    }

    if (m_opponetIsVadoDentro)
    {
        // play the min card and say nothing
    }
    else if (pointsFirstCard > maxpoints && m_iNumManiWon == 0 && curr_mano > 1)
    {
        if (CASO(20) < 16)
        {
            if (result != NULL && ChiamaAMonte(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R1_monte\n");
                result = NULL;
            }
        }
    }
    else if (curr_mano == 3 && pointsFirstCard == maxpoints && pointsFirstCard == 13 &&
        m_arrIxPlayerWonHand[0] == m_iMyIndex)
    {
        if (result != NULL && ChiamaAMonte(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R2_megacagna\n");
            result = NULL;
        }
        else if (result != NULL && ChiamaDiPiu(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R2C_piu\n");
            result = NULL;
        }

    }
    else if (first_take_pos == -1 && m_iNumManiWon == 0 && curr_mano > 1)
    {
        if (result != NULL && ChiamaAMonte(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R1B_perdosempre\n");
            result = NULL;
        }
    }
    else if (first_take_pos != -1 && m_bLastManoPatada)
    {
        int rest = pointsFirstCard >= 12 ? 15 : 35;
        if (CASO(40) > rest)
        {
            if (result != NULL && ChiamaAMonte(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R2A_monte_cagna\n");
                result = NULL;
            }
        }
        else
        {
            if (result != NULL && ChiamaDiPiu(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R2B_chiama\n");
                result = NULL;
            }
        }
    }
    else if (curr_mano == 3 && same_points_pos != -1 && m_iNumManiWon == 1 && m_WonFirstHand)
    {
        // terza posso pattare e la prima è mia, si vice sicuro, quindi chiama di più
        if ((CASO(30 - pointsFirstCard) > 3) || (m_MyLastSay == AMONTE))
        {
            if (result != NULL && ChiamaDiPiu(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R3B_pata_chiama\n");
                result = NULL;
            }
        }
        else
        {
            if (result != NULL && ChiamaAMonte(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R3B_pata_cagna\n");
                result = NULL;
            }
        }
    }
    else if (curr_mano == 3 && first_take_pos != -1 && m_iNumManiWon == 1)
    {
        if (CASO(40) > 35 && pointsFirstCard >= 10 && m_eScoreCurrent <= SC_TRASMAS)
        {
            if (result != NULL && ChiamaAMonte(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R2B_monte_cagna\n");
                result = NULL;
            }
        }
        else
        {
            if (result != NULL && ChiamaDiPiu(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R2B_chiama\n");
                result = NULL;
            }
        }
    }
    else if (curr_mano == 1 && first_take_pos != -1 && pointsFirstCard <= 11)
    {
        if (result != NULL && ChiamaDiPiu(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R3A_chiama\n");
            result = NULL;
        }
    }
    else if (same_points_pos != -1 && maxpoints >= 12)
    {
        result = m_vct_Cards_CPU[same_points_pos].GetCardInfo();
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_cand_same_points_pos: %s\n", result->CardName);
        if (CASO(20) > 5)
        {
            if (result != NULL && ChiamaDiPiu(lastNumChiamate))
            {
                result = NULL;
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R4A_dipiu\n");
            }
        }
        else if (CASO(20) > 17)
        {
            if (result != NULL && ChiamaAMonte(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R4B_monte\n");
                result = NULL;
            }
        }
    }
    else if (pointsFirstCard > maxpoints)
    {
        // si perde la mano
        if (CASO(20) > 15 || (curr_mano == 3 && m_iNumManiWon == 1) || (curr_mano == 2 && m_iNumManiWon == 0))
        {
            if (result != NULL && ChiamaAMonte(lastNumChiamate))
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R5_monte\n");
                result = NULL;
            }
        }
        if (result != NULL && curr_mano > 1)
        {
            // Vado dentro
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd non prendo, quindi dentro per vergona\n");
            doVadoDentro(min_pos);
            return;
        }
    }
    else if (lastNumChiamate == m_iNumChiamateInGiocata && result == NULL)
    {
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd_R5_acaso\n");
        ASSERT(0);
        GiocaACaso();
    }

    if (result != NULL)
    {
        m_pCoreGame->Player_playCard(m_iMyIndex, result);
    }
    else
    {
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]PL2nd non gioca per chiamata pending\n");
    }

}

BOOL cAlgAdvancedPlayer::IsPlayerFirst()
{
    return m_vct_Cards_played[m_ixCurrMano].size() == 0 ? TRUE : FALSE;
}

// Ritorna: 1,2,3 a seconda della mano
int cAlgAdvancedPlayer::NumMano()
{
    return m_ixCurrMano + 1;
}


////////////////////////////////////////
//       ALG_Play
/*! player have to play notification
*/
void cAlgAdvancedPlayer::ALG_Play()
{
    if (IsPlayerFirst())
    {
        PlayAsFirst();
    }
    else
    {
        PlayAsSecond();
    }

}

////////////////////////////////////////
//       ALG_ManoEnd
/*! mano end notification
*/
void cAlgAdvancedPlayer::ALG_ManoEnd(I_MatchScore* pScore)
{
    m_opponetIsVadoDentro = FALSE;
    m_ixCurrMano++;

    m_bLastManoPatada = pScore->IsManoPatada();
    int index = pScore->GetManoNum() - 1;
    ASSERT(index >= 0 && index < NUM_CARDS_HAND);
    m_arrIxPlayerWonHand[index] = m_bLastManoPatada ? -2 : pScore->GetManoWinner();
    m_iNumChiamateMonte = 0;
    if (pScore->GetManoWinner() == m_iMyIndex && !pScore->IsManoPatada())
    {
        if (index == 0 || (index == 1 && m_bLastManoPatada))
        {
            m_WonFirstHand = TRUE;
        }
        m_iNumManiWon += 1;
    }
}

////////////////////////////////////////
//       ALG_GiocataEnd
/*!
*/
void cAlgAdvancedPlayer::ALG_GiocataEnd(I_MatchScore* pScore)
{
    if (m_pTracer)
    {
        if (m_iMyIndex == 0)
        {
            BOOL bIsPata = pScore->IsGiocataPatada();
            if (bIsPata)
            {
                // giocata patada
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Giocata patada\n");
            }
            else if (pScore->IsGiocataMonte())
            {
                // giocata a monte
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Giocata a monte\n");
            }
            else
            {
                // winner
                int iPlWinner = pScore->GetGiocataWinner();

                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Giocata vinta da %d\n", iPlWinner);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Punteggio player 0: %d, punteggio player 1: %d\n",
                    pScore->GetPointsPlayer(m_iMyIndex),
                    pScore->GetPointsPlayer(m_iOppIndex));
            }
        }
    }
}

////////////////////////////////////////
//       ALG_MatchEnd
/*! match end notification
*/
void cAlgAdvancedPlayer::ALG_MatchEnd(I_MatchScore* pScore)
{
    int iPlWinner = pScore->GetMatchWinner();
    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Match vinto da %d\n", iPlWinner);
    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Punteggio player 0: %d, punteggio player 1: %d\n",
        pScore->GetPointsPlayer(m_iMyIndex),
        pScore->GetPointsPlayer(m_iOppIndex));

}

////////////////////////////////////////
//       ALG_HaveToRespond
/*! Algorithm is invited to respond
*/
void cAlgAdvancedPlayer::ALG_HaveToRespond()
{
    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] have to respond");
    CardSpec cardUndef;
    int lastNumChiamate = m_iNumChiamateInGiocata;
    if (m_OpponentSay == AMONTE && m_sayMyRisp == NO)
    {
        // a monte was called and it was responded NO, don't change idea
        Chiama(m_sayMyRisp, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say R1");
        return;
    }

    size_t iRndIndex;
    VCT_COMMANDS vct_cmd;
    ASSERT(m_pCoreGame);

    int pointsFirstCard = -1;
    if (m_vct_Cards_played[m_ixCurrMano].size() > 0)
    {
        pointsFirstCard = m_vct_Cards_played[m_ixCurrMano][0].GetPoints();
    }

    m_pCoreGame->GetAdmittedCommands(vct_cmd, m_iMyIndex);
    size_t iNumCmds = vct_cmd.size();
    int iLoops = 0, i, maxpoints = 0, max_pos = 0, sum_points = 0, min_pos = 0;
    int min_points = 20;
    int arrPoints[NUM_CARDS_HAND] = { 0,0,0 };
    for (i = 0; i < NUM_CARDS_HAND; i++)
    {
        if (m_vct_Cards_CPU[i] == cardUndef)
        {
            continue;
        }
        int points = m_vct_Cards_CPU[i].GetPoints();
        if (points > maxpoints)
        {
            maxpoints = points;
            max_pos = i;
        }
        if (points < min_points)
        {
            min_pos = i;
            min_points = points;
        }
        arrPoints[i] = points;
        sum_points += points;
    }
    int curr_mano = NumMano();
    TRACE("[ALG] Say: points first card %d, max points %d \n", pointsFirstCard, maxpoints);

    if (m_OpponentSay >= INVIDO && m_OpponentSay <= PARTIDA)
    {
        handleSayPopints(curr_mano, pointsFirstCard, lastNumChiamate, maxpoints, sum_points);
    } 
    else if (m_OpponentSay == AMONTE)
    {
        handleSayAmonte(curr_mano, pointsFirstCard, lastNumChiamate, maxpoints, sum_points);
    }
    else
    {
        iRndIndex = CASO(iNumCmds);
        Chiama(vct_cmd[iRndIndex], lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say R18");
    }
}

void cAlgAdvancedPlayer::handleSayPopints(int curr_mano, int pointsFirstCard, int lastNumChiamate, int maxpoints, int sum_points)
{
    if (maxpoints == 13 && m_bLastManoPatada)
    {
        if (!ChiamaDiPiu(lastNumChiamate))
        {
            Chiama(GIOCA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R000");
        }
        else
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R001");
        }
    }
    else if ((curr_mano == 1 && sum_points > 22 && maxpoints >= 12) ||
        (maxpoints >= 12 && m_iNumManiWon == 1))
    {
        if (CASO(40) > 32)
        {
            if (!ChiamaDiPiu(lastNumChiamate))
            {
                Chiama(GIOCA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R002");
            }
            else
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R003");
            }
        }
        else
        {
            if (!m_bIamCalledPoints && CASO(35) > 28)
            {
                if (!ChiamaAMonte(lastNumChiamate))
                {
                    Chiama(GIOCA, lastNumChiamate);
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R004");
                }
                else
                {
                    m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R005");
                }
            }
            else
            {
                Chiama(GIOCA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R006");
            }
        }
    }
    else if (m_iPlayerOnTurn != m_iMyIndex && pointsFirstCard < 10 && curr_mano == 3)
    {
        if (CASO(2) == 1)
        {
            if (!ChiamaAMonte(lastNumChiamate))
            {
                Chiama(VADOVIA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R007");
            }
            else
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R008");
            }
        }
        else
        {
            Chiama(VADOVIA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R009");
        }
    }
    else if (curr_mano > 1 && m_iNumManiWon == 0 && m_iPlayerOnTurn == m_iMyIndex &&
        pointsFirstCard > maxpoints)
    {
        // persa a tutte le maniere
        if (CASO(2) == 1)
        {
            if (!ChiamaAMonte(lastNumChiamate))
            {
                Chiama(VADOVIA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R010");
            }
            else
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R011");
            }
        }
        else if (CASO(40) > 36)
        {
            // bluff spudorato
            if (!ChiamaDiPiu(lastNumChiamate))
            {
                Chiama(VADOVIA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R012");
            }
            else
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R013");
            }
        }
        else
        {
            Chiama(VADOVIA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R014");
        }
    }
    else if (pointsFirstCard < maxpoints && maxpoints >= 12)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R015");
    }
    else if (pointsFirstCard == 11 && curr_mano == 1 && m_iPlayerOnTurn == m_iOppIndex
        && maxpoints <= 11)
    {
        if (CASO(10) > 2)
        {
            if (!ChiamaAMonte(lastNumChiamate))
            {
                Chiama(VADOVIA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R016");
            }
            else
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R017");
            }
        }
        else
        {
            Chiama(GIOCA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R018");
        }
    }
    else if (curr_mano == 1 && pointsFirstCard >= 12 && m_iOppIndex == m_iPlayerOnTurn)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R019");
    }
    else if (curr_mano == 2 && maxpoints >= 12 && m_iNumManiWon >= 1)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R020");
    }
    else if (m_bLastManoPatada && ((pointsFirstCard < 10 && m_iOppIndex == m_iPlayerOnTurn) ||
        maxpoints < 10))
    {
        if (!ChiamaAMonte(lastNumChiamate))
        {
            Chiama(VADOVIA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R021");
        }
        else
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R022");
        }
    }
    else if (m_iNumManiWon == 1 && pointsFirstCard >= 12 && m_iOppIndex == m_iPlayerOnTurn)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R023");
    }
    else if (m_iNumManiWon == 1 &&
        (pointsFirstCard < maxpoints || (m_arrIxPlayerWonHand[0] == m_iMyIndex && pointsFirstCard == maxpoints))
        && m_iMyIndex == m_iPlayerOnTurn)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R024");
    }
    else if (m_bLastManoPatada && pointsFirstCard <= maxpoints && m_iMyIndex == m_iPlayerOnTurn)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R025");
    }
    else if (curr_mano == 1 && maxpoints < 11 && pointsFirstCard == -1)
    {
        if (CASO(10) > 4)
        {
            if (!ChiamaAMonte(lastNumChiamate))
            {
                Chiama(VADOVIA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R026");
            }
        }
        else
        {
            Chiama(VADOVIA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R027");
        }
    }
    else if (curr_mano == 1 && maxpoints <= pointsFirstCard &&  pointsFirstCard < 11 && m_iPlayerOnTurn == m_iOppIndex)
    {
        if (CASO(10) > 4)
        {
            if (!ChiamaAMonte(lastNumChiamate))
            {
                Chiama(VADOVIA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R028");
            }
        }
        else
        {
            Chiama(VADOVIA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R029");
        }
    }
    else if (curr_mano == 2 && (maxpoints < pointsFirstCard || (pointsFirstCard == -1 && maxpoints < 11)) && m_iNumManiWon == 0)
    {
        if (CASO(10) > 4)
        {
            if (!ChiamaAMonte(lastNumChiamate))
            {
                Chiama(VADOVIA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R030");
            }
        }
        else
        {
            Chiama(VADOVIA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R031");
        }
    }
    else if ((m_iNumManiWon == 1 || m_bLastManoPatada) && m_bIamCalledPoints)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R032");
    }
    else if (curr_mano == 1 && pointsFirstCard == -1 && maxpoints >= 30)
    {
        Chiama(GIOCA, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R032");
    }
    else if (curr_mano == 2 && m_iNumManiWon == 0 && maxpoints < 12 && m_iPlayerOnTurn == m_iOppIndex)
    {
        if (!ChiamaAMonte(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R033");
            Chiama(VADOVIA, lastNumChiamate);
        }
        else
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R034");
        }
    }
    else if (curr_mano == 1 && maxpoints < 12 && pointsFirstCard < 12 && m_iPlayerOnTurn == m_iOppIndex)
    {
        if (!ChiamaAMonte(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R035");
            Chiama(VADOVIA, lastNumChiamate);
        }
        else
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R036");
        }
    }
    else if (curr_mano == 3 && m_iPlayerOnTurn == m_iOppIndex && (( pointsFirstCard < 11 && !m_WonFirstHand) ||
                                                                 ( pointsFirstCard < 12 && m_WonFirstHand)))
    {
        if (!ChiamaAMonte(lastNumChiamate))
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R035-A");
            Chiama(VADOVIA, lastNumChiamate);
        }
        else
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R036-B");
        }
    }
    else
    {
        TRACE("[TRALG] unhandled response rule: curr_mano %d, maxpoints: %d, pointsFirstCard %d, m_iPlayerOnTurn %d, prima vinta %d, mani vinte %d \n",
            curr_mano, maxpoints, pointsFirstCard, m_iPlayerOnTurn, m_WonFirstHand, m_iNumManiWon);
        if (CASO(10) > 5)
        {
            Chiama(GIOCA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R037");
        }
        else if (CASO(10) > 4)
        {
            if (!ChiamaAMonte(lastNumChiamate))
            {
                Chiama(GIOCA, lastNumChiamate);
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R038");
            }
            else
            {
                m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R039");
            }
        }
        else
        {
            Chiama(VADOVIA, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Pt R040");
        }
    }
}

void cAlgAdvancedPlayer::handleSayAmonte(int curr_mano, int pointsFirstCard, int lastNumChiamate, int maxpoints, int sum_points)
{
    if (curr_mano == 1 && pointsFirstCard == 13 && m_iPlayerOnTurn != m_iMyIndex)
    {
        Chiama(NO, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R20No");
    }
    else if (pointsFirstCard > maxpoints && m_iNumManiWon == 0 &&
        m_iPlayerOnTurn == m_iMyIndex)
    {
        Chiama(VABENE, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R13");
    }
    else if (((maxpoints < 10 && m_iNumManiWon == 0) ||
        (sum_points < 15 && m_iNumManiWon == 0))
        && m_iPlayerOnTurn == m_iMyIndex)
    {
        Chiama(VABENE, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R14");
    }
    else if ((m_iPlayerOnTurn != m_iMyIndex) && (curr_mano == 3) && (pointsFirstCard < 10) && (maxpoints == 0))
    {
        Chiama(VABENE, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say Va bene carta bassa giocata terza mano");
    }
    else if (curr_mano == 3 && pointsFirstCard == -1 && maxpoints < 9)
    {
        Chiama(VABENE, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R15A");
    }
    else if (m_iNumManiWon == 1 && m_iPlayerOnTurn == m_iMyIndex && pointsFirstCard != -1 && maxpoints > pointsFirstCard)
    {
        Chiama(NO, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R15D");
    }
    else if (m_iNumManiWon == 1 && m_iPlayerOnTurn == m_iMyIndex && pointsFirstCard != -1 && maxpoints == pointsFirstCard
        && m_arrIxPlayerWonHand[0] == m_iMyIndex)
    {
        Chiama(NO, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRispv R15B");
    }
    else if (m_iNumManiWon == 1 && maxpoints < 10 && m_iPlayerOnTurn == m_iMyIndex)
    {
        if (CASO(20) > 15)
        {
            Chiama(NO, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R15C");
        }
        else
        {
            Chiama(VABENE, lastNumChiamate);
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R16");
        }
    }
    else if (curr_mano == 1 && sum_points < 23 && pointsFirstCard == -1)
    {
        Chiama(VABENE, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R16B");
    }
    else if (m_bLastManoPatada && ((pointsFirstCard < 10 && m_iOppIndex == m_iPlayerOnTurn) ||
        maxpoints < 10))
    {
        Chiama(VABENE, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R16C");
    }
    else if (curr_mano > 1 && m_iNumManiWon == 0 && pointsFirstCard == -1 && maxpoints < 12 &&
        m_eScoreCurrent >= SC_INVIDO)
    {
        Chiama(VABENE, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R16D");
    }
    else
    {
        Chiama(NO, lastNumChiamate);
        m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG] Say MonteRisp R17");
    }
}


////////////////////////////////////////
//       ALG_GicataScoreChange
/*!
// \param eGiocataScoreState eNewScore :
*/
void cAlgAdvancedPlayer::ALG_GicataScoreChange(eGiocataScoreState eNewScore)
{
    m_eScoreCurrent = eNewScore;
    if (m_pTracer)
    {
        if (m_iMyIndex == 0)
        {
            m_pTracer->AddSimpleTrace(m_itrChan, "[TRALG]Score changed to %d\n", eNewScore);
        }
    }
}


void cAlgAdvancedPlayer::ALG_PlayerSaidWrong(int iPlayerIx)
{
}

