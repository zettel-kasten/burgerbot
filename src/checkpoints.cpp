// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (   1337, uint256("0x30fb4e683aeea122f563f246b544343f0ac72034b2689b6106a0a22db71a36a5"))
        (  50000, uint256("0x68fe27f8eb77e0986ef3004f8746babed42e005d71b42aace50497eda9ede86f"))
        ( 100000, uint256("0x2fceac4002f21f2f10c9666ecef584d1a62847a84656e121366284b3d84ac7bb"))
        ( 150000, uint256("0xc6deb0708b79d29f450a51f4a097dc0fca1f2e40cce8a44ebd526cfd9b6dba17"))
        ( 200000, uint256("0x01191f7558f66868ee89a0e9eb955a661b773877cde1d69352d1c7c29385e2f2"))
        ( 250000, uint256("0x2a81f42cf34d25c93c57b18c202219c79f24ea943ad8c652cb5f09269d249b66"))
        ( 300000, uint256("0x770283ba481729a929bdcee8b031348954d2887270fe4148655aff3f7bea074b"))
        ( 350000, uint256("0x5b9f6612bb38069c39bcd460bec551f899c05e4023a921e79bc11031129e178d"))
        ( 400000, uint256("0xbc9d878d6da7eca9aaaa8f0b0d117e56ff5bfaffa5e5577dff61b056a95016a6"))
        ( 450000, uint256("0x1f3300f5b7fdca3adfde43b71be1fec3d68207bd64b7627a3fa1afaa4f4b28fe"))
        ( 500000, uint256("0x798bfa45d78f7f2ea168b38e42112ed89da3ce423152ca260575a206eba00901"))
        ( 550000, uint256("0xd5088d7689f1e6cf252b59df15c087093cf86d68bcc70cc04006a92c4bf516b7"))
        ( 600000, uint256("0xa8dc15411d4bcd4775db395a95ab73f03a22298fb20b79c8f8c5606e97e777ca"))
        ( 650000, uint256("0xcd16af3c8c68dee16c644b61c20dd0abacd79e81441009816cb885c63bc6b14f"))
        ( 700000, uint256("0x7b7336bc21e09d7f30e5ac422204c0adc6e458524402a3f9ffd378982cea2632"))
        ( 750000, uint256("0x626cdf6a8de9594a8a5fca4814456a91245ce63a282dc737308c630b3c842f1f"))
        ( 800000, uint256("0x586d05cbdc066fd04e71a9cfd9acd5cb268d619af1238b9fd35966df5b07835d"))
        ( 850000, uint256("0xad59869722b97d7b836fc092781af981a3fbd5639fdd7529051e1844cdc460e5"))
        ( 900000, uint256("0x2744ae9fb2c3d9de322fbea99142732807b5c0e274525c3136bf0c8c85253efe"))
        ( 950000, uint256("0xfdb87f2f45f8313d2ec15d20912a64556f3d8388eba35932328526600557d828"))
        ( 1000000, uint256("0xd91fa67c2b4502a7d54894cb89f654e924b7303c94f46d194c2e654975a88298"))
        ( 1050000, uint256("0x7789c26a678c4ea7b1bace1b1abebc940c17724981fac4edb15183c83e6583a4"))
        ( 1100000, uint256("0x91774d58d4ef6ced953e8690b797f92169b549c37fc8292633d835d757046915"))
        ( 1150000, uint256("0xc6f0a2002ba2f8f01ce409c234d746b7cf1f2aba09b2ddf406a7db928b5bb639"))
        ( 1200000, uint256("0x89b08caaaba890ccc7582767ae6ec8a22fa3f6dd6d6fde49e63024a4cd9e11f9"))
        ( 1250000, uint256("0x5c23fd6ef3c8202fbf1a958f37d13697ab703bd68f451877378a90409e12c04f"))
        ( 1300000, uint256("0x6bffb09e2f5c08bba74caf9d443e46e44c86aaba1d89e8c26ed2496fc068b878"))
        ( 1350000, uint256("0x9ed3b4754b1887dac885444549fe8248303fda861ff7d9cf34dd37212dfd19b8"))
        ( 1400000, uint256("0x44e1c9c6ba1fac11e33a371d44e0fa4f1ef307941ab37b02e94e5dda9c359f98"))
        ( 1450000, uint256("0xbe67f51d45913b43924cb89da014bcb3e805a2330c7198aef4af0d0d8a2d45fd"))
        ( 1500000, uint256("0x33a674d7161cc0efe5f57ad03f8ae2c2f55fe81261165f772bf059b08ab975fd"))
        ( 1550000, uint256("0x53bd8252446cdb12c506e8a96c7f5deb265d4ba67e773e14da3709fa735c519c"))
        ( 1600000, uint256("0x420688349e58d858cb5b29259605cda5c5a4f2032530da7d53ac740460c5abdc"))
        ( 1650000, uint256("0x19ee474505ecaea903388b9eb68ce2e92aad1a5dc688c1c126e8ec690677b544"))
        ( 1700000, uint256("0xd812c07ddce2a50d2202345ba67fee60e193b845c0eaf09b7f30f21da0135b66"))
        ( 1750000, uint256("0x9a3f48cdbeaf679a31a2bd7490e1a91477ad082600b5c626a138f27334789aec"))
        ( 1800000, uint256("0x9ec6d5f9f62ee244a0442b30f79779360077272ecc736fdfb8e5dc1c24e8499b"))
        ( 1850000, uint256("0x8a88d21dc2a954829e18fc442d01fecd5a54943aef1c6144d14b81301690bd0c"))
        ( 1900000, uint256("0xb93a58d3490137c6f0ecc3176324316f486ead45513e3745c9e125c3af56281b"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1421787289, // * UNIX timestamp of last checkpoint block
        239377,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        150.0     // * estimated number of transactions per day after checkpoint


    };

    const CCheckpointData &Checkpoints() {
        return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
        //return true;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        /*const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);*/
        return 0.0;
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        //const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        //return checkpoints.rbegin()->first;
        return 0;

    }

    unsigned int LastCheckPoint()
    {
        if (Checkpoints().mapCheckpoints->empty())
            return 0;

        //return Checkpoints().mapCheckpoints->rbegin()->first;
        return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        /*const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }*/
        return NULL;
    }
}
