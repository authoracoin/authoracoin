// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Bitcoin Green developers
// Copyright (c) 2018 The Authoracoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
		(0, uint256("0x000009411fe9341392a7fc47bdb5759bcfb7e2053e2172b2a96f33bf61736708"))
		(18391, uint256("0x2da47f4141966341d4e11e10dcc8de720d5873055136658fbc6fe2ec6f1a8841"))
		(51652, uint256("0x69168607a69c6dc624722270818c3db58f7016d05560e1c90bbe7b5dfaf8a265"))
		(100000, uint256("0x45b0db4ed7a31fbff9980c879fd621c51fb873b82c975972bc38d9d67355a86f"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1544528689, // * UNIX timestamp of last checkpoint block
    218561,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x0000003c94d37c93846cd80ea6c1735c0cd0aa43de717445c81ad41eec76941f"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1538474401,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x0000069d9eb20f6108746dc243e56e5876c2ac00e524c8f3ecd81e281fc542c7"));
	
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1538474402,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0x2d;
        pchMessageStart[2] = 0xf1;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("048215a5cda2785aa066404c7c1097e13e73782d6d06cbbd44e2f7d14cf56ee4e433dc16b107e4f7dd3a0c7fb86cd42316c12de132122dbb9522f0ec55ebfa7dd0");
        nDefaultPort = 23854;
        bnProofOfWorkLimit = ~uint256(0) >> 16;
        nSubsidyHalvingInterval = 1050000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Authoracoin: 1 day
        nTargetSpacing = 1 * 60;  // Authoracoin: 1 minutes
        nMaturity = 30;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 100000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 300;
        nModifierUpdateBlock = 1; // we use the version 2 for ATHR

        /**
        python ~/GenesisH0new/genesis.py -a quark-hash -z "Poloniex exchange have launched their official trading app for iOS and Android" -t 1538474400 -p 042f8d34b56ecc2833ab4117a9a1d60cc16f2bdbaea320de00a4d32d0e1ca63466127d844f8a633817f1cab201f86aeb572284351fd0757dbf65cc6aad7fae8f76 -v 0
		algorithm: quark-hash
		merkle hash: 6852e9739b92effcd33d6c5f6d94fa672471093fbedfee3769028780876e62f9
		pszTimestamp: Poloniex exchange have launched their official trading app for iOS and Android
		pubkey: 042f8d34b56ecc2833ab4117a9a1d60cc16f2bdbaea320de00a4d32d0e1ca63466127d844f8a633817f1cab201f86aeb572284351fd0757dbf65cc6aad7fae8f76
		time: 1538474400
		bits: 0x1e0ffff0
		Searching for genesis hash..
		genesis hash found!
		nonce: 846894
		genesis hash: 000009411fe9341392a7fc47bdb5759bcfb7e2053e2172b2a96f33bf61736708
         */
        const char* pszTimestamp = "Poloniex exchange have launched their official trading app for iOS and Android";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("042f8d34b56ecc2833ab4117a9a1d60cc16f2bdbaea320de00a4d32d0e1ca63466127d844f8a633817f1cab201f86aeb572284351fd0757dbf65cc6aad7fae8f76") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1538474400;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 846894;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000009411fe9341392a7fc47bdb5759bcfb7e2053e2172b2a96f33bf61736708"));
        assert(genesis.hashMerkleRoot == uint256("0x6852e9739b92effcd33d6c5f6d94fa672471093fbedfee3769028780876e62f9"));

        // DNS Seeding
        vSeeds.push_back(CDNSSeedData("authoracoin.com", "dnsseed.authoracoin.com"));
	vSeeds.push_back(CDNSSeedData("seed1.authoracoin.com", "seed1.authoracoin.com"));
        vSeeds.push_back(CDNSSeedData("seed2.authoracoin.com", "seed2.authoracoin.com"));
	vSeeds.push_back(CDNSSeedData("seed3.authoracoin.com", "seed3.authoracoin.com"));
	vSeeds.push_back(CDNSSeedData("seed4.authoracoin.com", "seed4.authoracoin.com"));

        // Authoracoin addresses start with 'A'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        // Authoracoin script addresses start with '4'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 8);
        // Authoracoin private keys start with 'J'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 43);
        // Authoracoin BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Authoracoin BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "049a19348282ff6c354f769301a702dabb1c8d2e46e1af12b15ed681204b034bc7eee1610e4af8a6821e4f064049d0883d5ace467ac50f063633e22719c1c2e297";
        strMasternodePoolDummyAddress = "AHcqNBVGqc9XXuzvSbVj4ffPDNfefDG2wy";
        nStartMasternodePayments = genesis.nTime + 14400; // 4 hours after genesis creation

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0x2e;
        pchMessageStart[2] = 0xf2;
        pchMessageStart[3] = 0x06;
        vAlertPubKey = ParseHex("04e883f82fc706ef0e70e34a64bfd82790ae942f74f18646484e4bc93026714f3492193871952d67198e101116f6112844afea52e69b0112061534580c37b07d81");
        nDefaultPort = 24854;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Authoracoin: 1 day
        nTargetSpacing = 1 * 60;  // Authoracoin: 1 minute
        nLastPOWBlock = 20100;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 100000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1538474401;
        genesis.nNonce = 454734;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000003c94d37c93846cd80ea6c1735c0cd0aa43de717445c81ad41eec76941f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // Testnet Authoracoin addresses start with 'a'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);
        // Testnet Authoracoin script addresses start with '6'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        // Testnet private keys start with 'j'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 105);
        // Testnet Authoracoin BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Authoracoin BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Authoracoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "040d285ec5c08935c66562107d3752e8cff58248f9ba6d6dfe9d803cad0128dab507644fc44e9dfecb373b2ea23b069c8bef5b9966b73a669463cf2a14821bbec1";
        strMasternodePoolDummyAddress = "AHcqNBVGqc9XXuzvSbVj4ffPDNfefDG2wy";
        nStartMasternodePayments = genesis.nTime + 14400; // 4 hours after genesis
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0x2f;
        pchMessageStart[2] = 0xa2;
        pchMessageStart[3] = 0x07;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Authoracoin: 1 day
        nTargetSpacing = 1 * 60;        // Authoracoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1538474402;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 330547;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 25854;
        assert(hashGenesisBlock == uint256("0x0000069d9eb20f6108746dc243e56e5876c2ac00e524c8f3ecd81e281fc542c7"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 26854;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
