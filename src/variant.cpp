/*
  Fairy-Stockfish, a UCI chess variant playing engine derived from Stockfish
  Copyright (C) 2018 Fabian Fichter

  Fairy-Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Fairy-Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>

#include "variant.h"

using std::string;

VariantMap variants; // Global object

    // Define variant rules
    Variant* fairy_variant_base() {
        Variant* v = new Variant();
        v->endgameEval = false;
        return v;
    }
    Variant* chess_variant() {
        Variant* v = fairy_variant_base();
        v->endgameEval = true;
        return v;
    }
    Variant* makruk_variant() {
        Variant* v = chess_variant();
        v->remove_piece(BISHOP);
        v->remove_piece(QUEEN);
        v->add_piece(KHON, 's');
        v->add_piece(MET, 'm');
        v->startFen = "rnsmksnr/8/pppppppp/8/8/PPPPPPPP/8/RNSKMSNR w - - 0 1";
        v->promotionRank = RANK_6;
        v->promotionPieceTypes = {MET};
        v->doubleStep = false;
        v->castling = false;
        return v;
    }
    Variant* asean_variant() {
        Variant* v = chess_variant();
        v->remove_piece(BISHOP);
        v->remove_piece(QUEEN);
        v->add_piece(KHON, 'b');
        v->add_piece(MET, 'q');
        v->startFen = "rnbqkbnr/8/pppppppp/8/8/PPPPPPPP/8/RNBQKBNR w - - 0 1";
        v->promotionPieceTypes = {ROOK, KNIGHT, KHON, MET};
        v->doubleStep = false;
        v->castling = false;
        return v;
    }
    Variant* aiwok_variant() {
        Variant* v = makruk_variant();
        v->remove_piece(MET);
        v->add_piece(AIWOK, 'a');
        v->startFen = "rnsaksnr/8/pppppppp/8/8/PPPPPPPP/8/RNSKASNR w - - 0 1";
        v->promotionPieceTypes = {AIWOK};
        return v;
    }
    Variant* shatranj_variant() {
        Variant* v = fairy_variant_base();
        v->remove_piece(BISHOP);
        v->remove_piece(QUEEN);
        v->add_piece(ALFIL, 'b');
        v->add_piece(FERS, 'q');
        v->startFen = "rnbkqbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR w - - 0 1";
        v->promotionPieceTypes = {FERS};
        v->doubleStep = false;
        v->castling = false;
        v->bareKingValue = -VALUE_MATE;
        v->bareKingMove = true;
        v->stalemateValue = -VALUE_MATE;
        return v;
    }
    Variant* amazon_variant() {
        Variant* v = chess_variant();
        v->remove_piece(QUEEN);
        v->add_piece(AMAZON, 'a');
        v->startFen = "rnbakbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBAKBNR w KQkq - 0 1";
        v->promotionPieceTypes = {AMAZON, ROOK, BISHOP, KNIGHT};
        return v;
    }
    Variant* hoppelpoppel_variant() {
        Variant* v = chess_variant();
        v->remove_piece(KNIGHT);
        v->remove_piece(BISHOP);
        v->add_piece(KNIBIS, 'n');
        v->add_piece(BISKNI, 'b');
        v->promotionPieceTypes = {QUEEN, ROOK, BISKNI, KNIBIS};
        return v;
    }
    Variant* kingofthehill_variant() {
        Variant* v = fairy_variant_base();
        v->flagPiece = KING;
        v->whiteFlag = make_bitboard(SQ_D4, SQ_E4, SQ_D5, SQ_E5);
        v->blackFlag = make_bitboard(SQ_D4, SQ_E4, SQ_D5, SQ_E5);
        v->flagMove = false;
        return v;
    }
    Variant* racingkings_variant() {
        Variant* v = fairy_variant_base();
        v->startFen = "8/8/8/8/8/8/krbnNBRK/qrbnNBRQ w - - 0 1";
        v->flagPiece = KING;
        v->whiteFlag = Rank8BB;
        v->blackFlag = Rank8BB;
        v->flagMove = true;
        v->castling = false;
        v->checking = false;
        return v;
    }
    Variant* losers_variant() {
        Variant* v = fairy_variant_base();
        v->checkmateValue = VALUE_MATE;
        v->stalemateValue = VALUE_MATE;
        v->bareKingValue = VALUE_MATE;
        v->bareKingMove = false;
        v->mustCapture = true;
        return v;
    }
    Variant* giveaway_variant() {
        Variant* v = fairy_variant_base();
        v->remove_piece(KING);
        v->add_piece(COMMONER, 'k');
        v->promotionPieceTypes = {COMMONER, QUEEN, ROOK, BISHOP, KNIGHT};
        v->stalemateValue = VALUE_MATE;
        v->extinctionValue = VALUE_MATE;
        v->extinctionPieceTypes = {ALL_PIECES};
        v->mustCapture = true;
        return v;
    }
    Variant* antichess_variant() {
        Variant* v = giveaway_variant();
        v->startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1";
        v->castling = false;
        return v;
    }
    Variant* codrus_variant() {
        Variant* v = giveaway_variant();
        v->promotionPieceTypes = {QUEEN, ROOK, BISHOP, KNIGHT};
        v->extinctionPieceTypes = {COMMONER};
        return v;
    }
    Variant* extinction_variant() {
        Variant* v = fairy_variant_base();
        v->remove_piece(KING);
        v->add_piece(COMMONER, 'k');
        v->promotionPieceTypes = {COMMONER, QUEEN, ROOK, BISHOP, KNIGHT};
        v->extinctionValue = -VALUE_MATE;
        v->extinctionPieceTypes = {COMMONER, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};
        return v;
    }
    Variant* kinglet_variant() {
        Variant* v = extinction_variant();
        v->promotionPieceTypes = {COMMONER};
        v->extinctionPieceTypes = {PAWN};
        return v;
    }
    Variant* horde_variant() {
        Variant* v = fairy_variant_base();
        v->startFen = "rnbqkbnr/pppppppp/8/1PP2PP1/PPPPPPPP/PPPPPPPP/PPPPPPPP/PPPPPPPP w kq - 0 1";
        v->firstRankDoubleSteps = true;
        v->extinctionValue = -VALUE_MATE;
        v->extinctionPieceTypes = {ALL_PIECES};
        return v;
    }
    Variant* threecheck_variant() {
        Variant* v = fairy_variant_base();
        v->startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 3+3 0 1";
        v->maxCheckCount = CheckCount(3);
        return v;
    }
    Variant* fivecheck_variant() {
        Variant* v = fairy_variant_base();
        v->startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 5+5 0 1";
        v->maxCheckCount = CheckCount(5);
        return v;
    }
    Variant* crazyhouse_variant() {
        Variant* v = fairy_variant_base();
        v->startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR[] w KQkq - 0 1";
        v->pieceDrops = true;
        v->capturesToHand = true;
        return v;
    }
    Variant* loop_variant() {
        Variant* v = crazyhouse_variant();
        v->dropLoop = true;
        return v;
    }
    Variant* chessgi_variant() {
        Variant* v = loop_variant();
        v->firstRankDrops = true;
        return v;
    }
    Variant* pocketknight_variant() {
        Variant* v = fairy_variant_base();
        v->startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR[Nn] w KQkq - 0 1";
        v->pieceDrops = true;
        v->capturesToHand = false;
        return v;
    }
    Variant* placement_variant() {
        Variant* v = chess_variant();
        v->startFen = "8/pppppppp/8/8/8/8/PPPPPPPP/8[KQRRBBNNkqrrbbnn] w - - 0 1";
        v->mustDrop = true;
        v->pieceDrops = true;
        v->capturesToHand = false;
        v->whiteDropRegion = Rank1BB;
        v->blackDropRegion = Rank8BB;
        v->dropOppositeColoredBishop = true;
        v->castlingDroppedPiece = true;
        return v;
    }
    Variant* sittuyin_variant() {
        Variant* v = makruk_variant();
        v->startFen = "8/8/4pppp/pppp4/4PPPP/PPPP4/8/8[KFRRSSNNkfrrssnn] w - - 0 1";
        v->remove_piece(MET);
        v->add_piece(MET, 'f');
        v->mustDrop = true;
        v->pieceDrops = true;
        v->capturesToHand = false;
        v->whiteDropRegion = Rank1BB | Rank2BB | Rank3BB;
        v->blackDropRegion = Rank8BB | Rank7BB | Rank6BB;
        v->sittuyinRookDrop = true;
        v->promotionRank = RANK_1; // no regular promotions
        v->sittuyinPromotion = true;
        v->immobilityIllegal = false;
        return v;
    }
    Variant* euroshogi_variant() {
        Variant* v = fairy_variant_base();
        v->reset_pieces();
        v->add_piece(SHOGI_PAWN, 'p');
        v->add_piece(EUROSHOGI_KNIGHT, 'n');
        v->add_piece(GOLD, 'g');
        v->add_piece(BISHOP, 'b');
        v->add_piece(HORSE, 'h');
        v->add_piece(ROOK, 'r');
        v->add_piece(KING, 'k');
        v->add_piece(DRAGON, 'd');
        v->startFen = "1nbgkgn1/1r4b1/pppppppp/8/8/PPPPPPPP/1B4R1/1NGKGBN1[-] w 0 1";
        v->pieceDrops = true;
        v->capturesToHand = true;
        v->promotionRank = RANK_6;
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->promotedPieceType[SHOGI_PAWN]       = GOLD;
        v->promotedPieceType[EUROSHOGI_KNIGHT] = GOLD;
        v->promotedPieceType[SILVER]           = GOLD;
        v->promotedPieceType[BISHOP]           = HORSE;
        v->promotedPieceType[ROOK]             = DRAGON;
        v->mandatoryPiecePromotion = true;
        v->immobilityIllegal = true;
        v->shogiPawnDropMateIllegal = true;
        return v;
    }
    Variant* judkinsshogi_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_6;
        v->maxFile = FILE_F;
        v->reset_pieces();
        v->add_piece(SHOGI_PAWN, 'p');
        v->add_piece(SHOGI_KNIGHT, 'n');
        v->add_piece(SILVER, 's');
        v->add_piece(GOLD, 'g');
        v->add_piece(BISHOP, 'b');
        v->add_piece(HORSE, 'h');
        v->add_piece(ROOK, 'r');
        v->add_piece(DRAGON, 'd');
        v->add_piece(KING, 'k');
        v->startFen = "rbnsgk/5p/6/6/P5/KGSNBR[-] w 0 1";
        v->pieceDrops = true;
        v->capturesToHand = true;
        v->promotionRank = RANK_5;
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->promotedPieceType[SHOGI_PAWN]   = GOLD;
        v->promotedPieceType[SHOGI_KNIGHT] = GOLD;
        v->promotedPieceType[SILVER]       = GOLD;
        v->promotedPieceType[BISHOP]       = HORSE;
        v->promotedPieceType[ROOK]         = DRAGON;
        v->immobilityIllegal = true;
        v->shogiPawnDropMateIllegal = true;
        return v;
    }
    Variant* minishogi_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_5;
        v->maxFile = FILE_E;
        v->reset_pieces();
        v->add_piece(SHOGI_PAWN, 'p');
        v->add_piece(SILVER, 's');
        v->add_piece(GOLD, 'g');
        v->add_piece(BISHOP, 'b');
        v->add_piece(HORSE, 'h');
        v->add_piece(ROOK, 'r');
        v->add_piece(DRAGON, 'd');
        v->add_piece(KING, 'k');
        v->startFen = "rbsgk/4p/5/P4/KGSBR[-] w 0 1";
        v->pieceDrops = true;
        v->capturesToHand = true;
        v->promotionRank = RANK_5;
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->promotedPieceType[SHOGI_PAWN] = GOLD;
        v->promotedPieceType[SILVER]     = GOLD;
        v->promotedPieceType[BISHOP]     = HORSE;
        v->promotedPieceType[ROOK]       = DRAGON;
        v->immobilityIllegal = true;
        v->shogiPawnDropMateIllegal = true;
        return v;
    }
    Variant* losalamos_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_6;
        v->maxFile = FILE_F;
        v->remove_piece(BISHOP);
        v->startFen = "rnqknr/pppppp/6/6/PPPPPP/RNQKNR w - - 0 1";
        v->promotionRank = RANK_6;
        v->promotionPieceTypes = {QUEEN, ROOK, KNIGHT};
        v->doubleStep = false;
        v->castling = false;
        return v;
    }
    Variant* almost_variant() {
        Variant* v = chess_variant();
        v->remove_piece(QUEEN);
        v->add_piece(CHANCELLOR, 'c');
        v->startFen = "rnbckbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBCKBNR w KQkq - 0 1";
        v->promotionPieceTypes = {CHANCELLOR, ROOK, BISHOP, KNIGHT};
        return v;
    }
    Variant* chigorin_variant() {
        Variant* v = chess_variant();
        v->add_piece(CHANCELLOR, 'c');
        v->startFen = "rbbqkbbr/pppppppp/8/8/8/8/PPPPPPPP/RNNCKNNR w KQkq - 0 1";
        v->promotionPieceTypes = {QUEEN, CHANCELLOR, ROOK, BISHOP, KNIGHT};
        return v;
    }
    Variant* shatar_variant() {
        Variant* v = chess_variant();
        v->remove_piece(QUEEN);
        v->add_piece(BERS, 'j');
        v->startFen = "rnbjkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBJKBNR w - - 0 1";
        v->promotionPieceTypes = {BERS};
        v->doubleStep = false;
        v->castling = false;
        v->bareKingValue = VALUE_DRAW; // Robado
        v->shatarMateRule = true;
        return v;
    }
    Variant* clobber_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_6;
        v->maxFile = FILE_E;
        v->reset_pieces();
        v->add_piece(CLOBBER_PIECE, 'p');
        v->startFen = "PpPpP/pPpPp/PpPpP/pPpPp/PpPpP/pPpPp w 0 1";
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->stalemateValue = -VALUE_MATE;
        v->immobilityIllegal = false;
        return v;
    }
    Variant* breakthrough_variant() {
        Variant* v = fairy_variant_base();
        v->reset_pieces();
        v->add_piece(BREAKTHROUGH_PIECE, 'p');
        v->startFen = "pppppppp/pppppppp/8/8/8/8/PPPPPPPP/PPPPPPPP w 0 1";
        v->promotionPieceTypes = {};
        v->firstRankDoubleSteps = false;
        v->castling = false;
        v->stalemateValue = -VALUE_MATE;
        v->flagPiece = BREAKTHROUGH_PIECE;
        v->whiteFlag = Rank8BB;
        v->blackFlag = Rank1BB;
        return v;
    }
    Variant* connect4_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_6;
        v->maxFile = FILE_G;
        v->reset_pieces();
        v->add_piece(IMMOBILE_PIECE, 'p');
        v->startFen = "7/7/7/7/7/7[PPPPPPPPPPPPPPPPPPPPPppppppppppppppppppppp] w 0 1";
        v->pieceDrops = true;
        v->dropOnTop = true;
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->stalemateValue = VALUE_DRAW;
        v->immobilityIllegal = false;
        v->connectN = 4;
        return v;
    }
    Variant* tictactoe_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_3;
        v->maxFile = FILE_C;
        v->reset_pieces();
        v->add_piece(IMMOBILE_PIECE, 'p');
        v->startFen = "3/3/3[PPPPPpppp] w 0 1";
        v->pieceDrops = true;
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->stalemateValue = VALUE_DRAW;
        v->immobilityIllegal = false;
        v->connectN = 3;
        return v;
    }
#ifdef LARGEBOARDS
    Variant* shogi_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_9;
        v->maxFile = FILE_I;
        v->reset_pieces();
        v->add_piece(SHOGI_PAWN, 'p');
        v->add_piece(LANCE, 'l');
        v->add_piece(SHOGI_KNIGHT, 'n');
        v->add_piece(SILVER, 's');
        v->add_piece(GOLD, 'g');
        v->add_piece(BISHOP, 'b');
        v->add_piece(HORSE, 'h');
        v->add_piece(ROOK, 'r');
        v->add_piece(KING, 'k');
        v->add_piece(DRAGON, 'd');
        v->startFen = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL[-] w 0 1";
        v->pieceDrops = true;
        v->capturesToHand = true;
        v->promotionRank = RANK_7;
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->promotedPieceType[SHOGI_PAWN]   = GOLD;
        v->promotedPieceType[LANCE]        = GOLD;
        v->promotedPieceType[SHOGI_KNIGHT] = GOLD;
        v->promotedPieceType[SILVER]       = GOLD;
        v->promotedPieceType[BISHOP]       = HORSE;
        v->promotedPieceType[ROOK]         = DRAGON;
        v->mandatoryPiecePromotion = false;
        v->immobilityIllegal = true;
        v->shogiPawnDropMateIllegal = true;
        return v;
    }
    Variant* capablanca_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_8;
        v->maxFile = FILE_J;
        v->castlingKingsideFile = FILE_I;
        v->castlingQueensideFile = FILE_C;
        v->add_piece(ARCHBISHOP, 'a');
        v->add_piece(CHANCELLOR, 'c');
        v->startFen = "rnabqkbcnr/pppppppppp/10/10/10/10/PPPPPPPPPP/RNABQKBCNR w KQkq - 0 1";
        v->promotionPieceTypes = {ARCHBISHOP, CHANCELLOR, QUEEN, ROOK, BISHOP, KNIGHT};
        return v;
    }
    Variant* janus_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_8;
        v->maxFile = FILE_J;
        v->castlingKingsideFile = FILE_I;
        v->castlingQueensideFile = FILE_B;
        v->add_piece(ARCHBISHOP, 'j');
        v->startFen = "rjnbkqbnjr/pppppppppp/10/10/10/10/PPPPPPPPPP/RJNBKQBNJR w KQkq - 0 1";
        v->promotionPieceTypes = {ARCHBISHOP, QUEEN, ROOK, BISHOP, KNIGHT};
        return v;
    }
    Variant* embassy_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_8;
        v->maxFile = FILE_J;
        v->castlingKingsideFile = FILE_H;
        v->castlingQueensideFile = FILE_B;
        v->add_piece(ARCHBISHOP, 'a');
        v->add_piece(CHANCELLOR, 'c');
        v->startFen = "rnbqkcabnr/pppppppppp/10/10/10/10/PPPPPPPPPP/RNBQKCABNR w KQkq - 0 1";
        v->promotionPieceTypes = {ARCHBISHOP, CHANCELLOR, QUEEN, ROOK, BISHOP, KNIGHT};
        return v;
    }
    Variant* jesonmor_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_9;
        v->maxFile = FILE_I;
        v->reset_pieces();
        v->add_piece(KNIGHT, 'n');
        v->startFen = "nnnnnnnnn/9/9/9/9/9/9/9/NNNNNNNNN w - - 0 1";
        v->promotionPieceTypes = {};
        v->doubleStep = false;
        v->castling = false;
        v->stalemateValue = -VALUE_MATE;
        v->flagPiece = KNIGHT;
        v->whiteFlag = make_bitboard(SQ_E5);
        v->blackFlag = make_bitboard(SQ_E5);
        v->flagMove = true;
        return v;
    }
    Variant* courier_variant() {
        Variant* v = fairy_variant_base();
        v->maxRank = RANK_8;
        v->maxFile = FILE_L;
        v->remove_piece(QUEEN);
        v->add_piece(ALFIL, 'e');
        v->add_piece(FERS, 'f');
        v->add_piece(COMMONER, 'm');
        v->add_piece(WAZIR, 'w');
        v->startFen = "rnebmk1wbenr/1ppppp1pppp1/6f5/p5p4p/P5P4P/6F5/1PPPPP1PPPP1/RNEBMK1WBENR w - - 0 1";
        v->promotionPieceTypes = {FERS};
        v->doubleStep = false;
        v->castling = false;
        v->bareKingValue = -VALUE_MATE;
        v->bareKingMove = true;
        v->stalemateValue = -VALUE_MATE;
        return v;
    }
#endif


void VariantMap::init() {
    // Add to UCI_Variant option
    add("chess", chess_variant());
    add("standard", chess_variant());
    add("makruk", makruk_variant());
    add("asean", asean_variant());
    add("ai-wok", aiwok_variant());
    add("shatranj", shatranj_variant());
    add("amazon", amazon_variant());
    add("hoppelpoppel", hoppelpoppel_variant());
    add("kingofthehill", kingofthehill_variant());
    add("racingkings", racingkings_variant());
    add("losers", losers_variant());
    add("giveaway", giveaway_variant());
    add("antichess", antichess_variant());
    add("codrus", codrus_variant());
    add("extinction", extinction_variant());
    add("kinglet", kinglet_variant());
    add("horde", horde_variant());
    add("3check", threecheck_variant());
    add("5check", fivecheck_variant());
    add("crazyhouse", crazyhouse_variant());
    add("loop", loop_variant());
    add("chessgi", chessgi_variant());
    add("pocketknight", pocketknight_variant());
    add("placement", placement_variant());
    add("sittuyin", sittuyin_variant());
    add("euroshogi", euroshogi_variant());
    add("judkinshogi", judkinsshogi_variant());
    add("minishogi", minishogi_variant());
    add("losalamos", losalamos_variant());
    add("almost", almost_variant());
    add("chigorin", chigorin_variant());
    add("shatar", shatar_variant());
    add("clobber", clobber_variant());
    add("breakthrough", breakthrough_variant());
    add("connect4", connect4_variant());
    add("tictactoe", tictactoe_variant());
#ifdef LARGEBOARDS
    add("shogi", shogi_variant());
    add("capablanca", capablanca_variant());
    add("janus", janus_variant());
    add("embassy", embassy_variant());
    add("jesonmor", jesonmor_variant());
    add("courier", courier_variant());
#endif
}

void VariantMap::add(std::string s, const Variant* v) {
  insert(std::pair<std::string, const Variant*>(s, v));
}

void VariantMap::clear_all() {
  for (auto const& element : *this)
      delete element.second;
  clear();
}

std::vector<std::string> VariantMap::get_keys() {
  std::vector<std::string> keys;
  for (auto const& element : *this)
      keys.push_back(element.first);
  return keys;
}
