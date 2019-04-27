#ifndef __OTSERV_IOMARKET_H__
#define __OTSERV_IOMARKET_H__

#include <string>
#include "account.h"
#include "player.h"
#include "database.h"

class IOMarket
{
	public:
		IOMarket() {}
		~IOMarket() {}

		static IOMarket* getInstance()
		{
			static IOMarket instance;
			return &instance;
		}

		MarketOfferList getActiveOffers(MarketAction_t action);
		MarketOfferList getOwnOffers(MarketAction_t action, uint32_t playerId);
		HistoryMarketOfferList getOwnHistory(MarketAction_t action, uint32_t playerId);

		ExpiredMarketOfferList getExpiredOffers(MarketAction_t action);

		int32_t getPlayerOfferCount(uint32_t playerId);
		uint32_t getOfferIdByCounter(uint32_t timestamp, uint16_t counter);
		MarketOfferEx getOfferById(uint32_t id);

		void createOffer(uint32_t playerId, MarketAction_t action, uint32_t itemId, uint16_t amount, uint32_t price, bool anonymous, const std::string& attrss);
		void acceptOffer(uint32_t offerId, uint16_t amount);
		void deleteOffer(uint32_t offerId);
		void deleteOfferMessage(uint32_t offerId);

		void appendHistory(uint32_t playerId, MarketAction_t type, uint16_t itemId, uint16_t amount, uint32_t price, time_t timestamp, MarketOfferState_t state, const std::string& attrss);
		void moveOfferToHistory(uint32_t offerId, MarketOfferState_t state);
		void clearOldHistory();

		void updateStatistics();

		MarketStatistics* getPurchaseStatistics(uint16_t itemId);
		MarketStatistics* getSaleStatistics(uint16_t itemId);

	private:
		std::map<uint16_t, MarketStatistics> purchaseStatistics;
		std::map<uint16_t, MarketStatistics> saleStatistics;
};

#endif
